#include <iostream>
#include "cov1.h"
#include "cov2.h"

void error1()
{
    printf("x\n");
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
    cov1 c1;
    c1.f1();
    return 0;
}