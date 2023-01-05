#include <iostream>
#include "../inter_sock.hpp"
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

using namespace std;
mutex mu;
int hu = 0;
int fa = 0;
atomic<int> at_fa{0};

//

class cl : public inter_client
{
    void on_open() override
    {
        cout<<"inter_client on_open: "<<std::this_thread::get_id()<<endl;
    }
    void on_message(const string& meg) override
    {
        fa++;
        cout<<"inter_client on_message: "<<std::this_thread::get_id()<<"|"<<fa<<endl;
    }
    void on_close() override
    {
//        cout<<"inter_client on_close: "<<std::this_thread::get_id()<<endl;
    }
};

//服务器的on_message函数并非线程安全,on_message函数是多线程回调,
//只保证回调次数与send次数一致,
//不保证线程之间的对临界区的数据安全问题
class sl : public inter_server
{
    void on_open(const web_sock& sock, const web_http& http) override
    {
        hu++;
        cout<<"inter_server on_open: "<<std::this_thread::get_id()<<"|"<<hu<<endl;
    }
    void on_message(const web_sock& sock, const string& meg) override
    {
//        unique_lock<mutex> lock(mu);
        fa--;
        at_fa--;
        cout<<"inter_server on_message: "<<meg<<"|"<<fa<<"|"<<at_fa<<endl;
        usleep(4000);
    }
    void on_close(const web_sock& sock) override
    {
        unique_lock<mutex> lock(mu);
        hu--;
        cout<<"inter_server on_close: "<<std::this_thread::get_id()<<"|"<<hu<<endl;
        if(hu == 0) this->stop_server();
    }
};

int main()
{
    cout << "Hello World!" << endl;

#if 0
    if(fork() == 0)
    {
        sl s;
        s.open();
    }
    else
    {
        vector<cl*> vec;
        for(int i=0;i<100;i++)
        {
            cl *pt = new cl;
            pt->open();
            vec.push_back(pt);
        }
        cout<<"vec.size(): "<<vec.size()<<endl;
        sleep(2);

        while(true)
        {
            static int k=0;
            if(k == 10) break;
            k++;

//            sleep(1);
            for(size_t i=0;i<vec.size();i++)
            {
                for(size_t j=0;j<10;j++)
                {
                    unique_lock<mutex> lock(mu);
                    fa++; vec[i]->sock().send(to_string(fa));
                    cout<<"send: "<<fa<<endl;
                }
            }
        }
        sleep(3);
        for(size_t i=0;i<vec.size();i++) { vec[i]->close_client(); }
        for(size_t i=0;i<vec.size();i++) { delete vec[i]; }
        cout<<"send close: "<<fa<<endl;
    }

#endif

#if 0
    sl s;
    s.open();
#else


    vector<cl*> vec;
    for(int i=0;i<100;i++)
    {
        cl *pt = new cl;
        pt->open();
        vec.push_back(pt);
    }
    cout<<"vec.size(): "<<vec.size()<<endl;
    sleep(2);

    while(true)
    {
        static int k=0;
        if(k == 10) break;
        k++;
        for(size_t i=0;i<vec.size();i++)
        {
            for(size_t j=0;j<10;j++)
            {
                unique_lock<mutex> lock(mu);
                fa++; vec[i]->sock().send(to_string(fa));
                cout<<"send: "<<fa<<endl;
            }
        }
    }
    sleep(3);
    for(size_t i=0;i<vec.size();i++) { vec[i]->close_client(); }
    for(size_t i=0;i<vec.size();i++) { delete vec[i]; }
    cout<<"send close: "<<fa<<endl;

#endif

    return 0;
}
