#include <iostream>
#include <string>

using namespace std;

class toto
{
public:
    explicit toto(const string& msg) : _what(msg) {}
    toto(const toto& other)
    {
        _what = other._what;
    }
    virtual ~toto()=default;
    virtual const char* what() const noexcept {return _what.c_str();}
protected:
    string _what;
};

class tata : public toto
{
public:
    tata(const tata& other) : toto(other)
    {
        _name = other._name;
    }
    explicit tata(const string& msg, const string& n) : toto(msg) , _name(n) {}
    virtual ~tata()=default;
    virtual const char* what() const noexcept override
    {
        return string(_what + "\nName : " + _name + "\n\n").c_str();
    }
private:
    string _name;
};



void foo()
{
    throw tata("Hello bro!","This is tata!");
}

void bar()
{
    throw toto("Hello from toto!\n");
}

int main(int argc, char ** argv)
{
    (void) argc;
    (void) argv;

    for (uint8_t i = 0 ;  i < 2 ; i++)
    {
        try {

            if (0 == i)
            {
                foo();
            }
            else
            {
                bar();
            }
        }
        // Use the most specialised handlers before going to the lesser ones
        catch (const tata& e)
        {
            cout << "Caught tata exception !" << endl;
            cout << e.what();
        }
        // More general case
        catch (const toto &e)
        {
            cout << "Caught toto exception !" << endl;
            cout << e.what();
        }
    }

    /* Will generate a warning from g++ and msvc++ compilers
       because DerivedClass will always be caught by BaseClass
       handler first (i.e. toto exception handler)              */
    try
    {
        foo();
    }
    catch(const toto& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const tata& e)
    {
        std::cerr << e.what() << '\n';
    }


    return 0;
}