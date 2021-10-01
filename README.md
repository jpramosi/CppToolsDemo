## C++ Tools Demonstration
This project will introduce you on how to use sanitizers, generating core dumps and coverage reports.

This setup was tested on Ubuntu 21.04 with Clang & GNU compiler.
The main focus of this project is to offer an example on how to use these tools and setting up an own project.

Instead of MemorySanitizer [Valgrind](http://valgrind.org/) will be used for uninitialized reads, because all code needs to be instrumented with the sanitizer itself.

Additionally, a Cmake module is included to create the testing scripts and can also be used for other things.  
Everything else is explained in the [CMakeLists.txt](https://github.com/reapler/sanitize-coredump-coverage/blob/master/CMakeLists.txt).


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