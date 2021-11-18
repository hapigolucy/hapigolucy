#include "ThreadWrapper.h"

ThreadWrapper::ThreadWrapper(function<void()> func) : threadHandler(func)
{}

ThreadWrapper::~ThreadWrapper()
{
    if(threadHandler.joinable()) {
        cout << "Joining the thread " << endl;
        threadHandler.join();
    }
}

ThreadWrapper::ThreadWrapper(ThreadWrapper&& other) : threadHandler(move(other.threadHandler))
{
    cout << "Move Constructor Called..." << endl;
}

ThreadWrapper& ThreadWrapper::operator=(ThreadWrapper&& other)
{
    cout << "Move Assignment Called..." << endl;

    if(threadHandler.joinable())
    {
        cout << "Joinable thread..." << endl;
        threadHandler.join();
    }

    threadHandler = move(other.threadHandler);
    return *this;
}
