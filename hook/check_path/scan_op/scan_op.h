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
#include <map>

using namespace std;

class scan_op
{
public:
    scan_op();
    void open_scan();

private:
    bool _run = true;
    string _cmd = "../data/check_op.sh";
    string _log = "check_op.log";

    void observe_op();                  //命令监控
    bool filter_op(const string &str);  //过滤器
    void less_enter(char *buf);         //去除换行符号
    bool watch_op(const string &str);   //内容统计与分析
};

#endif // SCAN_OP_H
