#include <cstring>
#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;




//== 字符串类型转换 ==
template<typename T>
string to_string(const T& t){ ostringstream os; os<<t; return os.str(); }

template<typename T>
T from_string(const string& str){ T t; istringstream iss(str); iss>>t; return t; }
//== 字符串类型转换 ==



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



//===== stm =====
//功能:字符串切割,主要针对单字符串的多重切割,支持不同切割符号,支持正反双向切割,
//      无法切割到分割符最后一段字符串，如果需要最后一段字符可以反向切割
//算法:查找标记位置,向前取值,舍弃标记末尾数据
struct stm
{
    string v_str;
    stm(const string &str) : v_str(str){}

    template<class ...Tarr> string split_t(){ return v_str; }
    template<class ...Tarr>
    string split_t(const string &flg,int begin,int end,const Tarr &...arg)
    {
        if((begin < 0) && (end < 0)) v_str = split_back(v_str,flg,begin,end);
        else v_str = split_go(v_str,flg,begin,end);
        return split_t(arg...);
    }

    template<class ...Tarr>
    string operator()(const Tarr &...arg) { return split_t(arg...); }

    //反向切割:反向参数传递
    string split_back(const string &str,const string &flg, int end,int begin)
    {
        begin *= -1; begin -= 1; end *= -1;
        int len = end - begin;
        if((begin < 0) || (len <= 0)) return "";

        size_t pos_begin = str.size();
        for(int i=0;i<begin;i++)
        {
            if((pos_begin = str.rfind(flg,pos_begin)) == str.npos) return "";
            pos_begin -= 1;
        }

        size_t pos_end = pos_begin;
        for(int i=0;i<len;i++)
        {
            if((pos_end = str.rfind(flg,pos_end)) == str.npos) return "";
            pos_end -= 1;
        }

        if(pos_begin != str.size()) pos_begin += 1;
        pos_end += flg.size() +1;

        if(pos_begin <= pos_end) return "";
        return string (str.begin()+pos_end,str.begin()+pos_begin);
    }

    //正向切割:正向参数传递
    string split_go(const string &str,const string &flg, int begin,int end)
    {
        int len = (end - begin) + 1;
        if((begin < 0) || (len <= 0)) return "";

        size_t pos_begin = 0;
        for(int i=0;i<begin;i++)
        {
            if((pos_begin = str.find(flg,pos_begin)) == str.npos) return "";
            pos_begin += flg.size();
        }

        size_t pos_end = pos_begin;
        for(int i=0;i<len;i++)
        {
            if((pos_end = str.find(flg,pos_end)) == str.npos) return "";
            pos_end += flg.size();
        }

        pos_end -= flg.size();
        if(pos_begin >= pos_end) return "";
        return string(str.begin()+pos_begin,str.begin()+pos_end);
    }
};
//===== stm =====


//== 信息结构体 ==
struct ct_disk
{
    string name;
    string serial;
    string rule;
};

struct ct_cmd
{
    string cmd;
    string operate;
};
//== 信息结构体 ==


//== 生成命令 ==
string create_cmd(const string &cmd,const string &op)
{
    string str;
    str = "[info]##"+ cmd +"##"+ op +"##";
    return str;
}

string create_disk(const string &name,const string &serial,const string &rule)
{
    string str;
    str = "[disk]##"+ name +"##"+ serial +"##"+ rule +"##";
    return str;
}

bool is_cmd(const string &str)
{
    string type = stm(str)("##",0,0);
    if(type == "[info]") return true;
    return false;
}

bool is_disk(const string &str)
{
    string type = stm(str)("##",0,0);
    if(type == "[disk]") return true;
    return false;
}

ct_cmd sto_cmd(const string &str)
{
    ct_cmd ct;
    ct.cmd = stm(str)("##",1,1);
    ct.operate = stm(str)("##",2,2);
    return ct;
}

ct_disk sto_disk(const string &str)
{
    ct_disk ct;
    ct.name = stm(str)("##",1,1);
    ct.serial = stm(str)("##",2,2);
    ct.rule = stm(str)("##",3,3);
    return ct;
}
//== 生成命令 ==


//去除换行符号
void less_enter(char *buf)
{
    for(size_t i=0;i<strlen(buf);i++)
    {
        if(buf[i] == '\n')
        {
           buf[i] = '\0';
           return ;
        }
    }
}

//获取所有磁盘信息
list<ct_disk> get_inti_disk()
{
    string cmd = "lsblk --nodeps -no name,serial";
    list<ct_disk> ls;

    FILE *fd = popen(cmd.c_str(),"r");
    if(fd)
    {
        char buf[256];
        ct_disk ct;
        int count = 0;
        while(fgets(buf,sizeof(buf),fd) != NULL)
        {
            count++;
            less_enter(buf);
            ct.name = to_string(count);
            ct.serial = stm(buf)("  ",-1,-1);
            ls.push_back(ct);
        }
        fclose(fd);
    }
    return ls;
}

//初始化操作命令
list<ct_cmd> get_init_cmd()
{
    list<ct_cmd> ls;
    {
        ct_cmd ct;
        ct.cmd = "open";
        ct.operate = "0";
        ls.push_back(ct);
    }
    {
        ct_cmd ct;
        ct.cmd = "size";
        ct.operate = "0";
        ls.push_back(ct);
    }
    return ls;
}


//初始化磁盘数据,获取所有当前插入的磁盘,并记录为读写
bool init_disk_rule(list<ct_cmd> ls_cmd,list<ct_disk> ls_disk,const string &filename)
{
    fstream ofs(filename,ios::out);
    if(ofs.is_open())
    {
        for(auto a:ls_cmd)
        {
            ofs<<create_cmd(a.cmd,a.operate)<<endl;
        }

        for(auto a:ls_disk)
        {
            if(a.serial == "") a.serial = "NULL";
            ofs<<create_disk(a.name,a.serial,"RW")<<endl;
        }
        ofs.close();
        return true;
    }
    else return false;

    return true;
}

//初始化磁盘数据,将命令与磁盘信息写入文件
list<string> create_table_list(list<ct_cmd> ls_cmd,list<ct_disk> ls_disk)
{
    list<string> ls;
    for(auto a:ls_cmd)
    {
        ls.push_back(create_cmd(a.cmd,a.operate));
    }
    for(auto a:ls_disk)
    {
        if(a.serial == "") a.serial = "NULL";
        ls.push_back(create_disk(a.name,a.serial,"RW"));
    }
    return ls;
}



//== 显示操作 ==
void show_file_table(const string &filename)
{
    fstream ifs(filename,ios::in);
    if(ifs.is_open())
    {
        cout<<"|== 配置文件信息 =="<<endl;
        string str;
        while(getline(ifs,str))
        {
            cout<<"|"<<str<<endl;
        }
        cout<<"|====="<<endl;
        ifs.close();
    }
}

void show_disk_now()
{
    string cmd = "lsblk --nodeps -no name,serial";
    FILE *fd = popen(cmd.c_str(),"r");
    if(fd)
    {
        cout<<"|== 当前磁盘信息 =="<<endl;
        char buf[256];
        while(fgets(buf,sizeof(buf),fd) != NULL)
        {
            cout<<"|"<<buf;
        }
        fclose(fd);
        cout<<"|====="<<endl;
    }
}
//== 显示操作 ==


//文件转列表
list<string> file_to_list(const string &filename)
{
    list<string> ls;
    fstream ifs(filename,ios::in);
    if(ifs.is_open())
    {
        string str;
        while(getline(ifs,str))
        {
            ls.push_back(str);
        }
        ifs.close();
    }
    return ls;
}

//列表写入文件
bool list_to_file(list<string> ls,const string &filename)
{
    fstream ofs(filename,ios::out);
    if(ofs.is_open())
    {
        for(auto a:ls)
        {
            ofs<<a<<endl;
        }
        ofs.close();
        return true;
    }
    else return false;
}

//修改cmd
bool change_cmd(list<string> &ls,const string &in_cmd,const string &new_op)
{
    for(auto &str:ls)
    {
        if(is_cmd(str))
        {
            ct_cmd ct = sto_cmd(str);
            if(ct.cmd == in_cmd)
            {
                string new_str = create_cmd(ct.cmd,new_op);
                str = new_str;
                return true;
            }
        }
    }
    return false;
}

//修改disk
bool change_disk(list<string> &ls,const string &in_name,const string &new_rule)
{
    for(auto &str:ls)
    {
        if(is_disk(str))
        {
            ct_disk ct = sto_disk(str);
            if(ct.name == in_name)
            {
                string new_str = create_disk(ct.name,ct.serial,new_rule);
                str = new_str;
                return true;
            }
        }
    }
    return false;
}

//判断文件是否存在
bool is_exist_file(const string &filename)
{
    ifstream ifs(filename);
    if(ifs.is_open())
    {
        ifs.close();
        return true;
    }
    return false;
}

//获取文件记录的磁盘序列号
list<string> get_serial_table(list<string> ls)
{
    list<string> ls_serial;

    for(auto a:ls)
    {
        if(is_disk(a))
        {
            ct_disk ct = sto_disk(a);
            if(ct.serial != "NULL") ls_serial.push_back(ct.serial);
        }
    }
    return ls_serial;
}

//获取现在插入的磁盘序列号
list<string> get_serial_dev()
{
    list<string> ls_serial;
    string cmd = "lsblk --nodeps -no serial";
    FILE *fd = popen(cmd.c_str(),"r");
    if(fd)
    {
        char buf[256];
        while(fgets(buf,sizeof(buf),fd) != NULL)
        {
            less_enter(buf);
            if(strlen(buf) > 0) ls_serial.push_back(buf);
        }
        fclose(fd);
    }
    return ls_serial;
}

//检查新插入的磁盘
list<string> get_new_dev(const string &filename)
{
    list<string> ls;
    list<string> ls_table = get_serial_table(file_to_list(filename));
    list<string> ls_dev = get_serial_dev();

    //1.获取记录文件的序列号
    //2.获取当前插入的序列号
    //3.排除文件存在的序列号(等于获取新序列号)
    //4.生成list容器
    set<string> set_new;
    for(auto a:ls_table)
    {
        set_new.emplace(a);
    }
    for(auto a:ls_dev)
    {
        set_new.emplace(a);
    }
    for(auto a:ls_table)
    {
        set_new.erase(a);
    }
    for(auto a:set_new)
    {
        ls.push_back(a);
    }
    return ls;
}

//插入新磁盘到容器
bool push_disk_new(list<string> &ls_table,list<string> ls_new)
{
    int size = -1;
    for(auto a:ls_table)
    {

        ct_cmd ct = sto_cmd(a);
        if(ct.cmd == "size")
        {
             size = from_string<int>(ct.operate);
             break;
        }
    }
    if(size == -1) return false;

    for(auto a:ls_new)
    {
        size++;
        ls_table.push_back(create_disk(to_string(size),a,"RW"));
    }
    return change_cmd(ls_table,"size",to_string(size));
}

//更新序列号到文件
bool update_dev(const string &filename)
{
    list<string> ls_table = file_to_list(filename);
    list<string> ls_new = get_new_dev(filename);

    if(push_disk_new(ls_table,ls_new) == false) return false;
    return list_to_file(ls_table,filename);
}


//== 界面代码 ==
void show_wid()
{

string str =
R"(|===== 磁盘管理系统 =====
| 1.查看配置信息
| 2.修改权限
| 3.帮助信息
| 4.初始化磁盘管理
| 5.追加新磁盘管理
| 0.退出
|========================)";
    cout<<str<<endl;
}

void wid_show(const string &filename)
{
    show_file_table(filename);
    cout<<endl;
    show_disk_now();
}

void wid_change_file(const string &filename,const string &cmd)
{
    string err_fm_null = "== 命令格式错误:分隔符错误 ==";
    string err_fm_type = "== 命令格式错误:命令类型错误 ==";
    string err_ch = "== 修改失败-可能不存在该信息 ==";
    string err_ok = "== 修改成功 ==";
    string err_bad = "== 写入文件时发生错误-请重新操作 ==";
    string err_no = "== 文件不存在-请先初始化磁盘 ==";

    if(is_exist_file(filename) == false)
    {
        cout<<err_no<<endl;
        return ;
    }

    vector<string> vec = stmv(cmd)(":");
    if(vec.size() != 3)
    {
        cout<<err_fm_null<<endl;
        return ;
    }

    string s1 = vec[0];
    string s2 = vec[1];
    string s3 = vec[2];

    bool is_ok = false;
    list<string> ls = file_to_list(filename);
    if(s1 == "info")
    {
        bool ok = change_cmd(ls,s2,s3);
        if(ok) is_ok = true;
    }
    else if(s1 == "disk")
    {
        bool ok = change_disk(ls,s2,s3);
        if(ok) is_ok = true;
    }
    else cout<<err_fm_type<<endl;

    if(is_ok)
    {
        bool ok = list_to_file(ls,filename);
        if(ok)
        {
            cout<<err_ok<<endl;
            show_file_table(filename);
        }
        else cout<<err_bad<<endl;
    }
    else cout<<err_ch<<endl;
}

void wid_help()
{
    string str =
R"(|=====
|使用说明:首次使用需要初始化磁盘权限,初始化之后会进行拦截
|=====
|[info]命令说明:
|    open:[0/1] (0为禁用拦截,1为开启拦截)
|    size:[n] (统计磁盘数量)
|=====
|[info]类型修改:
|    例子:
|        info:open:0 ([类型]:[命令]:[操作])
|[disk]类型修改:
|    例子:
|        disk:2:OR ([类型]:[磁盘序号]:[权限])
|=====
|权限:
|RW:读写权限
|OR:只读权限
|OO:非法权限
|=====)";

    cout<<str<<endl;
}

void wid_init(const string &filename)
{
    string err_ok = "== 初始化成功 ==";
    string err_fm = "== 初始化失败-请重试 ==";
    list<ct_cmd> ls_cmd = get_init_cmd();
    list<ct_disk> ls_disk = get_inti_disk();
    list<string> ls_table = create_table_list(ls_cmd,ls_disk);

    {
        bool ok = change_cmd(ls_table,"size",to_string(ls_disk.size()));
        if(ok == false)
        {
            cout<<err_fm<<endl;
            return ;
        }
    }
    {
        bool ok = list_to_file(ls_table,filename);
        if(ok == false)
        {
            cout<<err_fm<<endl;
            return ;
        }
    }
    cout<<err_ok<<endl;
    wid_show(filename);
}
//== 界面代码 ==



int main()
{


    string file_table = "/home/red/test/hook/file_table.txt";

#if 1
    string str_in;
    while(true)
    {
        show_wid();

        cin>>str_in;
        if(str_in == "1")
        {
            wid_show(file_table);
        }
        else if(str_in == "2")
        {
            string str_cmd;
            cout<<"== 请输入命令 =="<<endl;
            cin>>str_cmd;
            wid_change_file(file_table,str_cmd);
        }
        else if(str_in == "3")
        {
            wid_help();
        }
        else if(str_in == "4")
        {
            wid_init(file_table);
        }
        else if(str_in == "5")
        {
            bool ok = update_dev(file_table);
            if(ok) cout<<"== 成功追加新磁盘到磁盘权限管理系统 =="<<endl;
        }
        else if(str_in == "0") break;

        cout<<endl;
    }

    cout<<"===== 欢迎下次登录 ====="<<endl;
    return 0;
#endif



//    {
//        list<string> ls = get_new_dev(file_table);

//        for(auto a:ls)
//        {
//            cout<<a<<endl;
//        }
//    }

    bool ok = update_dev(file_table);
    cout<<ok<<endl;

    return 0;

    list<string> ls_t = file_to_list(file_table);

    cout<<"== "<<endl;
    for(auto a:ls_t)
    {
        cout<<a<<endl;
    }

    list<string> ls_new = get_new_dev(file_table);

    {
        cout<<"ok: "<<push_disk_new(ls_t,ls_new)<<endl;
    }

    cout<<"== "<<endl;
    for(auto a:ls_t)
    {
        cout<<a<<endl;
    }

    cout<<"end=="<<endl;

    return 0;



    list<string> ls_t1 = get_serial_table(file_to_list(file_table));
    list<string> ls_n2 = get_serial_dev();

    set<string> set_le;





//    ls_new.resize(ls_n2.size()+ls_t1.size());



    for(auto a:ls_t1)
    {
        cout<<a<<endl;
        set_le.emplace(a);
    }
    cout<<"========"<<endl;
    for(auto a:ls_n2)
    {
        cout<<a<<endl;
        set_le.emplace(a);
    }

    cout<<"========"<<endl;
    for(auto a:set_le)
    {
        cout<<a<<endl;
    }

    for(auto a:ls_t1)
    {
        set_le.erase(a);
    }


    cout<<"========"<<endl;
    for(auto a:set_le)
    {
        cout<<a<<endl;
    }





    cout<<"====end===="<<endl;

    return 0;

    cout << "== begin ==" << endl;



    list<ct_cmd> ls_cmd = get_init_cmd();
    list<ct_disk> ls_disk = get_inti_disk();
    list<string> ls_table = create_table_list(ls_cmd,ls_disk);



    for(auto a:ls_table)
    {
        cout<<a<<endl;
    }


    {
        bool ok = change_cmd(ls_table,"size",to_string(ls_disk.size()));
        cout<<"change_cmd ok: "<<ok<<endl;
    }

    for(auto a:ls_table)
    {
        cout<<a<<endl;
    }

    {
        bool ok = change_disk(ls_table,"2","OR");
        cout<<"change_disk ok: "<<ok<<endl;
    }

    for(auto a:ls_table)
    {
        cout<<a<<endl;
    }

    list_to_file(ls_table,file_table);




    show_file_table(file_table);

//    system("clear");
    show_disk_now();



//    bool ok = init_disk_rule(ls_cmd,ls_disk,file_table);
//    cout<<"ok: "<<ok<<endl;

//    show_file_table(file_table);
//    show_disk_now();

//    list<string> ls = file_to_list(file_table);
//    {
//        bool ok = change_cmd(ls,"size",to_string(ls_disk.size()));
//        cout<<"change_cmd ok: "<<ok<<endl;
//    }

//    for(auto a:ls)
//    {
//        cout<<a<<endl;
//    }
//    {
//        bool ok = list_to_file(ls,file_table);
////        bool ok = change_cmd(ls,"size",to_string(ls_disk.size()));
//        cout<<"list_to_file ok: "<<ok<<endl;
//    }





    cout << "== end ==" << endl;
    return 0;
}
