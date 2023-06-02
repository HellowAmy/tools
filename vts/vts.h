#ifndef VTS_H
#define VTS_H


//=====
#define VOPEN_VLOG
#define VOPEN_STM
#define VOPEN_STMV
#define VOPEN_FOR
#define VOPEN_PUSH
#define VOPEN_TIME



//#define VLOG_CLOSE //开启此宏将取消所有注释--头文件之前定义
//=====

//===== vflog =====
#ifdef VOPEN_VLOG

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using std::endl;

namespace vts
{
//===== vts =====
#define cl "\033[0m"<<end
#define okc ok_c && op_c && oc_c
#define okf ok_f && op_f && oc_f

//说明:简单日志系统,可将日志同时输入到文件或控制台终端上
//      注意: 1、初始化之后可用,输入文件和输入终端需要分别初始化
//              终端: vinit_c 文件: vinit_f
//           2、文件输入可重定向到新文件,支持不同代码段分别输入不同文件内
//           3、支持日志四级等级: e_error,e_warning,e_debug,e_info
//           4、支持代码分段关闭功能,vstatus(false,true)可控制开启或者关闭输入
//           5、支持快速打印: 将变量与变量名追加到日志中
//                  string str = "are you ok";
//                  int value = 100;
//                  vloge("hellow world" vv(str) vv(value));
//
//init()参数说明:
//      [string filename:输出到的文件名路径]
//      [level el:输出等级,等级不足将无法输出]
//      [bool is_new:追加或者从零开始写入到文件]
//
class vlog
{
public:
    enum level{ e_error,e_warning,e_debug,e_info };
    static vlog* instance() { if(obj==nullptr){obj=new vlog;} return obj; };
    void set_level(level elf,level elc) { el_f=elf; el_c=elc; }
    void set_status(bool of,bool oc) { oc_f=of; oc_c=oc; }

    bool init(const std::string &filename,bool is_app = true,level el = e_info)
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
    vlog& operator<<(const T &txt)
    { if(okf) ofs<<txt; if(okc) std::cout<<txt; return *this; };
    vlog& operator<<(std::ostream& (*end)(std::ostream&))
    { if(okf) ofs<<cl; if(okc) std::cout<<cl; return *this; };
    vlog& operator<<(level el)
    {
        if(el <= el_f) ok_f = true; else ok_f = false;
        if(el <= el_c) ok_c = true; else ok_c = false;
        if(okf){ ofs<<vec[el]<<"] ["<<get_time()<<"] "; }
        if(okc){ std::cout<<vec[el]<<"] "; }
        return *this;
    };

private:
    explicit vlog();
    ~vlog(){ if(ofs.is_open()){ofs.close();} };

    bool oc_f = true;
    bool oc_c = true;
    bool op_f = false;
    bool op_c = false;
    bool ok_f = false;
    bool ok_c = false;
    level el_f;
    level el_c;

    static vlog* obj;
    std::fstream ofs;
    std::vector<std::string> vec;
    std::string v_filename;

    std::string get_time()
    {
        time_t t; time(&t); char tmp[32];
        strftime(tmp,sizeof(tmp),"%Y-%m-%d %H:%M:%S",localtime(&t));
        return tmp;
    }
    class mcv { ~mcv(){delete obj; obj = nullptr;} }; static mcv t;
};

//打印到文件

#ifdef VLOG_CLOSE

#define vloge(...)
#define vlogw(...)
#define vlogd(...)
#define vlogf(...)

#else

#define vloge(...) \
    *vlog::instance()<<vlog::e_error\
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl \

#define vlogw(...) \
    *vlog::instance()<<vlog::e_warning\
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl \

#define vlogd(...) \
    *vlog::instance()<<vlog::e_debug\
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl \

#define vlogf(...) \
    *vlog::instance()<<vlog::e_info\
    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl \

#endif

//==快速宏
#define vv(value) "["#value": "<<value<<"] " \

#define vl <<"|"<< \

#define vinit_f(filename,status,level) \
    vlog::instance()->init(filename,status,level) \

#define vinit_c(level) \
    vlog::instance()->init(level) \

#define vstatus(of,oc) \
    vlog::instance()->set_status(of,oc) \

#define vlevel(of,oc) \
    vlog::instance()->set_level(of,oc) \
//==快速宏

//===== vts =====
}
#endif //VOPEN_VLOG
//===== vflog =====







//===== stm =====
#ifdef VOPEN_STM

#include <string>
using std::string;

namespace vts
{
//===== vts =====

//功能:字符串切割,主要针对单字符串的多重切割,支持不同切割符号,支持正反双向切割
//算法:查找标记位置,向前取值,舍弃标记末尾数据
//用法示例:
//      [1]
//      string a = "1-22-333-4444-55555";
//      string b = "-";
//      cout<<"ret = "<<tools::stm(a)("-",0,2)<<endl;
//      [ret = 1-22-333]
//      cout<<"ret = "<<tools::stm(a)("-",-1,-1)<<endl;
//      [ret = 55555]
//      cout<<"ret = "<<tools::stm(a)("-",-3,-1)<<endl;
//      [ret = 333-4444-55555]
//
//      [2]
//      string a = "11--22--33ashgdas pas<<19911-12-3>>da asdg ausd";
//      string b = "--";
//      cout<<"ret = "<<tools::stm(a)(" ",1,1,"<<",1,-1,">>",0,0)<<endl;
//      [ret = 19911-12-3]
//
struct stm
{
    string v_str;
    stm(const string &str) : v_str(str){}

    template<class ...Tarr> string split_t(){ return v_str; }
    template<class ...Tarr>
    string split_t(const string &flg,int begin,int end,const Tarr &...arg)
    {
        if((begin < 0) && (end < 0)) v_str = split_back(v_str,flg,begin,end);
        else v_str = split_go(v_str,flg,begin,end);
        return split_t(arg...);
    }

    template<class ...Tarr>
    string operator()(const Tarr &...arg) { return split_t(arg...); }

    //反向切割:反向参数传递
    string split_back(const string &str,const string &flg, int end,int begin)
    {
        begin *= -1; begin -= 1; end *= -1;
        int len = end - begin;
        if((begin < 0) || (len <= 0)) return "";

        size_t pos_begin = str.size();
        for(int i=0;i<begin;i++)
        {
            if((pos_begin = str.rfind(flg,pos_begin)) == str.npos) return "";
            pos_begin -= 1;
        }

        size_t pos_end = pos_begin;
        for(int i=0;i<len;i++)
        {
            if((pos_end = str.rfind(flg,pos_end)) == str.npos) return "";
            pos_end -= 1;
        }

        if(pos_begin != str.size()) pos_begin += 1;
        pos_end += flg.size() +1;

        if(pos_begin <= pos_end) return "";
        return string (str.begin()+pos_end,str.begin()+pos_begin);
    }

    //正向切割:正向参数传递
    string split_go(const string &str,const string &flg, int begin,int end)
    {
        int len = (end - begin) + 1;
        if((begin < 0) || (len <= 0)) return "";

        size_t pos_begin = 0;
        for(int i=0;i<begin;i++)
        {
            if((pos_begin = str.find(flg,pos_begin)) == str.npos) return "";
            pos_begin += flg.size();
        }

        size_t pos_end = pos_begin;
        for(int i=0;i<len;i++)
        {
            if((pos_end = str.find(flg,pos_end)) == str.npos) return "";
            pos_end += flg.size();
        }

        pos_end -= flg.size();
        if(pos_begin >= pos_end) return "";
        return string(str.begin()+pos_begin,str.begin()+pos_end);
    }
};


//===== vts =====
}
#endif //VOPEN_STM
//===== stm =====


//===== stmv =====
#ifdef VOPEN_STMV

#include <string>
#include <vector>
#include <bitset>
using std::string;
using std::vector;

namespace vts
{
//===== vts =====

//功能:字符串切割,按分隔符将字符串切割到数组
//算法:利用vector<bool>生成与字符串一样长的标记位
//      切割算法扫描到切割符时将vector<bool>对应标记位置1(切割符占领位)
//      然后将连续0段加入结果数组
//用法示例:
//      [1]
//      string a = "11--22--33";
//      string b = "11--22++33";
//      string c = "11 22 33 44++55--66";
//      vector<string> vec = vts::stmv(a)("--");
//      [ret = 11,22,33]
//      vector<string> vec1 = vts::stmv(b)("--");
//      [ret = 11,22++33]
//      vector<string> vec2 = vts::stmv(c)(" ","++","--");
//      [ret = 11,22,33,44,55,66]
//
struct stmv
{
    string v_str;
    vector<string> vec_flg;
    vector<bool> vec_bit;

    stmv(const string &str) : v_str(str) { vec_bit.resize(str.size(),false); }

    template<class ...Tarr>
    vector<string> operator()(const Tarr &...arg) { return push_flg(arg...); }

    //获取切割符
    template<class ...Tarr> vector<string> push_flg()
    { return split_value(v_str,vec_flg); }
    template<class ...Tarr>
    vector<string> push_flg(const string &flg,Tarr ...arg)
    { vec_flg.push_back(flg); return push_flg(arg...); };

    //根据标记切割字符串
    vector<string> split_value(const string &in_str,const vector<string> &in_flg)
    {
        vector<string> vec;

        //标记数循环
        for(size_t iflg=0;iflg<in_flg.size();iflg++)
        {
            //字符串标记排查,存在用bit标记
            size_t pos_begin = 0;
            while(true)
            {
                pos_begin = in_str.find(in_flg[iflg],pos_begin);
                if(pos_begin != in_str.npos)
                {
                    for(size_t il=0;il<in_flg[iflg].size();il++)
                    { vec_bit[pos_begin+il]=1; }
                    pos_begin+=1;
                }
                else break;
            }
        }

        //根据0/1状态获取字符串,加入返回结果
        string str;
        for(size_t i=0;i<vec_bit.size();i++)
        {
            if(vec_bit[i] == false)
            {
                if(i>0 && (vec_bit[i-1] == true)) str.clear();
                str+=in_str[i];
            }
            else if(i>0 && (vec_bit[i-1] == false)) vec.push_back(str);
        }

        //末尾无状态转跳时加入结果
        if(vec_bit[vec_bit.size()-1] == false)
        { vec.push_back(str); }

        return vec;
    }
};


//===== vts =====
}
#endif //VOPEN_STM
//===== stm =====


//===== for =====
#ifdef VOPEN_FOR

//功能:直接打印(包括换行)或者提供快捷的for版本
//      提供对象版本和指针版本,后缀_p为指针版本
//for_show : 根据迭代器打印
//for_it : 返回迭代器自行操作
//for_i : 返回类型size_t的变量自行操作
//for_n : 制定执行循环次数,不希望返回迭代器
#define for_show(arr) \
    for(auto it=arr.begin();it!=arr.end();it++) \
    { std::cout<<*it<<std::endl; }
#define for_show_p(arr) \
    for(auto it=arr->begin();it!=arr->end();it++) \
    { std::cout<<*it<<std::endl; }

#define for_it(it,arr) \
    for(auto it=arr.begin();it!=arr.end();it++)
#define for_it_p(it,arr) \
    for(auto it=arr->begin();it!=arr->end();it++)

#define for_i(i,arr) \
    for(size_t i=0;i<arr.size();i++)

#define for_n(n) \
    for(size_t index_it_for=0;index_it_for<n;index_it_for++)

#endif //VOPEN_FOR
//===== for =====


//===== time =====
#ifdef VOPEN_TIME

#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

namespace vts
{

//!
//! 说明：主要用于计算函数运行的时间，测试函数性能
//!         steady_clock时间：精确到纳秒的均速时间
//!
//! 例子：
//!     {
//!         ctimel tm;
//!         func();
//!     }//到这里析构退出并打印时间
//!
//! 原理：构建对象时开始计时，析构时打印时间
//!
class ctimel
{
public:
    ctimel() { _begin = steady_clock::now(); }
    ~ctimel() { show(); }

    inline string to_str()
    {
        //顺序 [纳秒|微秒|毫秒|秒]
        auto loss = steady_clock::now() - _begin;
        string str =
                "[nan: " + std::to_string(loss.count()) +
                "|mic: " + std::to_string(duration_cast<microseconds>(loss).count()) +
                "|mil: " + std::to_string(duration_cast<milliseconds>(loss).count()) +
                "|sec: " + std::to_string(duration_cast<seconds>(loss).count()) +
                "]\n";
        return str;
    }

    inline void show_str(const string str) { cout<<str<<endl; }
    inline void show() { show_str(to_str()); }
    inline void update() { _begin = steady_clock::now(); }

protected:
    time_point<steady_clock,nanoseconds> _begin;
};

/*
class ctimel
{
public:
    ctimel() { _begin = steady_clock::now(); }
    ~ctimel() { show(); }

    inline void show()
    {
        //顺序 [纳秒|微秒|毫秒|秒]
        auto loss = steady_clock::now() - _begin;
        std::cout<<"[nan: "<<loss.count()
                <<"|mic: "<<duration_cast<microseconds>(loss).count()
               <<"|mil: "<<duration_cast<milliseconds>(loss).count()
              <<"|sec: "<<duration_cast<seconds>(loss).count()
             <<"]"<<std::endl;
    }

    inline void update() { _begin = steady_clock::now(); }

protected:
    time_point<steady_clock,nanoseconds> _begin;
};
*/

//!
//! 显示可视化的时间
//!
class ctimes
{
public:
    //现在的时间点-可视化
    string date_now(const string &format = "%Y-%m-%d %H:%M:%S")
    {
        char ret[1024];
        time_t t = system_clock::to_time_t(system_clock::now());
        strftime(ret,sizeof(ret),format.c_str(),localtime(&t));
        return ret;
    }

    //格式化时间-可视化
    string to_format(const time_t &t, const string &format = "%Y-%m-%d %H:%M:%S")
    {
        char ret[1024];
        strftime(ret,sizeof(ret),format.c_str(),localtime(&t));
        return ret;
    }
    time_t time_now(){ time_t t; return time(&t); };//当前时间
};


}
#endif //VOPEN_TIME
//===== time =====


#endif // VTS_H
