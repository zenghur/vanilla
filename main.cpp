//
//  main.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/1.
//
//

#include <iostream>
#include "Singleton.h"

using namespace std;

class T {
public:
    T()
    {
        i = 4;
    }
public:
    int i;
};

int main()
{
    cout << Singleton<T>::getInstance().i << endl;
    return 0;
}
