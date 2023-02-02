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
    { vloge("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }

#if 1
    vloge("=====================================");
    vinit_f("tt2.txt",true,vlog::e_info);
    vlevel(vlog::e_warning,vlog::e_warning);

    for(int i=0;i<3;i++)
    { vloge("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }

    vinit_f("test_vlogf.txt",true,vlog::e_info);
    vloge("=====================================");
    vlevel(vlog::e_info,vlog::e_info);

    for(int i=0;i<3;i++)
    { vloge("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }

    vloge("=====================================");
    vstatus(false,false);

    for(int i=0;i<3;i++)
    { vloge("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }

    vstatus(true,true);
    vloge("=====================================");

    for(int i=0;i<3;i++)
    { vloge("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogw("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogd("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
    for(int i=0;i<3;i++)
    { vlogf("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
#endif
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
#include <fstream>
void t_stmv()
{
#if 0
    using namespace std;
    string a = "11--22--33ashgdas pas<<1991-12-3>>da asdg ausd";
    string b = "--11--22--33ashgdas pas<<1991-12-3>>da asdg ausd";
    string c = "11--22--33ashgdas pas<<1991-12-3>>da asdg ausd--";
    string d = "--11--22--33ashgdas pas<<1991-12-3>>da asdg ausd ";
    string e = "ajkwjfajknfjabcwjiabfjawabcabwfiagalkfabc";
    vector<string> vec = vts::stmv(a)("--");
    vector<string> vec1 = vts::stmv(b)("--"," ");
    vector<string> vec2 = vts::stmv(c)("--"," ","<<");
    vector<string> vec3 = vts::stmv(d)("--"," ","<<",">>");
    vector<string> vec4 = vts::stmv(e)("abc","ab");

    cout<<"========"<<endl;
    for_show(vec);

    cout<<"========"<<endl;
    for_show(vec1);

    cout<<"========"<<endl;
    for_show(vec2);

    cout<<"========"<<endl;
    for_show(vec3);

    cout<<"========"<<endl;
    for_show(vec4);

    cout<<"========"<<endl;
    cout<<vec.size()<<"|"<<vec1.size()<<"|"<<vec2.size()<<"|"<<vec3.size()<<endl;
#endif

#if 1
    fstream ofs("/home/red/test/inventory.vmls");
    if(ofs.is_open())
    {
        string str;
        while (getline(ofs,str))
        {
            cout<<"==============="<<endl;
            cout<<str<<endl;
            vector<string> vec = vts::stmv(str)("."," = ","\"");
            for_show(vec);
        }
        ofs.close();
    }
#endif

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

template<class T,typename _Alloc = std::allocator<T>>
class AAP
{
public:

    void pos(T&& ){};
};

#if 1
#include <vector>
#include <list>
void t_push()
{
    using namespace std;
    using namespace std::placeholders;
    using namespace vts;

//    cout<<"1:====="<<endl;
//    new_arr(vec,vector,int,1,12);
//    for_show_p(vec);

//    cout<<"2:====="<<endl;
//    new_arr(lis,list,string,"aaa","bbb","ccc");
//    for_show_p(lis);

//    push_arr(vec,10,20,30);
//    cout<<"3:====="<<endl;
//    for_show_p(vec);

//    push_arr(lis,"hellow","are you ok","no no no!!!");
//    cout<<"4:====="<<endl;
//    for_show_p(lis);

//    cout<<"5:====="<<endl;
//    op_dot<vector,double> op;
//    op,3.14,33.11,3344;
//    std::shared_ptr<vector<double>> sp_vec = op.get_arr();
//    for(auto it=sp_vec->begin();it!=sp_vec->end();it++)
//    { cout<<*it<<endl; }



//    vec4.push_back("124");
    //const value_type& __x


    // T 是模板声明
    //类成员声明： void pos(T&& po){};
//    AAP<string> po;
//    auto tre = &AAP<string>::pos;

    // value_type 是模板声明
    //类成员声明： void push_back(value_type&& __x)
//    vector<string> vec;
//    vec.push_back("1241");
//    auto vec_func = &std::vector<string>::push_back;

//    list<string> li;
//    li.push_back("14212");
//    auto vec_funcll = &std::list<string>::push_back;


//    po.pos("124124");
//    cout<<typeid(tre)<<endl;
//    auto func = bind(&AAP<string>::pos,po,_1);
//    bind(&vector<string>::push_back,vec4,_1);

//    template<typename _Tp, typename _Alloc = std::allocator<_Tp> >


//    auto func2 =
//            bind(&vector<int>::push_back,vec4,412);

//    op_dot<vector,double> op(bind(&vector<string>::push_back,vec,"412");
}
#endif


#include <typeindex>

int main()
{
    A aa;
    B bb;


//    int value =294;
//    double bbg = 3.14541;
//    auto ji =bbg;
//    ji::
//    ji::type_info::name();
//    cout<<typeid (value).type_info::name()<<endl;
//    cout<<typeid (bbg).name()<<endl;

//    t_vlogf();
//    t_stm();
    t_stmv();
//    t_for();
//    t_push();

    cout << "Hello World!" << endl;
    return 0;
}
