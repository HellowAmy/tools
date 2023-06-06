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

#define VLOG_COLOR
#include "Tvlog.h"
#include <vector>
#include <list>

void t_Tvlog()
{
    Tsvlog::get()->set_level(level4::level::e_info); //日志等级

    //普通打印
    vloge("== 普通打印 ==");
    vlogi("e_info level");
    vlogd("this template log");
    vlogd("10+20 ret: " << 10+20);
    vlogw("PI: "<<3.14);
    vloge("2^4 calculate: "<<2*2<<" * "<<2*2<<" = "<<4*4);
    vloge("2^4 calculate:" $1(2*2) $1(2*2) "=" $1(4*4));

    //快速打印结果
    vloge("== 快速打印 ==");
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
    vloge("== 容器打印--宏 ==");
    vlogc($v1,ls);                              //打印容器
    vlogc($v2,ls,4);                            //打印容器，带换行
    vlogc($v3,vec,vec.begin()+2,vec.end()-2);   //打印容器，指定迭代器范围
    vlogc($v4,vec,3,"[","]");                   //打印容器，制定分界符

    vloge("== 容器打印--模板 ==");
    {
        vector<int> vec;
        for(int i=0;i<25;i++)
        {
            vec.push_back(i);
        }
        vlogp(vec);
        vlogp(vec,5);
        vlogp(vec,5,"][");
        vlogp(vec.begin(),vec.end(),5);
        vlogp(vec.begin(),vec.end(),5,".");
    }

    int ifor = 1000000;

#if 0
    {
        vts::ctimel c;
        for(int i=0;i<ifor;i++)
        {
            vlogi($1(i) "hellow world");
        }
        string s1 = c.to_str();
        int value=100;
        string s = "hellow world";
        for(int i=0;i<ifor;i++)
        {
            vlogi($1(i) $1(value) $1(s));
        }
        string s2 = c.to_str();
    }
#endif

#if 0
    {
        vts::ctimel c;
        for(int i=0;i<ifor;i++)
        {
            cout<<i<<": hellow world"<<endl;
        }
        string s1 = c.to_str();
        int value=100;
        string s = "hellow world";
        for(int i=0;i<ifor;i++)
        {
            cout<<i<<": value:"<<value<<" | s:"<<s<<endl;
        }
        string s2 = c.to_str();
    }
#endif

#if 0
    {
        vts::ctimel c;
        for(int i=0;i<ifor;i++)
        {
            printf("%d: hellow world\n",i);
        }
        string s1 = c.to_str();
        int value=100;
        const char *s = "hellow world";
        for(int i=0;i<ifor;i++)
        {
            printf("%d: value: %d| s: %s\n",i,value,s);
        }
        string s2 = c.to_str();
    }
#endif

}

void t_Tflog()
{
    Tsflog::get()->init("Tflog.log",false);
    Tsflog::get()->set_level(level4::level::e_debug);
    Tsflog::get()->set_limit(5);

    //普通打印
    floge("== 普通打印 ==");
    flogi("e_info level");
    flogd("this template log");
    flogd("10+20 ret: " << 10+20);
    flogw("PI: "<<3.14);
    floge("2^4 calculate: "<<2*2<<" * "<<2*2<<" = "<<4*4);
    floge("2^4 calculate:" $1(2*2) $1(2*2) "=" $1(4*4));

    //快速打印结果
    floge("== 快速打印 ==");
    int count = 0;
    for(int i=0;i<=100;i++) count += i;
    string str = "hello world";
    int ret = 10*60;
    flogd($1(str) $1(ret) $1(count));

    int ifor = 1000000;

#if 0
    {
        vts::ctimel c;
        for(int i=0;i<ifor;i++)
        {
            flogw($1(i) "hellow world");
        }
        string s1 = c.to_str();
        int value=100;
        string s = "hellow world";
        for(int i=0;i<ifor;i++)
        {
            flogw($1(i) $1(value) $1(s));
        }
        string s2 = c.to_str();
    }
#endif
}


//vlog:
//[nan: 7189842803|mic: 7189842|mil: 7189|sec: 7]
//[nan: 7165359528|mic: 7165359|mil: 7165|sec: 7]
//[nan: 7169156501|mic: 7169156|mil: 7169|sec: 7]

//cout:
//[nan: 4834558776|mic: 4834558|mil: 4834|sec: 4]
//[nan: 4898849502|mic: 4898849|mil: 4898|sec: 4]
//[nan: 4793082020|mic: 4793082|mil: 4793|sec: 4]

//print:
//[nan: 4714220664|mic: 4714220|mil: 4714|sec: 4]
//[nan: 4750219105|mic: 4750219|mil: 4750|sec: 4]
//[nan: 4736075373|mic: 4736075|mil: 4736|sec: 4]





//vlogi     -- [nan: 1840431518|mic: 1840431|mil: 1840|sec: 1]
//cout      -- [nan: 743386933|mic: 743386|mil: 743|sec: 0]
//printf    -- [nan: 902455603|mic: 902455|mil: 902|sec: 0]


//cout
//[nan: 2025252118|mic: 2025252|mil: 2025|sec: 2]
//[nan: 2004377021|mic: 2004377|mil: 2004|sec: 2]
//[nan: 2091675392|mic: 2091675|mil: 2091|sec: 2]
//[nan: 5899699028|mic: 5899699|mil: 5899|sec: 5]
//[nan: 5296568542|mic: 5296568|mil: 5296|sec: 5]
//[nan: 4606000975|mic: 4606000|mil: 4606|sec: 4]




int main()
{





    A aa;
    B bb;

//    t_vlogf();
//    t_stm();
//    t_stmv();
//    t_for();
//    t_timel();
    t_Tvlog();
    t_Tflog();





    cout<<"===== end ====="<<endl;
    return 0;
}
