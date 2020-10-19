// g++ thread.cpp -lpthread -std=c++14


#include <cassert>
#include <iostream>
#include <atomic>
#include <future>
#include <thread>

using namespace std;

// 只调用一次
void case1()
{
    static once_flag flag;
    auto f = []()
    {
        cout << "tid=" <<
        this_thread::get_id() <<endl;

        std::call_once(flag, 
            [](){
                cout << "only once" <<endl;
            }
        );
    };
    thread t1(f);
    thread t2(f);

    t1.join();
    t2.join();
}

// 线程局部存储
void case2() {
    thread_local int n = 0;

    auto f = [&](int x)
    {
        n += x;
        cout <<n;
        cout << ", tid = " <<
        this_thread::get_id() <<endl;
    };

    thread t1(f, 10);
    thread t2(f, 20);

    t1.join();
    t2.join();
    cout << n <<endl;
}


void case3() 
{
    atomic_int  x {0};
    atomic_long y (100L);

    assert(++x == 1);
    y += 20;
    assert(y < 2000);

    static atomic_flag  flag {false};
    static atomic_int   n;
    auto f = [&]()
    {
        auto value = flag.test_and_set();

        if (value) {
            cout << "flag has been set" <<endl;
        }else {
            cout << "set flag by" <<
            this_thread::get_id() <<endl;
        }

        n += 10;
        // cout << this_thread::get_id() << "befor_yield:" << n <<endl;
        // this_thread::yield();
        // cout << this_thread::get_id() << "after_yield:" << n <<endl;

        this_thread::sleep_for(n.load() * 10ms);
        cout << this_thread::get_id() << "after_sleep:" << n <<endl;

        // this_thread::sleep_until()
    };

    thread t1(f);
    thread t2(f);
    cout << "t1 joinable :" << t1.joinable() << endl;
    cout << "t2 joinable :" << t2.joinable() << endl;
    t1.join();
    t2.join();

}


int fib(int n)
{
    if (n < 2) {
        return 1;
    }
    return fib(n-1)+fib(n-2);
}

void case4()
{
    auto f1 = std::async(fib, 4);
    cout << "future async ..." <<endl;

    f1.wait();
    cout << f1.get() <<endl;
}

void case5()
{
    auto task = [](auto x)
    {
        this_thread::sleep_for(x * 1ms);
        cout << "sleep for" << x <<endl;
        return x;
    };

    auto f = std::async(task, 10);  // 启动一个异步任务

    f.wait();                       // 等待任务完成

    cout <<f.valid() <<endl;        // 确实已经完成了任务
    cout <<f.get() <<endl;          // 获取任务的执行结果 get() 只能调一次
    cout << f.valid() <<endl;
}

int main()
{

    cout << "main_thread_id = " <<
        this_thread::get_id() <<endl;

    // case1();
    // case2();
    // case3();
    // case4();
    case5();

    return 0;
}




