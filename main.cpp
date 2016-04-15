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
#include <cassert>

using namespace std;

int parseDate(const char* str)
{
    if(NULL == str)
        return -1;
    
    if( strlen(str) == 0)
        return -1 ;
    
    tm  date={0};
    strptime(str, "%Y-%m-%d %H:%M:%S", &date);
    return (int)mktime(&date);
}


time_t getDiffSeconds(string lhs, string rhs)
{
    time_t leftTime = parseDate(lhs.c_str());
    time_t rightTime = parseDate(rhs.c_str());
    
    return rightTime - leftTime;
}

int main()
{
    cout << getDiffSeconds("2016-04-18 00:05:00", "2016-04-13 15:00") << endl;
    return 0;
}
