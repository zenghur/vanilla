//
//  main.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/1.
//
//
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <iostream>

#include "GenericSingleton.h"

#include <libkern/OSByteOrder.h>
#include "Endian.h"
#include <iomanip>
#include <vector>

using namespace std;


struct T {
    T() {
        i = 3;
    }
    int i;
};

void* print(void *para)
{
    cout << vanilla::GenericSingleton<T>::getInstance().i <<  endl;
    return para;
}

int main()
{
  
}
