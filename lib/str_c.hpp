#ifndef STR_C_HPP
#define STR_C_HPP

#include <string>
using std::string;

namespace tools
{
//===== namespace tools =====


//===== struct st =====
//功能:字符串切割,主要针对单字符串的多重切割
//算法:查找标记位置,向前取值,舍弃标记末尾数据
//用法:
//      string a = "11--22--33--44--55--66--77--88--99";
//      string b = "--";
//      cout<<"ret = "<<st(a,b)(0,5,1,3,1,2)<<endl;
//      cout<<"ret = "<<st(a,b)(0,5,1,4,0,1)<<endl;
//      [ret = 22--33]
struct st
{
    string v_str;
    string v_flg;

    template<class ...Tarr>
    st(string str,string flg) : v_str(str),v_flg(flg){}

    template<class ...Tarr> string split_t(){ return v_str; }
    template<class ...Tarr>
    string split_t(int begin,int end,Tarr ...arg)
    {
        string ret = split_s(v_str,v_flg,begin,end);
        v_str = ret;
        return split_t(arg...);
    }

    template<class ...Tarr>
    string operator()(Tarr ...arg) { return split_t(arg...); }

    string split_s(const string &str,const string &flg, int begin,int end)
    {
        if((begin < 0 || end < 0) && (end >= begin)) return "";

        size_t pos_begin = 0;
        for(int i=0;i<begin;i++)
        {
            if((pos_begin = str.find(flg,pos_begin)) == str.npos) return "";
            pos_begin += flg.size();
        }

        size_t len = (end - begin) +1;

        size_t pos_end = pos_begin;
        for(int i=0;i<(int)len;i++)
        {
            if((pos_end = str.find(flg,pos_end)) == str.npos) return "";
            pos_end += flg.size();
        }

        pos_end -= flg.size();
        string temp(str.begin()+pos_begin,
                    str.begin()+pos_end);
        return temp;
    }
};
//===== struct st =====



//===== namespace tools =====
}

#endif // STR_C_HPP
