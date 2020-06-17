#pragma once

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

class weak_ptr;

template <class T>
class SharedPtr
{
public:
    SharedPtr(T* p) : _p(p) {
        _counter->incUse();
        _counter->incWeak();
    }
    ~SharedPtr() { decrementRef(); }
    SharedPtr(const SharedPtr<T>& p) : _counter(NULL)
    {
        *this = p;
    }
    const SharedPtr<T>& operator = (const SharedPtr<T>& sp)
    {
        decrementRef();
        _p = sp._p;
        _counter = sp._counter;
        _counter->incUse();
        return *this;
    }

    T* operator -> () const { return _p; }
    T operator * () const { return *_p; }
private:
    T* _p;
    Counter* _counter;
    void decrementRef()
    {
        if (_counter == NULL) return;
        _counter->decUse();
        _counter->decWeak();

        if (_counter->getUse() == 0 && _counter->getWeak()==0 )
        {
            delete _p;
            delete _counter;
        }
    }

};
