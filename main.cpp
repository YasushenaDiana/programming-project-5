#include <iostream>
#include <syncstream>
#include <future>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

void slow(const string &name)
{
    this_thread::sleep_for(7s);
    osyncstream(cout) << name << endl;
}

void quick(const string &name)
{
    this_thread::sleep_for(1s);
    osyncstream(cout) << name << endl;
}

void work()
{
    auto begin = chrono::system_clock::now();

    auto fut = async(launch::async, []
                     {
                         quick("A1");
                         quick("C1");
                         quick("C2");
                         quick("D2"); });

    slow("A2");
    fut.get();
    slow("B");
    quick("D1");

    auto end = chrono::system_clock::now();
    auto duration = chrono::duration<double>(end - begin).count();
    osyncstream(cout) << "Time: " << duration << " seconds" << endl;
    osyncstream(cout) << "Work is done!" << endl;
}

int main()
{
    work();
    return 0;
}
