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
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "
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
#include <string>
#include <vector>
#include <fstream>
using std::endl;


//===== vflog =====
//说明:简单打印日志系统,输出到文件中
//init()参数说明:
//      [string filename:输出到的文件名路径]
//      [level el:输出等级,等级不足将无法输出]
//      [bool is_new:追加或者从零开始写入到文件]
//
#define cl "\033[0m"<<end
#define okc ok_c && op_c && oc_c
#define okf ok_f && op_f && oc_f
class vflog
{
protected:
    std::vector<std::string> vec
    { "\033[31m[Error","\033[33m[Warning","\033[32m[Debug","[Info" };
public:
    enum level{ e_error,e_warning,e_debug,e_info };
    static vflog* instance() { if(obj==nullptr){obj=new vflog;} return obj; };
    void set_level(level elf,level elc) { el_f=elf; el_c=elc; }
    void close_log(bool of,bool oc) { oc_f=of; oc_c=oc; }

    bool init(std::string filename,level el = e_info,bool is_app = true)
    {
        if(v_filename!=filename){ if(op_f){ op_f=false; ofs.close(); } }
        else { if(op_f) return op_f; } el_f = el;
        if(is_app) ofs.open(filename,std::ios::out | std::ios::app);
        else ofs.open(filename,std::ios::out );
        op_f = ofs.is_open(); return op_f;
    }
    bool init(level el = e_info)
    {
        if(op_c) { return op_c; }
        el_c = el; op_c = true; return op_c;
    }

    template<class T>
    vflog& operator<<(const T &txt)
    { if(okf) ofs<<txt; if(okc) std::cout<<txt; return *this; };
    vflog& operator<<(std::ostream& (*end)(std::ostream&))
    { if(okf) ofs<<cl; if(okc) std::cout<<cl; return *this; };
    vflog& operator<<(level el)
    {
        if(el <= el_f) ok_f = true; else ok_f = false;
        if(el <= el_c) ok_c = true; else ok_c = false;
        if(okf){ ofs<<vec[el]<<"] ["<<get_time()<<"] "; }
        if(okc){ std::cout<<vec[el]<<"] "; }
        return *this;
    };

private:
    vflog(){}
    ~vflog(){ if(ofs.is_open()) ofs.close(); };

    static vflog* obj;
    std::fstream ofs;
    std::string v_filename;

    bool oc_f = true;
    bool oc_c = true;
    bool op_f = false;
    bool op_c = false;
    bool ok_f = false;
    bool ok_c = false;
    level el_f;
    level el_c;

    std::string get_time()
    {
        time_t t; time(&t); char tmp[32];
        strftime(tmp,sizeof(tmp),"%Y-%m-%d %H:%M:%S",localtime(&t));
        return tmp;
    }
    class mcv { ~mcv(){delete obj; obj = nullptr;} }; static mcv t;
};
vflog* vflog::obj = nullptr;

//打印到文件
#define vloge \
    *vflog::instance()<<vflog::e_error\
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "

#define vlogw \
    *vflog::instance()<<vflog::e_warning\
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "

#define vlogd \
    *vflog::instance()<<vflog::e_debug\
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "

#define vlogf \
    *vflog::instance()<<vflog::e_info\
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "
//===== vflog =====

//模板打印--数组
template<class T>
void show_arr(const T vec,std::string flg = "#")
{
    std::cout<<"===== " +flg+ " ====="<<std::endl;
    for(size_t i = 0;i<vec.size();i++)
    {
        std::cout<<"["<<vec[i]<<"] ";
    }
    std::cout<<endl<<"---------- ----------"<<std::endl;
}

#endif // OPEN_CPP
//===== C++ =====

#endif // VLOG_H
