#include <thread>

void test()
{
    int a = 0;

    auto t1 = std::thread([&] { a++; });
    auto t2 = std::thread([&] { a++; });

    t1.join();
    t2.join();
}