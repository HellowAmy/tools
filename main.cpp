#include <iostream>
#include <vts/vts.h>

#include "a.h"
#include "b.h"

using namespace std;

#if 1
void t_vlogf()
{
    using namespace vts;


    vinit_f("test_vlogf.txt",false,vlog::e_info);
    vinit_c(vlog::e_info);

    int value =100;
    string str = "i am red";
    for(int i=0;i<3;i++)
    { vloge("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }

    vloge("=====================================");
    vinit_f("tt2.txt",true,vlog::e_info);
    vlevel(vlog::e_warning,vlog::e_warning);

    for(int i=0;i<3;i++)
    { vloge("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }

    vinit_f("test_vlogf.txt",true,vlog::e_info);
    vloge("=====================================");
    vlevel(vlog::e_info,vlog::e_info);

    for(int i=0;i<3;i++)
    { vloge("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }

    vloge("=====================================");
    vstatus(false,false);

    for(int i=0;i<3;i++)
    { vloge("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }

    vstatus(true,true);
    vloge("=====================================");

    for(int i=0;i<3;i++)
    { vloge("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: "<<v(value) v(str) l 3.14 l 1234 l "asd"); }

}
#endif

#if 1
void t_stm()
{
    using namespace std;
    string a = "1-22-333-4444-55555";
    cout<<"ret = "<<vts::stm(a)("-",0,2)<<endl;
    //[ret = 1-22-333]
    cout<<"ret = "<<vts::stm(a)("-",-1,-1)<<endl;
    //[ret = 55555]
    cout<<"ret = "<<vts::stm(a)("-",-3,-1)<<endl;
    //[ret = 333-4444-55555]

    string a1 = "11--22--33ashgdas pas<<1991-12-3>>da asdg ausd";
    cout<<"ret = "<<vts::stm(a1)(" ",1,1,"<<",-1,-1,">>",0,0)<<endl;
    //[ret = 19911-12-3]
}
#endif

#if 1
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
    for_show(vec);
    cout<<"==========="<<endl;
    for_it(it,list) { cout<<*it<<endl; }
    cout<<"==========="<<endl;
    for_i(i,list) { cout<<vec[i]<<endl; }
    cout<<"==========="<<endl;
    for_n(3) { cout<<"for_n"<<endl; }
    cout<<"==========="<<endl;
}
#endif

#if 1
#include <vector>
#include <list>
void t_push()
{
    using namespace std;
    using namespace vts;

    cout<<"1:====="<<endl;
    new_arr(vec,vector,int,1,12);
    for_show_p(vec);

    cout<<"2:====="<<endl;
    new_arr(lis,list,string,"aaa","bbb","ccc");
    for_show_p(lis);

    push_arr(vec,10,20,30);
    cout<<"3:====="<<endl;
    for_show_p(vec);

    push_arr(lis,"hellow","are you ok","no no no!!!");
    cout<<"4:====="<<endl;
    for_show_p(lis);

    cout<<"5:====="<<endl;
    op_dot<vector,double> op;
    op,3.14,33.11,3344;
    std::shared_ptr<vector<double>> sp_vec = op.get_arr();
    for(auto it=sp_vec->begin();it!=sp_vec->end();it++)
    { cout<<*it<<endl; }
}
#endif


int main()
{
    A aa;
    B bb;

    t_vlogf();
    t_stm();
    t_for();
    t_push();

    cout << "Hello World!" << endl;
    return 0;
}
