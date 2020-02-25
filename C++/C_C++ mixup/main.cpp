#include "c_functions.h"
#include "class_collection.hpp"
#include "class.hpp"
#include <iostream>

using namespace std;

class callback_1 : public callback
{
public:
    void operator()() override
    {
        cout << "Calling callback 1" << endl;
    }
};

class callback_2 : public callback
{
public:
    void operator()() override
    {
        cout << "Calling callback 2" << endl;
    }
};

class callback_3 : public callback
{
public:
    void operator()() override
    {
        cout << "Calling callback 3" << endl;
    }
};

class c_cbk_1 : public callback
{
public:
    void operator()() override
    {
        char msg[50] = "Calling c callback 1 using c functions\n";
        print_stuff_to_screen(msg,50);
    }
};

class c_cbk_2 : public callback
{
public:
    void operator()() override
    {
        char msg[50] = "Calling c callback 2 using c functions\n";
        print_stuff_to_screen(msg,50);
    }
};

class c_cbk_3 : public callback
{
public:
    void operator()() override
    {
        char msg[50] = "Calling c callback 3 using c functions\n";
        print_stuff_to_screen(msg,50);
    }
};


int main()
{
    callback_1 cbk1;
    callback_2 cbk2;
    callback_3 cbk3;
    class_collection[CLASS_1].set_callback(cbk1);
    class_collection[CLASS_2].set_callback(cbk2);
    class_collection[CLASS_3].set_callback(cbk3);

    // from c interface
    run_callback(CLASS_1);
    run_callback(CLASS_2);
    run_callback(CLASS_3);

    // natively from C functions, using C++ under the hood
    use_classes_callback(CLASS_1);
    use_classes_callback(CLASS_2);
    use_classes_callback(CLASS_3);

    c_cbk_1 c_cbk1;
    c_cbk_2 c_cbk2;
    c_cbk_3 c_cbk3;

    class_collection[CLASS_1].set_callback(c_cbk1);
    class_collection[CLASS_2].set_callback(c_cbk2);
    class_collection[CLASS_3].set_callback(c_cbk3);

    // from c interface
    run_callback(CLASS_1);
    run_callback(CLASS_2);
    run_callback(CLASS_3);

    // natively from C functions, using C++ under the hood
    use_classes_callback(CLASS_1);
    use_classes_callback(CLASS_2);
    use_classes_callback(CLASS_3);


    return 0;
}