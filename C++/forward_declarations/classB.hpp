 #ifndef CLASSB_HEADER
 #define CLASSB_HEADER

// Forward declaration
class B;

#include <memory>
#include "classA.hpp"
class B
{
public:
    B();
    void calling_a_from_b();
    void printmsg();
private:
    std::unique_ptr<A> a;
};

#endif