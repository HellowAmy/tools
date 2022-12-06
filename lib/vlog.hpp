#ifndef VLOG_H
#define VLOG_H

//注解:常用日志文件,包含Qt和C++两种类型

//#include "vlog.h"
//#define OPEN_QT
#define OPEN_CPP



//===== QT =====
#ifdef OPEN_QT

#include <QDebug>
#ifndef out
#define out qDebug()\
    <<"{"<<__FILE__<<":"<<__LINE__<<"} <<<<"
#endif



//=====
//模板打印--数组
template<class T>
void show_arr(const T vec,QString flg = "|")
{
    qDebug()<<"===== " +flg+ " =====";
    for(int i = 0;i<vec.size();i++)
    {
        qDebug()<<vec[i];
    }
    qDebug()<<"--------------------";
}
//=====


#endif // OPEN_QT
//===== QT =====






//===== C++ =====
#ifdef OPEN_CPP

#include <iostream>
using std::cout;
using std::endl;

#define vlog cout\
    <<"{ "<<__FILE__<<": "<<__LINE__<<" } <<<< "

////=====
////带换行日志
//#define vlog(format, ...) \
//    do {printf("( %s | %s:%d ) ========== { " format " }\n", \
//    __FILE__, __func__, __LINE__, ##__VA_ARGS__);} while (0)

////不换行日志
//#define clog(format, ...) \
//    do {printf("( %s | %s:%d ) " format , \
//     __FILE__, __func__, __LINE__, ##__VA_ARGS__);} while (0)
////=====


#endif // OPEN_CPP
//===== C++ =====

#endif // VLOG_H
