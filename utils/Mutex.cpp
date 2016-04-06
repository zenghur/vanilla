//
//  Mutex.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/7.
//
//

#include "Mutex.hpp"


using namespace vanilla;

Mutex::Mutex()
{
    if (pthread_mutex_init(&mutex_, NULL)) {
        // log
    }
}

Mutex::~Mutex()
{
    if (pthread_mutex_destroy(&mutex_)) {
        // log
    }
}

void Mutex::lock()
{
    if (pthread_mutex_lock(&mutex_)) {
        // log
    }
}

void Mutex::unLock()
{
    if (pthread_mutex_destroy(&mutex_)) {
        // log
    }
}