#pragma once
#include<thread>
#include<iostream>
#include<functional>
#include<mutex>

using namespace std;

class ThreadWrapper
{
    private:
        thread threadHandler;
    public:
        ThreadWrapper(const ThreadWrapper& other)            = delete;
        ThreadWrapper& operator=(const ThreadWrapper& other) = delete;

        ThreadWrapper(function<void()> func);
        ThreadWrapper(ThreadWrapper&& other);
        ThreadWrapper& operator=(ThreadWrapper&& other);

        virtual ~ThreadWrapper();
};


class some_data
{
    private:
        int a = 0;
        string b;
    public:
        void do_something() {
            ++a;
            cout << " a = " << a << endl;
        }
};

class data_wrapper
{
    private:
        some_data data;
        mutex data_mutex;
    public:
        template<typename Function>
        void process_Data(Function func)
        {
            lock_guard<mutex> lock_mutex(data_mutex);
            func(data);
        }
};
