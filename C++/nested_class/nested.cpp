#include <iostream>

namespace toto
{
class out
{
public:
    struct in
    {
        enum class inside
        {
            Hello,
            Goodbye
        };
        in();
    };

    out()=default;
};
out::in tata;
out::in::in(){}
}

toto::out::in titi;

int main(int argc, char ** argv)
{
    return 0;
}