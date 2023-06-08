#ifndef HTOOLS_H
#define HTOOLS_H

#include <ctype.h>
#include <stdio.h>
#include "str_sc.h"


//去除换行符号
void less_enter(char *buf)
{
    for(size_t i=0;i<strlen(buf);i++)
    {
        if(buf[i] == '\n')
        {
           buf[i] = '\0';
           return ;
        }
    }
}

//通过序列号查看文件表格的权限
//参数1:文件表格
//参数2:序列号
//参数3:存储的权限
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

    if(get_disk_serial(disk_name,pserial,sizeof(size)) == 1)
    { if(check_table(filename,pserial,rule) == 1) { ret = 1; } }
    return ret;
}

#endif // HTOOLS_H
