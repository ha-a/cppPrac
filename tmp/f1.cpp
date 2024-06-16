// f1.cpp
#include <iostream>
#include "f2.h"

int a[] = {123, 456};

int main() {
    // std::cout << f2() << std::endl;

    int* p = a;
    // int** q = &a; // これはコンパイルエラーになります
    int** q = &p;
    std::cout << *q << std::endl;
    std::cout << **q << std::endl;
    std::cout << (*q)[1] << std::endl;

    const size_t sz = 10;
    int b[sz]{0};
    int* ptr = b;
    for (int i = 0; i < sz; ++i){
        *ptr++ = 2 * i;
    }
    for (int i = 0; i < sz; ++i){
        std::cout << b[i] << ' ';
    }
    std::cout << std::endl;
    ptr = b;
    for (int i = 0; i < sz-1; ++i){
        *(++ptr) = 2 * i;
    }
    for (int i = 0; i < sz; ++i){
        std::cout << b[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
