#include "scan_op.h"



//===== stmv =====
//功能:字符串切割,按分隔符将字符串切割到数组
//算法:利用vector<bool>生成与字符串一样长的标记位
//      切割算法扫描到切割符时将vector<bool>对应标记位置1(切割符占领位)
//      然后将连续0段加入结果数组
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
        //标记数循环
        vector<string> vec;
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
//===== stmv =====



scan_op::scan_op()
{

}

void scan_op::open_scan()
{
    thread (system,_cmd.c_str()).detach();
    observe_op();
}

void scan_op::observe_op()
{
    //监控文件
    FILE *fd = fopen(_log.c_str(),"r");
    if(fd)
    {
        //跳过历史内容
        char buf[1024];
        while(fgets(buf,sizeof(buf),fd) != NULL){}

        //开始监控
        while (_run)
        {
            //读取新数据
            while(fgets(buf,sizeof(buf),fd) != NULL)
            {
                less_enter(buf);
                string str = buf;
                if(filter_op(str))
                {
                    watch_op(str);
                }
            }
        }
        fclose(fd);
    }
}

bool scan_op::filter_op(const string &str)
{
    //重复事件过滤
    static string str_old;
    if(str == str_old) return false;

    //垃圾信息筛选
    //筛选信息内容不包含: ".Trash-1000/*/|OPEN,ISDIR|*.swp|*.swx|*.txt~"
    {
        string reg = "/.Trash-(.*)/";
        try { if(regex_search(str,regex(reg))) return false; }
        catch (...) { return false; }
    }
    {
        string reg = "OPEN,ISDIR";
        try { if(regex_search(str,regex(reg))) return false; }
        catch (...) { return false; }
    }
    {
        string reg = "(.*.swp)";
        try { if(regex_search(str,regex(reg))) return false; }
        catch (...) { return false; }
    }
    {
        string reg = "(.*.swx)";
        try { if(regex_search(str,regex(reg))) return false; }
        catch (...) { return false; }
    }
    {
        string reg = "(.*.txt~)";
        try { if(regex_search(str,regex(reg))) return false; }
        catch (...) { return false; }
    }
    {
        string reg = "4913";
        try { if(regex_search(str,regex(reg))) return false; }
        catch (...) { return false; }
    }

    str_old = str;
    return true;
}

void scan_op::less_enter(char *buf)
{
    for(size_t i=0;i<strlen(buf);i++)
    {
        if(buf[i] == '\n')
        { buf[i] = '\0'; return; }
    }
}

//        if(ch_txt == 1)
//        {
//            ch_txt = 0;
//            cout<<"== 修改内容 =="<<endl;
//        }
//        else if(ch_name == 1)
//        {
//            ch_name = 0;
//            cout<<"重命名: "<<str_ch_name<<" >> "<<name<<endl;
//        }

bool scan_op::watch_op(const string &str)
{
    //解析信息
    auto vec = stmv(str)("    ");
    if(vec.size() < 4) return false;
    string time = vec[0];
    string path = vec[1];
    string name = vec[2];
    string even = vec[3];

    cout<<"in: "<<str<<endl;

    //== 分析事件 ==
    static vector<string> vec_pre;  //保存上一条信息,用于分析
    static bool ch_content = false; //分析:修改内容
    static bool ch_name = false;    //分析:修改名称
    static bool ch_name_r = false;  //分析:修改名称-目录
    //== 分析事件 ==


    //== 事件对应操作 ==
    //文件
    function<void()> fn_create = [](){
        cout<<"func:创建文件"<<endl;
    };
    function<void()> fn_open = [](){
        cout<<"func:打开文件"<<endl;
    };
    function<void()> fn_delete = [](){
        cout<<"func:删除文件"<<endl;
    };
    function<void()> fn_modify = [](){
        cout<<"func:修改内容"<<endl;
    };
    function<void()> fn_move_from = [](){
        cout<<"func:移除文件"<<endl;
    };
    function<void()> fn_move_to = [&](){
        if(ch_content)
        {
            ch_content = false;
            cout<<"func:修改内容"<<endl;
        }
        else if(ch_name)
        {
            ch_name = false;
            cout<<"func:重命名 ["<<vec_pre[2]<<" >> "<<name<<"]"<<endl;
        }
//        cout<<"func:fn_move_to"<<endl;
    };

    //目录
    function<void()> fn_create_r = [](){
        cout<<"func:创建目录"<<endl;
    };
    function<void()> fn_delete_r = [](){
        cout<<"func:删除目录"<<endl;
    };
    function<void()> fn_move_from_r = [](){
        cout<<"func:移除目录"<<endl;
    };
    function<void()> fn_move_to_r = [&](){
        if(ch_name_r)
        {
            ch_name_r = false;
            cout<<"func:重命名 ["<<vec_pre[2]<<" >> "<<name<<"]"<<endl;
        }
        cout<<"func:fn_move_to_r"<<endl;
    };
    //== 事件对应操作 ==

    //操作容器索引
    static map<string,function<void()>> map_op {
        { "CREATE",fn_create },
        { "OPEN",fn_open },
        { "DELETE",fn_delete },
        { "MODIFY",fn_modify },
        { "MOVED_FROM",fn_move_from },
        { "MOVED_TO",fn_move_to },

        { "CREATE,ISDIR",fn_create_r },
        { "DELETE,ISDIR",fn_delete_r },
        { "MOVED_FROM,ISDIR",fn_move_from_r },
        { "MOVED_TO,ISDIR",fn_move_to_r },
    };




    //分析:修改内容
    if((name.find(".goutputstream") != string::npos))
    {
        if(even == "MOVED_FROM")
        {
            vec_pre = vec;
            ch_content = true;
        }
        return false;
    }

    //分析:修改名称
    if(even == "MOVED_FROM")
    {
        vec_pre = vec;
        ch_name = true;
    }

    //分析:修改名称-目录
    if(even == "MOVED_FROM,ISDIR")
    {
        vec_pre = vec;
        ch_name_r = true;
    }

    //执行事件函数
    auto it = map_op.find(even);
    if(it != map_op.end())
    {
        it->second();
    }





//    static int ch_txt = 0;
//    if((name.find(".goutputstream") != string::npos))
//    {
//        vec_pre = vec;
//        if(even == "MOVED_FROM") ch_txt = 1;
//        return false;
//    }

//    static int ch_name = 0;
//    static string str_ch_name;
//    if(even == "MOVED_FROM")
//    {
//        str_ch_name = name;
//        ch_name = 1;
//    }

//    static int ch_name_rd = 0;
//    static string str_ch_name_rd;
//    if(even == "MOVED_FROM,ISDIR")
//    {
//        str_ch_name_rd = name;
//        ch_name_rd = 1;
//    }



//    if(even == "MOVED_FROM")
//    {
//        cout<<"== 移除文件 =="<<endl;
//    }
//    else if(even == "CREATE")
//    {
//        cout<<"== 创建文件 =="<<endl;
//    }
//    else if(even == "OPEN")
//    {
//        cout<<"== 打开文件 =="<<endl;
//    }
//    else if(even == "MOVED_TO")
//    {
//        if(ch_txt == 1)
//        {
//            ch_txt = 0;
//            cout<<"== 修改内容 =="<<endl;
//        }
//        else if(ch_name == 1)
//        {
//            ch_name = 0;
//            cout<<"重命名: "<<str_ch_name<<" >> "<<name<<endl;
//        }
//        else cout<<"== 文件重命名 =="<<endl;
//    }
//    else if(even == "DELETE")
//    {
//        cout<<"== 删除文件 =="<<endl;
//    }
//    else if(even == "MODIFY")
//    {
//        cout<<"== 修改内容:MODIFY =="<<endl;
//    }


//    else if(even == "DELETE,ISDIR")
//    {
//        cout<<"== 删除目录 =="<<endl;
//    }
//    else if(even == "CREATE,ISDIR")
//    {
//        cout<<"== 新建目录 =="<<endl;
//    }
//    else if(even == "MOVED_TO,ISDIR")
//    {
//        if(ch_name_rd == 1)
//        {
//            cout<<"重命名目录: "<<str_ch_name_rd<<" >> "<<name<<endl;
//        }
//    }
//    else if(even == "MOVED_FROM,ISDIR")
//    {
//        cout<<"== 移除目录 =="<<endl;
//    }

    vec_pre = vec;

    return true;
}
