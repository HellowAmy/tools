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
class vflog
{
protected:
    std::vector<std::string> vec
    { "\033[31m[Error","\033[33m[Warning","\033[32m[Debug","[Info" };
public:
    enum level{ e_error,e_warning,e_debug,e_info };
    static vflog* instance() { if(obj == nullptr) obj = new vflog; return obj; };
    bool init(std::string filename,level el = e_info,bool is_app = true)
    {
        if(is_open) return false;
        is_open = true; v_el = el;
        if(is_app) ofs.open(filename,std::ios::out);
        else ofs.open(filename,std::ios::out | std::ios::app);
        if(ofs.is_open()) return true;
        return false;
    }
    bool init(level el = e_info)
    {
        if(is_open) return false;
        is_open = true; is_cout = true; v_el = el;
        return true;
    }

    template<class T>
    vflog& operator<<(const T &txt)
    { if(is_write) {if(is_cout) std::cout<<txt; else ofs<<txt;}return *this; };
    vflog& operator<<(std::ostream& (*end)(std::ostream&))
    { if(is_write) {if(is_cout) std::cout<<cl; else ofs<<cl;}return *this; };
    vflog& operator<<(level el)
    {
        if(el <= v_el) is_write = true; else is_write = false;
        if(is_write)
        {
            if(is_cout) { std::cout<<vec[el]<<"] "; }
            else { ofs<<vec[el]<<"] ["<<get_time()<<"] "; }
        }
        return *this;
    };

private:
    vflog(){}
    ~vflog(){ if(is_cout == false) ofs.close(); };

    static vflog* obj;
    std::fstream ofs;
    bool is_write = false;
    bool is_open = false;
    bool is_cout = false;
    level v_el;

    std::string get_time()
    {
        time_t t; time(&t); char tmp[32];
        strftime(tmp,sizeof(tmp),"%Y-%m-%d %H:%M:%S",localtime(&t));
        return tmp;
    }
    class mcv { ~mcv(){delete obj; obj = nullptr;} }; static mcv t;
};
vflog* vflog::obj = nullptr;

#define vlog_init(filename) vflog::instance()->init(filename)

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
