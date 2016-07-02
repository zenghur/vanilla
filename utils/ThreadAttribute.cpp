// Copyright (c) 2016 zenghur


#include "ThreadAttribute.h"

#include "Error.h"

using vanilla::ThreadAttribute;

ThreadAttribute::ThreadAttribute() {
  int ref = pthread_attr_init(&attr_);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
}

ThreadAttribute::~ThreadAttribute() {
  int ref = pthread_attr_destroy(&attr_);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
}

int ThreadAttribute::getInheritSched(int *inheritsched) {
  int ref = pthread_attr_getinheritsched(&attr_, inheritsched);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::setInheritSched(int inheritsched) {
  int ref = pthread_attr_setinheritsched(&attr_, inheritsched);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::getSchedParam(struct sched_param *param) {
  int ref = pthread_attr_getschedparam(&attr_, param);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::setSchedParam(struct sched_param *param) {
  int ref = pthread_attr_setschedparam(&attr_, param);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

// man sched, SCHED_FIFO, SCHED_RR, and SCHED_OTHER
int ThreadAttribute::getSchedPolicy(int *policy) {
  int ref = pthread_attr_getschedpolicy(&attr_, policy);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::setSchedPolicy(int policy) {
  int ref = pthread_attr_setschedpolicy(&attr_, policy);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::getScope(int *contentionscope) {
  int ref = pthread_attr_getscope(&attr_, contentionscope);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::setScope(int contentionscope) {
  int ref = pthread_attr_setscope(&attr_, contentionscope);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::getStackSize(size_t *stacksize) {
  int ref = pthread_attr_getstacksize(&attr_, stacksize);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::setStackSize(size_t stacksize) {
  int ref = pthread_attr_setstacksize(&attr_, stacksize);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::getStack(void **stackaddr, size_t *stacksize) {
  int ref = pthread_attr_getstack(&attr_, stackaddr, stacksize);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::setStack(void *stackaddr, size_t stacksize) {
  int ref = pthread_attr_setstack(&attr_, stackaddr, stacksize);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return  ref;
}

int ThreadAttribute::getDetachState(int *detachstate) {
  int ref = pthread_attr_getdetachstate(&attr_, detachstate);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}

int ThreadAttribute::setDetachState(int detachstate) {
  int ref = pthread_attr_setdetachstate(&attr_, detachstate);
  if (ref != 0) {
    vanilla::threadError(ref);
  }
  return ref;
}
