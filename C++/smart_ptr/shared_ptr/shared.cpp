#include <iostream>
#include <string>
#include <memory>

struct toto
{
    explicit toto();
    explicit toto(int _a, int _b) : a(_a), b(_b) {}

private:
    int a;
    int b;
};

int main (int argc, char** argv)
{
    (void) argc;
    (void) argv;

#ifndef START_WITH_SHARED
    toto* t1 = new toto(23,45);
#else
    auto t1 = std::make_shared<toto>(12,24);
#endif
{
    // Catch t1 address and encapsulate it into a shared_ptr
    std::shared_ptr<toto> t1_sh(t1);
    std::cout << "References to t1 : " << t1_sh.use_count() << std::endl;
    {
        std::shared_ptr<toto> t2_sh = t1_sh;
        std::cout << "References to t1 : " << t1_sh.use_count() << std::endl;
    }
    std::cout << "References to t1 : " << t1_sh.use_count() << std::endl;
}

#ifndef START_WITH_SHARED
    std::cout << "t1 = " << t1 << std::endl;
    delete t1;
#else
    std::cout << "t1 = " << t1.use_count() << std::endl;
#endif

    return 0;
}