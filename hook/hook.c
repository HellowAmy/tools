#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mount.h>

#include "htools.h"

///* Mount a filesystem.  */
//extern int mount (const char *__special_file, const char *__dir,
//		  const char *__fstype, unsigned long int __rwflag,
//		  const void *__data) __THROW;

///* Unmount a filesystem.  */
//extern int umount (const char *__special_file) __THROW;

///* Unmount a filesystem.  Force unmounting if FLAGS is set to MNT_FORCE.  */
//extern int umount2 (const char *__special_file, int __flags) __THROW;


static int (*org_mount) (const char *__special_file, const char *__dir,
          const char *__fstype, unsigned long int __rwflag,
          const void *__data) = NULL;
static int (*org_umount) (const char *__special_file) = NULL;

static int (*org_umount2) (const char *__special_file, int __flags) = NULL;



//extern char * __progname;

//static int (*hook_mount)(const  char  *source,  const char *target, const char *filesystemtype, unsigned long mountflags, const void *data)=NULL;
//#define LINE_MAX 1024
//const char* filepath = "/tmp/1.txt";

//hook_open保存系统调用open函数指针
void __attribute__ ((constructor)) before_load(void)
{
   if(org_mount == NULL) org_mount = dlsym(RTLD_NEXT, "mount");
   if(org_umount == NULL) org_umount = dlsym(RTLD_NEXT, "mount");
   if(org_umount2 == NULL) org_umount2 = dlsym(RTLD_NEXT, "mount");
}


//生成.SO mount符号函数，先于调用系统mount
int mount(const char *__special_file, const char *__dir,
          const char *__fstype, unsigned long int __rwflag,
          const void *__data)
{

    vlogf("[%s : %s : %s : %ld]",__special_file,__dir,__fstype,__rwflag);

    char disk_rule[256];
    int rule = 0;
    if(get_disk_rule(file_table,"/dev/sdb",disk_rule) == 1)
    {
        rule = rule_cmp(disk_rule);
    }
    show_log(rule);


    //拦截
    if(rule == 2) return org_mount(__special_file,__dir,__fstype,MS_RDONLY,__data);
    else if(rule == 3) return -1;

    return org_mount(__special_file,__dir,__fstype,__rwflag,__data); //MS_RDONLY
}



//(const  char  *source,  const char *target, const char *filesystemtype, unsigned long mountflags, const void *data)
//{

//    return
//	char buf2[256];
//memset(buf2,0,sizeof(buf2));
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
