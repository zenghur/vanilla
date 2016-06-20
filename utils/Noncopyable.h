// Copyright (c) 2016 zenghur

#ifndef Noncopyable_h
#define Noncopyable_h

namespace vanilla {

class Noncopyable {
private:
    Noncopyable(const Noncopyable &);
    const Noncopyable &operator =(const Noncopyable &);
protected:
    Noncopyable();
    ~Noncopyable();
};
    
}

#endif /* Noncopyable_h */
