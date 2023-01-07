#include <iostream>
#define __NO_SHOW_VLOG__
#include <lib/vlog.hpp>
#include <lib/str_c.hpp>

void t_vlogf()
{
    vflog::instance()->init("test_vlogf.txt",vflog::e_info,false);
    vflog::instance()->init(vflog::e_info);

    for(int i=0;i<3;i++)
    { vloge<<"error:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogw<<"warning:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogd<<"debug:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogf<<"info:to txt form stdout"<<endl; }

    vlogf<<"==============="<<endl;
    vflog::instance()->init("tt2.txt",vflog::e_info,true);
    vflog::instance()->set_level(vflog::e_warning,vflog::e_warning);

    for(int i=0;i<3;i++)
    { vloge<<"error:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogw<<"warning:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogd<<"debug:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogf<<"info:to txt form stdout"<<endl; }

    vflog::instance()->init("test_vlogf.txt",vflog::e_info,true);
    vloge<<"==============="<<endl;
    vflog::instance()->set_level(vflog::e_info,vflog::e_info);

    for(int i=0;i<3;i++)
    { vloge<<"error:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogw<<"warning:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogd<<"debug:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogf<<"info:to txt form stdout"<<endl; }

    vloge<<"========close_log:false======="<<endl;
    vflog::instance()->close_log(false,false);
    for(int i=0;i<3;i++)
    { vloge<<"error:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogw<<"warning:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogd<<"debug:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogf<<"info:to txt form stdout"<<endl; }

    vflog::instance()->close_log(true,true);
    vloge<<"========close_log:true======="<<endl;
    for(int i=0;i<3;i++)
    { vloge<<"error:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogw<<"warning:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogd<<"debug:to txt form stdout"<<endl; }
    for(int i=0;i<3;i++)
    { vlogf<<"info:to txt form stdout"<<endl; }

}

void t_stm()
{
    using namespace std;
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

#include <vector>
#include <list>
void t_for()
{
    using namespace std;
    vector<string> vec;
    vec.push_back("012");
    vec.push_back("123");
    vec.push_back("234");
    vec.push_back("345");

    list<int> list;
    list.push_back(123);
    list.push_back(1234);
    list.push_back(12345);
    list.push_back(123456);

    cout<<"==========="<<endl;
    for_show(it,vec);
    cout<<"==========="<<endl;
    for_it(it,list) { cout<<*it<<endl; }
    cout<<"==========="<<endl;
}

void t_push()
{
    using namespace std;
    cout<<"1:====="<<endl;
    new_arr(vec,vector,int,1,12);
    for_show_p(it,vec);

    cout<<"2:====="<<endl;
    new_arr(lis,list,string,"aaa","bbb","ccc");
    for_show_p(it,lis);

    push_arr(vec,10,20,30);
    cout<<"3:====="<<endl;
    for_show_p(it,vec);

    push_arr(lis,"hellow","are you ok","no no no!!!");
    cout<<"4:====="<<endl;
    for_show_p(it,lis);

    cout<<"5:====="<<endl;
    op_dot<vector,double> op;
    op,3.14,33.11,3344;
    std::shared_ptr<vector<double>> sp_vec = op.get_arr();
    for(auto it=sp_vec->begin();it!=sp_vec->end();it++)
    { cout<<*it<<endl; }
}


#if 1
int main()
{
//    t_stm();//字符切割
//    t_vlogf();//测试文件日志
//    t_for();//循环宏
    t_push();//重载push类

    return 0;
}
#else

#endif

