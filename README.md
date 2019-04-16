## CMake setup example
This setup will introduce you into sanitizing code, coverage & core dumping.
It has been used on ubuntu 18.04 with clang & gnu compiler.
It just focuses on setting the project up and using the tools.  
Instead of [MemorySanitizer](https://clang.llvm.org/docs/MemorySanitizer.html) we will be using [Valgrind](http://valgrind.org/)
 for uninitialized reads, because all code needs to be instrumented with the sanitizer.  
Additionally a cmake module is included to create the testing scripts and can also be used for other things.  


This project use these utilities:

- [AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html)
- [ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html)
- [UndefinedBehaviorSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)
- [Valgrind](http://valgrind.org/)
- [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html)
- [gcovr](https://github.com/gcovr/gcovr)
- [llvm-cov](https://llvm.org/docs/CommandGuide/llvm-cov.html)

### Motivation

I have written this for myself to get an overview of all these utilities and to help other who are struggling with these tools and just needs a reference with examples.