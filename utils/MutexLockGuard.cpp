//
//  MutexLockGuard.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/7.
//
//

#include "MutexLockGuard.h"

using namespace vanilla;

MutexLockGuard::MutexLockGuard(Mutex &m): mutex_(m)
{
    mutex_.lock();
}

MutexLockGuard::~MutexLockGuard()
{
    mutex_.unLock();
}