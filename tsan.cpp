#include <iostream>
#include <thread>

int global = 0;

void thread1()
{
    global++;
}

void thread2()
{
    global--;
}

void error1()
{
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join();
    t2.join();
}

void error2()
{
    error1();
}

void error3()
{
    error2();
}

int main(int argc, char **argv) 
{
    error3();
    return 0;
}