#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mount.h>
#include <ctype.h>

#include "str_sc.h"


//== 对应权限函数 ==
#define FN_MOUNT_ORG org_mount(__special_file, __dir, __fstype, __rwflag, __data)   //放行权限
#define FN_MOUNT_RO org_mount(__special_file, __dir, __fstype, MS_RDONLY, __data)   //只读权限
#define FN_MOUNT_OO -1                                                              //拦截权限
//== 对应权限函数 ==


//== hook函数原型 ==
///* Mount a filesystem.  */
// extern int mount (const char *__special_file, const char *__dir,
//		  const char *__fstype, unsigned long int __rwflag,
//		  const void *__data) __THROW;

///* Unmount a filesystem.  */
// extern int umount (const char *__special_file) __THROW;

///* Unmount a filesystem.  Force unmounting if FLAGS is set to MNT_FORCE.  */
// extern int umount2 (const char *__special_file, int __flags) __THROW;

static int (*org_mount)(const char *__special_file, const char *__dir,
                        const char *__fstype, unsigned long int __rwflag,
                        const void *__data) = NULL;
static int (*org_umount)(const char *__special_file) = NULL;
static int (*org_umount2)(const char *__special_file, int __flags) = NULL;

// hook_open保存系统调用open函数指针
void __attribute__((constructor)) before_load(void)
{
    if (org_mount == NULL)
        org_mount = dlsym(RTLD_NEXT, "mount");
    if (org_umount == NULL)
        org_umount = dlsym(RTLD_NEXT, "umount");
    if (org_umount2 == NULL)
        org_umount2 = dlsym(RTLD_NEXT, "umount2");
}
//== hook函数原型 ==


//== 文件与日志 ==
//文件路径
const char *file_table  = "/etc/hook_watch/file_table.txt";  //文件表格
const char *file_log    = "/etc/hook_watch/file_log.txt";    //日志文件

//打印文件日志
#define vlogf(fm,...) do{                       \
    FILE *fd = fopen(file_log,"a+");            \
    if(fd){                                     \
        fprintf(fd,"[%s:<%d>]<<<< " fm "\n",    \
        __func__,__LINE__, ##__VA_ARGS__);      \
        fclose(fd);                             \
    }                                           \
} while(0)
//== 文件与日志 ==


//===== 文件操作函数 =====
//从字符尾部去除换行符号
//参数1:需要去\n符号的字符串
void less_enter(char *buf)
{
    size_t len = strlen(buf);
    for(size_t i=0;i<len;i++)
    {
        if(buf[len -i -1] == '\n')
        {
           buf[len -i -1] = '\0';
           return ;
        }
    }
}

//通过序列号查看文件表格的权限
//参数1:文件表格
//参数2:序列号
//参数3:存储的权限
//返回值:[1/0] 成功或者失败
int check_table(const char *file_table,const char *pserial,char *prule)
{
    int is_open = 0;
    int ret = 0;

    FILE *fd = fopen(file_table,"r");
    if(fd)
    {
        char buf[1024];
        while(fgets(buf,sizeof (buf),fd) != NULL)
        {
            less_enter(buf);
            if(is_open == 0)
            {
                char *cmd = split_ac(buf,"##",1,1);
                char *op = split_ac(buf,"##",2,2);
                if(strcmp(cmd,"open") == 0)
                {
                    if(strcmp(op,"1") == 0) is_open = 1;
                    else is_open = -1;
                }
                free(op);
                free(cmd);
            }
            else if(is_open == 1)
            {
                char *serial = split_ac(buf,"##",2,2);
                char *rule = split_ac(buf,"##",3,3);
                if(strcmp(serial,pserial) == 0)
                {
                    strcpy(prule,rule);
                    ret = 1;
                }
                free(serial);
                free(rule);
            }
            if(is_open == -1 || ret == 1) break;
        }
        fclose(fd);
    }
    return ret;
}

//修正磁盘名称,用于获取序列号
//参数1:原磁盘名称
//参数2:存储的新磁盘名称
void ch_disk_name(const char *source,char *buf)
{
    strcpy(buf,source);
    size_t len = strlen(buf);
    for(size_t i=0;i<len;i++)
    {
        if(isdigit(buf[len -i -1])) buf[len -i -1] = '\0';
        else break;
    }
}

//通过修正的磁盘名称获取序列号
//参数1:磁盘名称
//参数2:存储的序列号
//参数3:序列号长度
//返回值:[1/0] 成功或者失败
int get_disk_serial(const char* pname,char *serial,size_t size_serial)
{
    int ret = 0;
    char cmd[256] = "lsblk --nodeps -no serial ";
    strcat(cmd,pname);
    FILE *fd = popen(cmd,"r");
    if(fd)
    {
        if(fgets(serial,size_serial,fd) != NULL)
        {
            less_enter(serial);
            ret = 1;
        }
        fclose(fd);
    }
    return ret;
}

//从文件表格中查找磁盘对应的权限
//参数1:文件表格
//参数2:磁盘名
//参数3:存储的规则
//参数4:存储的序列号
//参数5:序列号长度
//返回值:[1/0] 成功或者失败
int get_disk_rule(const char* filename,const char* pname,char *rule,char *pserial,int size)
{
    int ret = 0;
    char disk_name[256];
    ch_disk_name(pname,disk_name);

    if(get_disk_serial(disk_name,pserial,size) == 1)
    { 
        if(check_table(filename,pserial,rule) == 1) { ret = 1; }
        else vlogf("err: check_table");
    }
    else vlogf("err: get_disk_serial");
    return ret;
}
//===== 文件操作函数 =====


//== 权限判断部分 == 
//规则
typedef enum en_rule en_rule;
enum en_rule
{
    e_pass,     //文件放行默认挂载权限
    e_limit,    //默认限制只读
    e_failed,   //文件中记录拦截则挂载失败
};

//显示日志
void show_log(en_rule rule)
{
    switch (rule)
    {
    case e_pass     : vlogf("权限:读写 [%d]",rule); break;
    case e_limit    : vlogf("权限:只读 [%d]",rule); break;
    case e_failed   : vlogf("权限:拦截 [%d]",rule); break;
    }
}

//权限判断
void rule_cmp(char *rule,en_rule *en)
{
    if(strcmp(rule,"RW") == 0) *en = e_pass;
    else if(strcmp(rule,"OR") == 0) *en = e_limit;
    else if(strcmp(rule,"OO") == 0) *en = e_failed;
}
//== 权限判断部分 == 


//== 函数拦截部分 ==
int umount(const char *__special_file)
{
    // vlogf("[umount]: [%s]", __special_file);
    return org_umount(__special_file);
}

int umount2(const char *__special_file, int __flags)
{
    // vlogf("[umount2]: [%s : %d]", __special_file, __flags);
    return org_umount2(__special_file, __flags);
}

int mount(const char *__special_file, const char *__dir,
          const char *__fstype, unsigned long int __rwflag,
          const void *__data)
{
    vlogf("==================== [mount]: [%s : %s : %s : %ld]", __special_file, __dir, __fstype, __rwflag);

    // 数据防空
    if (__special_file && __dir && __fstype)
    {
        //磁盘类型排除
        if(find_c(__special_file, "/dev/", 0) == -1)
        { return FN_MOUNT_ORG; }

        //主盘屏蔽拦截
        char disk_name[256];
        ch_disk_name(__special_file,disk_name);
        if(strcmp(disk_name,"/dev/sda") == 0)
        { return FN_MOUNT_ORG; }


        //== 判断开始 == 
        vlogf("[mount dev]: %s",__special_file);
        // return org_mount(__special_file, __dir, __fstype, __rwflag, __data);

        //权限判断
        en_rule en = e_limit;
        {
            char disk_rule[256];
            char disk_serial[256];
            if(get_disk_rule(file_table, __special_file, 
                disk_rule,disk_serial,sizeof(disk_serial)) == 1)
            {
                rule_cmp(disk_rule,&en); //根据文件表格的规则赋值权限
                vlogf("[disk_serial]: [%s]",disk_serial);
            }
            else vlogf("open file_table err: get_disk_rule"); 
            vlogf("####back####serial:%s####rule:%s####",disk_serial,disk_rule);
        }
        show_log(en); //显示最终权限

        // return org_mount(__special_file, __dir, __fstype, __rwflag, __data);

        


        //返回权限对应函数指针
        switch (en)
        {
        case e_pass     : return FN_MOUNT_ORG; 
        case e_limit    : return FN_MOUNT_RO; 
        case e_failed   : return FN_MOUNT_OO;
        }

        vlogf("not found rule: return FN_MOUNT_RO");
        return FN_MOUNT_RO;
    }

    //存在空值时从这返回,一般为开机挂载系统目录时触发
    return FN_MOUNT_ORG; 
}
//== 函数拦截部分 ==
