//
//  Mutex.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/7.
//
//

#include "Mutex.h"

#include <iostream>


using namespace vanilla;

Mutex::Mutex()
{
    if (pthread_mutex_init(&mutex_, NULL)) {
        std::runtime_error("cannot initialize mutex.");
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex_);
}

void Mutex::lock()
{
    if (pthread_mutex_lock(&mutex_)) {
        // log
    }
}

void Mutex::unLock()
{
    if (pthread_mutex_unlock(&mutex_)) {
        // log
    }
}