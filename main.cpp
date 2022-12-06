#include <iostream>

#include <lib/vlog.hpp>
#include <lib/str_c.hpp>

using namespace std;

void t_log()
{
    vlog<<"hellow world"<<endl;
    vlog<<"===== end ====="<<endl;
}

void t_st()
{
    string a = "11--22--33--44--55--66--77--88--99";
    string b = "--";
    cout<<"ret = "<<tools::st(a,b)(0,5,1,4,0,1)<<endl;
}


int main()
{

    t_log();//测试日志
    t_st();//字符切割

    return 0;
}
