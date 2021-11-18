/****************************************Notes******************************************
1. lock_guard vs unique_lock: A lock_guard always holds a lock from its construction to its destruction.
    A unique_lock can be created without immediately locking, can unlock at any point in its existence,
    and can transfer ownership of the lock from one instance to another.
    A condition_variable needs a unique_lock.

2. unsigned long const hardware_threads = std::thread::hardware_concurrency() gives the number of cores in the CPU.
*/

#include "Async.h"

using namespace std;
using namespace std::chrono;

class DataFetcher {
    public:
    string operator()(string recdData) {
        cout << "Sleeping inside DataFetcher " << endl;
        this_thread::sleep_for(seconds(2));
        for(int i = 0; i < 10; ++i) {
            this_thread::sleep_for(milliseconds(500));
            cout << "DataFetcher()" << endl;
        }
        return "DataFetcher_" + recdData;
    }
};

string fetchDataFromDB(string recdData)
{
    cout << "Sleeping inside fetchDataFromDB " << endl;
    this_thread::sleep_for(seconds(2));
    for(int i = 0; i < 10; ++i) {
        this_thread::sleep_for(milliseconds(500));
        cout << "Fetching Data from DB..." << endl;
    }
    return "DB_" + recdData;
}

string fetchDataFromFile(string recdData)
{
    for(int i = 0; i < 10; ++i) {
        this_thread::sleep_for(milliseconds(500));
        cout << "Fetching Data from File" << endl;
    }
    return "File_" + recdData;
}

void startAsyncCalls()
{
    system_clock::time_point start = system_clock::now();
    auto start_time = system_clock::to_time_t ( start );

    string dataForDataFetcher = "DataForDataFetcher";

    future<string> resultFromDB          = async(launch::async, fetchDataFromDB, "DataForDB");
    future<string> resultFromDataFetcher = async(launch::async, DataFetcher(), dataForDataFetcher);
    string fileData = fetchDataFromFile("DataForFile");

    string dbData = resultFromDB.get();
    string dfData = resultFromDataFetcher.get();

    system_clock::time_point end_point = system_clock::now();
    auto diff = duration_cast<seconds> (end_point - start).count();

    auto end_time = system_clock::to_time_t ( end_point );
    cout << "Start time = " << ctime(&start_time)
    << "End   time = " << ctime(&end_time)
    << "Total Time Taken = " << diff << " Seconds." << endl;

    string data = dbData + " :: " + fileData + " :: " + dfData;
    cout << "Data = " << data << endl;
}

/**************************Future-Promise******************************/
void startFuturePromise()
{
    using ull = unsigned long long;
    std::promise<ull> oddSum;
    std::future<ull> oddFuture = oddSum.get_future();
    cout << "******************Demonstrating Future-Promise******************" << endl;
    std::thread t([](promise<ull>&& oddSumPromise, ull start, ull end) {
            auto timeIt = [](){
                system_clock::time_point timeNow = system_clock::now();
                auto time_now = system_clock::to_time_t ( timeNow );
                return ctime(&time_now);
            };

            cout << "\tThread Start Time = " << timeIt() << endl;

            ull oddSum = 0;
            for(ull i = start; i <= end; ++i)
                if( i & 1)
                    oddSum += i;
            std::this_thread::sleep_for(seconds(5));
            oddSumPromise.set_value(oddSum);

            cout << "\tThread   End Time = " << timeIt() << endl;
        }, std::move(oddSum), 0, 2000000000);

    for(int i = 0; i < 5; ++i) {
        cout << "Waiting for result of the sum" << endl;
        std::this_thread::sleep_for(seconds(1));
    }

    ull oddSumResult = oddFuture.get();
    t.join();

    cout << "Result of very large Odd Sum = " << oddSumResult << endl;

    cout << "**********Completed Demonstration of Future-Promise**************" << endl;
}

/***************************Shared Futures*****************************/
int queryNumber()
{
    int num = 2;

    if(!cin) {
        throw runtime_error("No number entered or read.");
    }
    return num;
}

void doSomething(string str, shared_future<int> f) {
    try {
        cout << "Doing Something with " << str << endl;
        int num = f.get();
        for(int i=0; i < num; ++i) {
            this_thread::sleep_for(seconds(i));
            cout << str << "\n" << endl;
        }
    } catch(const exception& e) {
        cerr << "\nEXCEPTION in thread " << this_thread::get_id() << " : " << e.what() << endl;
    }
}

void sharedFutureDemo() {
    try {
        //Need to write async().share if you want to use auto to let the compiler know about your intension
        auto sf = async(queryNumber).share(); // shared_future<int> sf = async(queryNumber);

        auto f1 = async(launch::async, doSomething, "Aasim", sf);
        auto f2 = async(launch::async, doSomething, "Abdul", sf);
        auto f3 = async(launch::async, doSomething, "Latif", sf);
        auto f4 = async(launch::async, doSomething, "Surve", sf);

        for(int i = 0; i < 10; ++i) {
            cout << "Sleeping for 1 second to emphasize that the async task is launched until we call future.get() on it." << endl;
            //this_thread::sleep_for(chrono::seconds(1));
        }

        f1.get();
        f2.get();
        f3.get();
        f4.get();
    } catch(const exception& e) {
        cout << "\nEXCEPTION : " << e.what() << endl;
    }
    cout << "\ndone" << endl;
}

mutex cout_mutex;

void threadFunc(int num, char str) {
    try {
        default_random_engine dre(21*str);
        uniform_int_distribution<int> id(10, 1000);
        int sum_wait_for = 0;

        for (int i=0; i<num; ++i) {
            int wait_for = id(dre);
            this_thread::sleep_for(chrono::milliseconds(wait_for));
            //cout_mutex.lock(); Using lock_guard instead of directly locking the mutex.
            lock_guard<mutex> lock(cout_mutex);
            sum_wait_for += wait_for;
            cout << "\tThread id --> " << this_thread::get_id()
                 << ". Waiting for " << wait_for << " milliseconds. "
                 << "  " << str << endl;
            //cout_mutex.unlock();
        }
        //cout_mutex.lock();
        cout << "Finished executing Thread id -->" << this_thread::get_id()
             << ". Total Wait_For = " << sum_wait_for << endl;
        //cout_mutex.unlock();
    }
    catch (const exception& e) {
        cerr << "THREAD-EXCEPTION (thread "
             << this_thread::get_id() << "): " << e.what() << endl;
    }
    catch (...) {
        cerr << "THREAD-EXCEPTION (thread "
             << this_thread::get_id() << ")  " << endl;
    }
}

void startThreads() {
    system_clock::time_point start = system_clock::now();
    auto start_time = system_clock::to_time_t ( start );

    try {
        thread t1(threadFunc, 7, '.');
        cout << "- started fg thread " << t1.get_id() << endl;
        cout << "*****************************************" << endl;
        for (int i=0; i<5; ++i) {
            thread t(threadFunc, 13, 'a'+i);
            cout << "- detach started bg thread " << t.get_id() << endl;
            t.detach();
        }
        cout <<"Reached End. Waiting for input.";
        cin.get();
        cout << "- join fg thread " << t1.get_id() << endl;

        system_clock::time_point end_point = system_clock::now();
        auto diff = duration_cast<seconds> (end_point - start).count();

        auto end_time = system_clock::to_time_t ( end_point );
        cout << "Start time = " << ctime(&start_time)
        << "End   time = " << ctime(&end_time)
        << "Total Time Taken = " << diff << " Seconds." << endl;

        t1.join();
    }
    catch (const exception& e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
}

void callThreadWrapper() {
    function<void()> func = [](){
        this_thread::sleep_for(chrono::seconds(1));
    };
    {
        ThreadWrapper thread1(func);
    }

    vector<ThreadWrapper> vecOfThreads;
    ThreadWrapper thwp1(func);
    ThreadWrapper thwp2(func);

    vecOfThreads.push_back(move(thwp1));
    vecOfThreads.push_back(move(thwp2));

    ThreadWrapper thwp3(func);
    // Change the content of vector
    vecOfThreads[1] = std::move(thwp3);

    cout << "Call ThreadWrapper End..." << endl;
}

void callIncorrectMutexUsage() {
    some_data* unprotected_data;
    data_wrapper x;
    auto l = [&unprotected_data](some_data& protected_data) {
        unprotected_data = &protected_data;
    };

    x.process_Data(l);
    unprotected_data->do_something();
}

mutex mut;
queue<int> data_queue;
condition_variable data_cond;

void data_preparation_thread() //Producer
{
    int i = 0;
	while(true)
	{
        ++i;
        this_thread::sleep_for(chrono::milliseconds(10));
		unique_lock<mutex> lk(mut);
		data_cond.wait(lk, [](){ return data_queue.size() < 10; });
		data_queue.push(i);
		cout << "Pushed "<< i << " into the queue. Currently left in queue : " << data_queue.size() << endl;
		lk.unlock();
		data_cond.notify_one();
		if( i > 120 )
            break;
	}
}

void data_preparation_thread_using_lock_guard()
{
    for(int chunk = 0; chunk < 10; ++chunk)
    {
        for(int i = 1; i <= 10; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(10));
            lock_guard<mutex> lk(mut);
            int candidate = chunk * 10 + i;
            data_queue.push(candidate);
            cout << "Pushed "<< candidate << " into the queue. Currently left in queue : " << data_queue.size() << endl;
        }
        data_cond.notify_all();
    }
}

void data_processing_thread() //Consumer
{
	while(true)
	{
        this_thread::sleep_for(chrono::milliseconds(10));
		unique_lock<mutex> lk(mut);
		//Wait to process until such a time that you have atleast 1 item in the queue.
		data_cond.wait(lk, []{ return data_queue.size() >= 1; });
		int front = data_queue.front();
		data_queue.pop();
		cout <<"	T1 -> Popped " << front << ". Left -> "<< data_queue.size() << endl;
		lk.unlock();
		//if(data_queue.size() == 0)
		//	break;
	}
}

void another_data_processing_thread() //Consumer 2
{
	while(true)
	{
        this_thread::sleep_for(chrono::milliseconds(10));
		unique_lock<mutex> lk(mut);
		//Wait to process until such a time that you have atleast 1 item in the queue.
		data_cond.wait(lk, []{ return data_queue.size() >= 1; });
		int front = data_queue.front();
		data_queue.pop();
		cout <<"	T2 -> Popped " << front << ". Left -> "<< data_queue.size() << endl;
		lk.unlock();
		//if(data_queue.size() == 0)
		//	break;
	}
}

void condition_var_demo()
{
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    cout << "Hardware Concurrency = " << hardware_threads << endl;

    thread t2{data_processing_thread};
    thread t1{data_preparation_thread_using_lock_guard};//thread t1{data_preparation_thread};
    thread t3{another_data_processing_thread};

    t2.join();
    t1.join();
    t3.join();
}

void demo_thread_safe_queue()
{
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    cout << "Hardware Concurrency = " << hardware_threads << endl;
    ThreadSafeQueue<Employee> employee_queue;
    int maxPushes = 1000;
    mutex mut;

    auto l1 = [&employee_queue, &maxPushes, &mut]{
                while(true) {
                --maxPushes;
                employee_queue.push({"Aasim", "Surve", 34, 10000});
                this_thread::sleep_for(chrono::milliseconds(500));
                employee_queue.push({"Viswam", "Kanduri", 40, 15000});
                employee_queue.push({"Siva", "Paddin", 45, 20000});
                employee_queue.push({"Nikhil", "Koshi", 38, 12000});
                employee_queue.push({"Elroy", "Haw", 22, 4000});
                this_thread::sleep_for(chrono::milliseconds(50));
                employee_queue.push({"Mahad", "Hachim", 25, 5000});
                }
            };

    auto l2 = [&employee_queue, &maxPushes, &mut]{
                    while(true) {
                        --maxPushes;
                        lock_guard<mutex> lk(mut);
                        while( !employee_queue.empty() ) {
                            auto emp_ptr = employee_queue.try_pop();
                            cout << this_thread::get_id() << " Left : " << employee_queue.size() << " Employee Details : " << *emp_ptr << endl;
                        }
                    }
                };

    //Producers
    thread t1(l1);
    thread t3(l1);

    //Consumers
    thread t2(l2);
    thread t4(l2);

    t1.join();
    t3.join();

    t2.join();
    t4.join();
}

void asyncCall()
{

    startFuturePromise();

    /*cout << "\n\n****************Calling Conditional Varible****************" << endl;
    condition_var_demo();*/

    cout << "\n\n****************Concurrency Using Async***************" << endl;
    //startAsyncCalls();
    //sharedFutureDemo();

    /*cout << "\n\n****************Concurrency Using Threads*****************" << endl;
    thread::id masterThreadID = this_thread::get_id();
    cout << "Main thread id is : " << masterThreadID << endl;
    cout << "Starting threads >>>>>>>>>>>>>" << endl;
    startThreads();

    cout << "\n\n****************Calling Thread Wrapper****************" << endl;
    callThreadWrapper();

    cout << "\n\n****************Calling Thread Safe Queue****************" << endl;
    demo_thread_safe_queue();*/
}
