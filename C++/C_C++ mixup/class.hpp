#ifndef _CLASS_HEADER_
#define _CLASS_HEADER_

class callback
{
public:
    virtual void operator()() = 0;
};

class myclass
{
public:
    myclass():cbk(nullptr){}
    myclass(callback const& c):cbk(const_cast<callback *>(&c)){}
    void set_callback(callback const& c) {cbk = const_cast<callback*>(&c);}
    auto run_callback()
    {
       if (cbk != nullptr)
        return (*cbk)();
    }
private:
    callback * cbk;
};

#endif /* _CLASS_HEADER_ */