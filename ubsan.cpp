#include <iostream>

int argn = 0;

void error1()
{
    int arr[1]{};
    printf("%d\n", arr[argn]);
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
    argn = argc;
    error3();
    return 0;
}