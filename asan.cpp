#include <iostream>

void error1()
{
    auto *array = new int[100];
    delete[] array;
    delete[] array;
    printf("%d\n", array[0]);
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