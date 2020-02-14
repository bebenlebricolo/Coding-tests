#include <iostream>

using namespace std;

class pair
{
public:
    pair(int f, int s) : fst(f), sec(s) {}
    int first() {return fst;}
    int second() {return sec;};
private:
    int fst;
    int sec;
};

template<typename T>
struct Trait
{
    typedef T type;
    constexpr bool is_simple();
    constexpr bool is_complex();
    bool equals(T& a, T&b);
};

template<>
struct Trait<int>
{
    constexpr bool is_simple() {return true;}
    constexpr bool is_complex() {return false;}
    bool equals(int&a, int&b) {return a==b;}
};

template<>
struct Trait<::pair>
{
    constexpr bool is_simple() {return false;}
    constexpr bool is_complex() {return true;}
    bool equals(::pair &a, ::pair &b) {return ((a.first()==b.first()) && a.second() == b.second());}
};


template<typename T>
void perform_equals(T& a, T& b)
{
    Trait<T> t;
    cout << (t.equals(a,b) == true ?  "true" : "false") << endl;
}

int main()
{
    int a = 25;
    int b = 56;
    ::pair premiere(35,52);
    ::pair seconde(35,52);
    ::pair troisieme(22,52);

    perform_equals<decltype(a)>(a,b);
    perform_equals<decltype(premiere)>(premiere,seconde);
    perform_equals<decltype(premiere)>(premiere,troisieme);

    return 0;
}