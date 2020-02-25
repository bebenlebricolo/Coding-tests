#include <iostream>
using namespace std;



int main(void)
{
    int sig = -56;
    unsigned int unsig = 33;
    double d = 0;

    auto toto = static_cast<decltype(unsig)>(sig);
    cout << "sig = " << sig << "\n";
    cout << "unsig = " << unsig << "\n";
    cout << "static_cast<unsigned>(sig) = " << toto << "\n";

    return 0;
}