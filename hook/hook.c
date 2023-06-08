#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mount.h>

#include "htools.h"

//返回hook函数
#define FN_MOUNT_ORG org_mount(__special_file, __dir, __fstype, __rwflag, __data)   //放行权限
#define FN_MOUNT_RO org_mount(__special_file, __dir, __fstype, MS_RDONLY, __data)   //只读权限
#define FN_MOUNT_OO -1                                                              //拦截权限


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
//== hook函数原型 ==


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
                rule_cmp(disk_rule,en); //根据文件表格的规则赋值权限
                vlogf("[disk_serial]: [%s]",disk_serial);
            }
            else vlogf("open file_table err: get_disk_rule"); 
        }
        show_log(en); //显示最终权限

        return org_mount(__special_file, __dir, __fstype, __rwflag, __data);

        //返回权限对应函数指针
        switch (en)
        {
        case e_pass     : return FN_MOUNT_ORG; 
        case e_limit    : return FN_MOUNT_RO; 
        case e_failed   : return FN_MOUNT_OO;
        }

        vlogf("not found rule: return FN_MOUNT_RO");
        return FN_MOUNT_RO;


        // switch (en)
        // {
        // case 0: {

        // } break;
        // case 1: return FN_MOUNT_ORG break;
        // case 2: {} break;
        // case 3: {} break;
        // case 4: {} break;
        //     break;
        
        // default:
        //     break;
        // }
        // // 拦截
        // if (rule == 2) return org_mount(__special_file, __dir, __fstype, MS_RDONLY, __data);
        // else if (rule == 3) return -1;
    }
    
    // vlogf("[mount]: return org");
    return FN_MOUNT_ORG; 
    // return org_mount(__special_file, __dir, __fstype, __rwflag, __data);

    //     is_find = 0;
    // if(find_c(__special_file,"/dev/",0) == -1)
    //     is_find = 0;

    // if(is_find == 0)
    // {
    //     vlogf("org exit");
    //     return org_mount(__special_file,__dir,__fstype,__rwflag,__data);
    // }

    // vlogf("[mount in]: [%s : %s : %s : %ld]",__special_file,__dir,__fstype,__rwflag);
    // // return org_mount(__special_file,__dir,__fstype,__rwflag,__data); //MS_RDONLY

    // char disk_rule[256];
    // int rule = 0;
    // if(get_disk_rule(file_table,__special_file,disk_rule) == 1)
    // {
    //     rule = rule_cmp(disk_rule);
    // }
    // show_log(rule);
    // vlogf("[mount rule]: %d",rule);

    // //拦截
    // if(rule == 2) return org_mount(__special_file,__dir,__fstype,MS_RDONLY,__data);
    // else if(rule == 3) return -1;

    // return org_mount(__special_file,__dir,__fstype,__rwflag,__data); //MS_RDONLY
}

//(const  char  *source,  const char *target, const char *filesystemtype, unsigned long mountflags, const void *data)
//{

//    return
//	char buf2[256];
// memset(buf2,0,sizeof(buf2));
//	ss(source,buf2);

//	char get_usb_key[256];
//    char lsblk[50]="lsblk --nodeps -no serial  ";
//    memset(get_usb_key,0,sizeof(get_usb_key));

//    strcat(lsblk,buf2);
//    FILE *fp2=popen(lsblk,"r");
//    fgets(get_usb_key,256,fp2);
//    fclose(fp2);

//   FILE *fp1;
//   fp1 = fopen("/home/kylin/桌面/hook_mount/2.txt", "rw+");
//   fprintf(fp1,"this is c ===%s\n,%s\n,%s\n,%s\n,%s\n",source,target,filesystemtype,get_usb_key,lsblk);
//   fclose(fp1);

//   return hook_mount(source,target,filesystemtype,mountflags,data);

//   int shmid;
//   char *shmaddr;

////      key_t ftok(const char *pathname, int proj_id);
//   key_t key;
//   key = ftok("/tmp/shared",23);

//    //create
////      int shmget(key_t key, size_t size, int shmflg);
//   shmid = shmget(key,1024*4,0);
//   if(shmid == -1){
//       return hook_mount(source,target,filesystemtype,mountflags,data);
//   }
//   int hook_ret;
//   hook_ret = -1;
//   FILE *fp;
//   int line_len = 0;         // 文件每行的长度
//   char buf[LINE_MAX] = {0}; // 行数据缓存
//   fp = fopen(filepath, "r");
//   if (NULL == fp)
//   {
//      //printf("open %s failed.\n", path);
//      hook_ret = hook_mount(source,target,filesystemtype,mountflags,data);
//      fclose(fp);
//      return hook_ret;  //return zheng chang
//   }
//   while(fgets(buf, LINE_MAX, fp))
//   {
//      line_len = strlen(buf);
//      //排除换行符
//      if ('\n' == buf[line_len - 1])
//      {
//         buf[line_len - 1] = '\0';
//         line_len--;
//         if(0 == line_len) //空行
//         {
//           continue;
//         }
//      }
//      //排除回车符
//      if ('\r' == buf[line_len - 1])
//      {
//         buf[line_len - 1] = '\0';
//         line_len--;
//         if (0 == line_len) //空行
//         {
//            continue;
//         }
//      }
//      // 对每行数据(buf)进行处理
//      if(strstr(buf, source) != NULL)
//      {
//         if(buf[strlen(buf)-1] == '2') //read and write
//         {
//            hook_ret  = hook_mount(source,target,filesystemtype,mountflags,data);
//         }
//         if(buf[strlen(buf)-1] == '1') //read ouly
//         {
//             hook_ret  = hook_mount(source,target,filesystemtype,MS_RDONLY,data);
//         }
//         if(buf[strlen(buf)-1] == '0') //cann't
//         {
//             hook_ret  = -1;
//         }
//         break;
//      }
//   }
//   if (0 == feof) // 未读到文件末尾
//   {
//      hook_ret = hook_mount(source,target,filesystemtype,mountflags,data);
//      fclose(fp);
//      return hook_ret;
//   }
//   //file no have source
//   //file no have source
//   //guangqu chuli
//   //guangqu chuli
//   fclose(fp);
//   return hook_ret;
//}
