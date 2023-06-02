#ifndef TVLOG_H
#define TVLOG_H

#include <iostream>
#include <mutex>

//== 单例模板 ==
template<class T>
class Tsingle_d
{
public:
    static T* get()
    {
        if(_obj == nullptr)
        {
            _mut.lock();
            if(_obj == nullptr) { _obj = new T; }
            _mut.unlock();
        }
        return _obj;
    }

    void clean()
    {
        _mut.lock();
        delete _obj; _obj = nullptr;
        _mut.unlock();
    }

private:
    static T *_obj;
    static std::mutex _mut;
    friend T;
    Tsingle_d() = default;
    ~Tsingle_d() = default;
    Tsingle_d(const Tsingle_d &) = delete ;
};

template<class T> T *Tsingle_d<T>::_obj = nullptr;
template<class T> std::mutex Tsingle_d<T>::_mut;
//== 单例模板 ==


//== 等级 ==
namespace level4
{ enum level{ e_error,e_warning,e_debug,e_info }; }

namespace level8
{ enum level{ e_off,e_fatal,e_error,e_warning,e_debug,e_trace,e_all }; }
//== 等级 ==


//== 日志模板 ==
//提供等级自定义模板参数
template<class Tlevel>
class Tvlog
{
public:
    void set_level(Tlevel el){ _level = el; } //设置等级

    inline Tvlog& operator<<(Tlevel el)
    { if(el <= _level) _ok = true; return *this; };

    inline Tvlog& operator<<(std::ostream& (*end)(std::ostream&))
    { if(_ok) std::cout<<end; return *this; };

    template<class T>
    inline Tvlog& operator<<(const T &log)
    { if(_ok) std::cout<<log; return *this; };

private:
    bool _ok = false;   //判断等级是否符合
    Tlevel _level;      //最低显示的等级
};

//== 容器打印格式 ==
//参数：容器
#define $v1(vec)                                        \
{                                                       \
    cout<<"===== "#vec":"<<vec.size()<<" ====="<<endl;  \
    for(const auto &a:vec)                              \
    {                                                   \
        cout<<a<<" ";                                   \
    }                                                   \
    cout<<endl;                                         \
    cout<<"===== ====="<<endl;                          \
}                                                       \

//参数：容器，换行数量
#define $v2(vec,count)                                  \
{                                                       \
    cout<<"===== "#vec":"<<vec.size()<<" ====="<<endl;  \
    size_t i=0;                                         \
    for(const auto &a:vec)                              \
    {                                                   \
        cout<<"["<<a<<"] ";                             \
        i++;                                            \
        if(i%count == 0&&i!=vec.size()) cout<<endl;     \
    }                                                   \
    cout<<endl;                                         \
    cout<<"===== ====="<<endl;                          \
}                                                       \

//参数：容器，换行数量，左分割符，右分割符
#define $v3(vec,count,left,right)                       \
{                                                       \
    cout<<"===== "#vec":"<<vec.size()<<" ====="<<endl;  \
    size_t i=0;                                         \
    for(const auto &a:vec)                              \
    {                                                   \
        cout<<left<<a<<right<<" ";                      \
        i++;                                            \
        if(i%count == 0&&i!=vec.size()) cout<<endl;     \
    }                                                   \
    cout<<endl;                                         \
    cout<<"===== ====="<<endl;                          \
}                                                       \

//参数：容器，开始迭代器，结束迭代器
#define $v4(vec,begin,end)                              \
{                                                       \
    cout<<"===== "#vec":"<<vec.size()<<" ====="<<endl;  \
    for(auto it=begin;it!=end;it++)                     \
    {                                                   \
        cout<<"["<<*it<<"] ";                           \
    }                                                   \
    cout<<endl;                                         \
    cout<<"===== ====="<<endl;                          \
}                                                       \

//参数：打印的值
#define $1(value) "["#value": "<<value<<"] "

//参数：$v的容器打印，$v的参数
#define vlogc(func,...)                                                 \
    *Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_error     \
    <<"[Con]["<<__FILE__<<":<"<<__LINE__<<">]"<<endl;                   \
    func(__VA_ARGS__)


//== 快捷打印 ==
#define vlevel(type,el)                                                     \
    Tsingle_d<Tvlog<type::level>>::get()->set_level(type::level::el);       \

#define vlogi(...)                                                          \
    *Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_info          \
    <<"[Inf]["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl     \

#define vlogd(...)                                                          \
    *Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_debug         \
    <<"[Deb]["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl     \

#define vlogw(...)                                                          \
    *Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_warning       \
    <<"[War]["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl     \

#define vloge(...)                                                          \
    *Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_error         \
    <<"[Err]["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl     \


//Tsingle_d<Tvlog<level4::level>>::get()->set_level(level4::level::e_info);

//*Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_info<<"12341"<<endl;
//*Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_warning<<546777<<endl;


//#define vloge(...) \
//    *vlog::instance()<<vlog::e_error\
//    <<"["<<__FILE__<<":<"<<__LINE__<<">] <<<< "<<__VA_ARGS__<<endl \


//== 日志模板 ==

#endif // TVLOG_H
