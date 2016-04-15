#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cassert>
#include <thread>


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

int main()
{
   
    
    return 0;
}

