#pragma once
#include "shared_ptr.h"
#include <iostream>

class Counter
{
public:
    Counter() : _useCount(0), _weakCount(0) {}
    void incUse() { ++_useCount; }
    void incWeak() { ++_weakCount; }
    void decUse() { --_useCount; }
    void decWeak() { --_weakCount; }
    int getUse() const { return _useCount; }
    int getWeak() const { return _weakCount; }
private:
    int _useCount;
    int _weakCount;
};


template <class T>
class WeakPtr
{
public:
    WeakPtr() : _shared(NULL), _counter(NULL) {
        _counter->incWeak();
    }
    WeakPtr(SharedPtr<T>& p) : _shared(&p), _counter(p._counter)
    {
        _counter->incWeak();
    }
    ~WeakPtr()
    {
        decrementRef();
    }
    WeakPtr(const WeakPtr<T>& wp)
    {
        _counter = NULL;
        *this = wp;
    }

    const WeakPtr<T>& operator = (const WeakPtr<T>& weakPtr)
    {
        decrementRef();
        _counter = weakPtr._counter;
        _shared = weakPtr._shared;
        _counter->incWeak();
        return *this;
    }
    bool expired() const { return _counter->getUse() == 0; }
    T* operator -> () const
    {
        if (expired())
            throw "Pointer is not longer valid.";
        return _shared->get();
    }
    const T& operator * () const
    {
        if (expired())
            throw "Pointer is not longer valid.";
        return *_shared->get();
    }

private:
    void decrementRef(void)
    {
        if (_counter == NULL)
            return;
        _counter->decWeak();
        if (_counter->getWeak() == 0)
            delete _counter;
    }
    SharedPtr<T>* _shared;
    Counter* _counter;

    friend class shared_ptr;

};


    