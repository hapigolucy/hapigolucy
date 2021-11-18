#pragma once

#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>

using namespace std;

template<typename T>
class ThreadSafeQueue
{
    private:
        mutable mutex mut;
        queue<T> data_queue;
        condition_variable data_cond;

    public:
        ThreadSafeQueue();
        ThreadSafeQueue(const ThreadSafeQueue& rhs);

        void push(T new_value);
        void wait_and_pop(T& value);
        shared_ptr<T> wait_and_pop();
        bool try_pop(T& value);
        shared_ptr<T> try_pop();
        bool empty() const;
        int size() const;
};

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue() {}

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue& rhs) {
    lock_guard<mutex> lk(rhs.mut);
    data_queue = rhs.data_queue;
}

template<typename T>
void ThreadSafeQueue<T>::push(T new_value) {
    lock_guard<mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
}

template<typename T>
void ThreadSafeQueue<T>::wait_and_pop(T& value) {
    unique_lock<mutex> lk(mut);
    data_cond.wait(lk, [this]{ return !data_queue.empty();});
    value=data_queue.front();
    data_queue.pop();
}

template<typename T>
shared_ptr<T> ThreadSafeQueue<T>::wait_and_pop() {
    unique_lock<mutex> lk(mut);
    data_cond.wait(lk, [this]{ return !data_queue.empty();});
    shared_ptr<T> res(make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool ThreadSafeQueue<T>::try_pop(T& value) {
    lock_guard<mutex> lk(mut);
    if(data_queue.empty())
        return false;
    value=data_queue.front();
    data_queue.pop();
    return true;
}

template<typename T>
shared_ptr<T> ThreadSafeQueue<T>::try_pop() {
    lock_guard<mutex> lk(mut);
    if(data_queue.empty()) {
        cout << "Returning empty queue" << endl;
        return shared_ptr<T>();
    }
    shared_ptr<T> res(make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool ThreadSafeQueue<T>::empty() const {
    lock_guard<mutex> lk(mut);
    return data_queue.empty();
}

template<typename T>
int ThreadSafeQueue<T>::size() const {
    lock_guard<mutex> lk(mut);
    return data_queue.size();
}
