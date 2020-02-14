#include <iostream>
#include <string>

using namespace std;

class toto
{
public:
    toto(int i) : a(i), b(2*i), c(3*i) , pa(4*i), pb(5*i) {};
    toto(const toto& from)=default;

    virtual void say_hello() const noexcept {std::cout << "Hello from toto!" << endl;}
    virtual void print() const noexcept
    {
        cout << "Class toto : \n"
             << "protected:\n"
             << " a = " << to_string(a) << endl
             << " b = " << to_string(b) << endl
             << " c = " << to_string(c) << endl
             << "private:\n"
             << " pa = " << to_string(pa) << endl
             << " pb = " << to_string(pb) << endl << endl;
    }
protected:
    int a;
    int b;
    int c;
private:
    int pa;
    int pb;
};

class tata : public toto
{
public:
    tata(int i) : toto(i), d(6*i), e(7*i), pd(8*i) , pe(9*i){};
    tata(const tata& from) : toto(from)
    {
        d = from.d;
        pd = from.pd;
        pe = from.pe;
    }

    virtual void say_hello() const noexcept override {std::cout << "Hello from tata!" << endl;}
    virtual void print() const noexcept override
    {
        cout << "\nClass tata : \n";
        toto::print();
        cout << "protected:" << endl
        << " d = " << to_string(d) << endl
        << " e = " << to_string(e) << endl
        << "private:" << endl
        << " pd = " << to_string(pd) << endl
        << " pe = " << to_string(pe) << endl << endl;
    }
protected:
    int d;
    int e;
private:
    int pd;
    int pe;
};

class titi final : public tata
{
public:
    titi(int i) : tata(i), pf(i*10), pg(i*11){}
    titi(const titi& from) : tata(from)
    {
        pf = from.pf;
        pg = from.pg;
    }
    virtual void say_hello() const noexcept override {std::cout << "Hello from titi!" << endl;}
    virtual void print() const noexcept override
    {
        cout << "\nClass titi :";
        tata::print();
        cout << "private:" << endl
        << " pg = " << to_string(pg) << endl
        << " pf = " << to_string(pf) << endl << endl;
    }
private:
    int pf;
    int pg;
};


int main(int argc, char ** argv)
{
    toto to(1);
    tata ta(2);
    titi ti(3);

    to.say_hello();
    ta.say_hello();
    ti.say_hello();

    to.print();
    ta.print();
    ti.print();

    try
    {
        throw titi(4);
    }
    catch (const titi& t)
    {
        t.print();
    }

    return 0;
}