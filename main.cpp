#include <iostream>

#include <lib/vlog.hpp>
#include <lib/str_c.hpp>

using namespace std;

void t_log()
{
    vlog<<"hellow world"<<endl;
    vlog<<"===== end ====="<<endl;
}

void t_stm()
{
    string a = "1-22-333-4444-55555";
    cout<<"ret = "<<tools::stm(a)("-",0,2)<<endl;
    //[ret = 1-22-333]
    cout<<"ret = "<<tools::stm(a)("-",-1,-1)<<endl;
    //[ret = 55555]
    cout<<"ret = "<<tools::stm(a)("-",-3,-1)<<endl;
    //[ret = 333-4444-55555]

    string a1 = "11--22--33ashgdas pas<<1991-12-3>>da asdg ausd";
    cout<<"ret = "<<tools::stm(a1)(" ",1,1,"<<",-1,-1,">>",0,0)<<endl;
    //[ret = 19911-12-3]
}


#if 1
int main()
{

    t_log();//测试日志
    t_stm();//字符切割

    return 0;
}
#else

#endif

