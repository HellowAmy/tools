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
    cout<<"ret = "<<vts::stm("1-22-333-4444-55555")("-",0,2)<<endl;
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
#if 1
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
#include <unistd.h>
void t_timel()
{
    {
        auto func = [](){
            for(size_t i=0;i<400000000;i++) {}
        };

        vts::ctimel tm;
        func();
        tm.show();

        func();
        tm.show();

        tm.update();
        sleep(1);
    }

    {
        //!
        //! 日志的性能测试
        //!
        //! vloge得分：
        //! [nan: 816759775|mic: 816759|mil: 816|sec: 0]
        //!
        //! cout得分：
        //! [nan: 96010909|mic: 96010|mil: 96|sec: 0]
        //!
        //! printf得分：与cout不相上下
        //! [nan: 107381042|mic: 107381|mil: 107|sec: 0]
        //!
        //! 总结：这个多功能日志非常消耗性能
        //!
        using namespace vts;
        ctimel tm;

        int value =100;
        string str = "i am red";
#if 1
        for(int i=0;i<3000;i++)
        { cout<<"to txt: "<<value<<str<<endl; }
        for(int i=0;i<3000;i++)
        { cout<<"to txt: "<<value<<str<<endl; }
        for(int i=0;i<3000;i++)
        { cout<<"to txt: "<<value<<str<<endl; }
        for(int i=0;i<3000;i++)
        { cout<<"to txt: "<<value<<str<<endl; }

//        for(int i=0;i<3000;i++)
//        { printf("to txt: %d %s\n",value,str.c_str()); }
//        for(int i=0;i<3000;i++)
//        { printf("to txt: %d %s\n",value,str.c_str()); }
//        for(int i=0;i<3000;i++)
//        { printf("to txt: %d %s\n",value,str.c_str()); }
//        for(int i=0;i<3000;i++)
//        { printf("to txt: %d %s\n",value,str.c_str()); }

#else
        vinit_f("test_vlogf.txt",false,vlog::e_info);
        vinit_c(vlog::e_info);
        for(int i=0;i<3000;i++)
        { vloge("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
        for(int i=0;i<3000;i++)
        { vlogw("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
        for(int i=0;i<3000;i++)
        { vlogd("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
        for(int i=0;i<3000;i++)
        { vlogf("to txt: " vv(value) vv(str) vl 3.14 vl 1234 vl "asd"); }
#endif
        cout<<"== vlog time test =="<<endl;
    }


    cout<<"== ctimes =="<<endl;
    vts::ctimes ct;
    cout<<ct.date_now()<<endl;
    cout<<ct.date_now("%H:%M:%S")<<endl;
    time_t t1 = ct.time_now();
    cout<<ct.to_format(t1)<<endl;
}

#endif


#include "Tvlog.h"
#include <vector>
#include <list>



//"["#value": "<<value<<"] "
void t_Tvlog()
{
    vlevel(level4,e_debug); //等级

    //普通打印
    vloge("== 普通打印 ==");
    vlogi("e_info level");
    vlogd("this template log");
    vlogd("10+20 ret: " << 10+20);
    vlogw("PI: "<<3.14);
    vloge("2^4 calculate: "<<2*2<<" * "<<2*2<<" = "<<4*4);

    //快速打印结果
    vloge("== 快速打印结果 ==");
    int count = 0;
    for(int i=0;i<=100;i++) count += i;
    string str = "hello world";
    int ret = 10*60;
    vlogd($1(str) $1(ret) $1(count));

    //容器打印
    vector<string> vec;
    list<string> ls;
    for(int i=0;i<10;i++)
    {
        vec.push_back("vec:"+to_string(i));
        ls.push_back("ls:"+to_string(i));
    }
    vlogc($v1,vec);
    vlogc($v2,vec,4);
    vlogc($v3,vec,3,"[","]");
    vlogc($v4,vec,vec.begin()+2,vec.end()-2);
    vlogc($v2,ls,5);
    vlogc($v2,ls,6);


//    {
//        int i = 0;
//        cout<<"===== ====="<<endl;
//        for(const auto &a:vec)
//        {
//            cout<<"["<<a<<"] ";
//            i++;
//            if(i == 5) cout<<endl;
//        }
//        cout<<endl;
//        cout<<"===== ====="<<endl;
//    }

//    {
//        int i = 0;
//        cout<<"===== ====="<<endl;
//        for(const auto &a:ls)
//        {
//            cout<<"["<<a<<"] ";
//            i++;
//            if(i == 5) cout<<endl;
//        }
//        cout<<endl;
//        cout<<"===== ====="<<endl;
//    }


//    if()








}

int main()
{

//    Tsingle_d<Tvlog<level4::level>>::get()->set_level(level4::level::e_info);
//    *Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_info<<"12341"<<endl;
//    *Tsingle_d<Tvlog<level4::level>>::get()<<level4::level::e_warning<<546777<<endl;


    A aa;
    B bb;

//    t_vlogf();
//    t_stm();
//    t_stmv();
//    t_for();
//    t_timel();
    t_Tvlog();

    cout << "Hello World!" << endl;
    return 0;
}
