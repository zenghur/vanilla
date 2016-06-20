// Copyright (c) 2016 zenghur

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