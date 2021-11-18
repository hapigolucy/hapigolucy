#include<iostream>
#include<mutex>
#include<condition_variable>
#include<queue>

using namespace std;

mutex m;
queue<int> _data_queue;
condition_variable _data_cond;

void data_preparation_func()
{
	for( int i = 0; i < 100; ++i)
	{
		lock_guard<mutex> lk(m);
		cout << "Pushing "<< i << " into the queue." << endl;
		_data_queue.push(i);
		_data_cond.notify_one();
	}
}

void data_processing_func()
{
	while(true)
	{
		unique_lock<mutex> lk(m);
		_data_cond.wait(lk, []{ return !_data_queue.empty(); });
		int front = _data_queue.front();
		_data_queue.pop();
		lk.unlock();
		cout <<"	Popped " << front << endl;
		if(front == 99)
			break;
	}
}
