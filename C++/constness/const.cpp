#include <cstring>
#include <iostream>
using std::cout;

int main(int argc, char**argv)
{
    int O = 0;
    const int a = 0;
    const int * b = &a;
    int * const c = &O;
    const int * const d = &O;
    //int * jerk = &a;          //KO, a value of type "const int *" cannot be used to initialize an entity of type "int *"
    int * jerk2 = (int*) &a;    //OK, Not good, but works !

    O = 3;          // Ok, non const
    //a = 3;        // KO, a is a const integer
    b = nullptr;    // OK, b is a pointer to a constant integer
    b = &O;         // idem
    //*b = 23;      // KO, dereferencing b leads to a constant integer
    //c = nullptr;  // KO, c is a const pointer, pointing to a non const value
    *c = 33;        // OK, dereferencing c gives write access to a non const value
    //d = &a;       // KO, d is a const pointer pointing a const integer
    //*d = 33;      // KO, idem
    *jerk2 = 28;


    /* Code below spits out a = 0; *jerk2 = 28
       which means that it refers to the static representation of a when we try to print a,
       and refers to the modifiable reprensation of a contained in jerk2.
       However, both variable points to the same memory address.
       This is precisely an undefined behavior of C  */
    cout << "a variable is now equal to = " << a << "\n";
    cout << "jerk2 variable is now equal to = " << *((const int*)jerk2) << "\n";
    {
        char msg[100];
        snprintf(msg,100,"a address = %p ; jerk2 value = %p", &a, (const int *)jerk2);
        cout << msg << std::endl;
    }

    return 0;
}