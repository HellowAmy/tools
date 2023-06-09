#ifndef SCAN_OP_H
#define SCAN_OP_H

#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <iostream>
#include <thread>
#include <regex>
#include <functional>
#include <fstream>
#include <map>

using namespace std;

//通过执行脚本将内容写入日志,并对日志内容进行过滤完成监控
class scan_op
{
public:
    scan_op();
    void open_scan(string cmd = "../data/check_op.sh" ,string log = "check_op.log");
    function<void(string)> func_watch_op;
private:
    bool _run = true;
    long _max_file = (1024*10);
    string _cmd;
    string _log;

    static void create_file(string file);   //不存在则创建
    void observe_op();                      //命令监控
    bool filter_op(const string &str);      //过滤器
    void less_enter(char *buf);             //去除换行符号
    string watch_op(const string &str);     //内容统计与分析
};

#endif // SCAN_OP_H
