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

using namespace std;

struct T {
    T() {
        i = 3;
    }
    int i;
};

int main()
{
    cout << vanila::GenericSingleton<T>::getInstance().i << endl;
    return 0;
}
