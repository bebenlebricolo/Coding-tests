 #ifndef CLASSA_HEADER
 #define CLASSA_HEADER

// Forward declaration
class A;

#include <memory>
#include "classB.hpp"
class A
{
public:
    A();
    void set_b(B& _b);
    void calling_b_from_a();
    void printmsg();
private:
   std::unique_ptr<B> b;
};

#endif