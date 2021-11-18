#pragma once

#include <future>
#include <thread>
#include <random>
#include <iostream>
#include <exception>
#include <string>
#include <chrono>
#include <queue>

#include "ThreadWrapper.h"
#include "ThreadSafeQueue.h"
#include "Algorithms.h"

void startFuturePromise();
void startAsyncCalls();
void sharedFutureDemo();
void threadFunc(int num, char str);
void startThreads();
void callThreadWrapper();
void data_preparation_thread();
void data_preparation_thread_using_lock_guard();
void data_processing_thread();
void another_data_processing_thread();
void condition_var_demo();
void demo_thread_safe_queue();

void asyncCall();
