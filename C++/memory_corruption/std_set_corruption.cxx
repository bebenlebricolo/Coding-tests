#include <set>
#include <iostream>

void print_set(const std::set<int>& set)
{
    std::cout << "std::set<int> = { ";
    for (const int& val : set)
    {
        std::cout << val;

        if (&val != &(*(--set.end())))
        {
            std::cout << ", ";
        }
    }
    std::cout << " }" << std::endl;
}

int main()
{
    std::set<int> set = {0,1,2,3,4,5,6,7,8,9};

    print_set(set);

    // Removes item "3" from std::set
    set.erase(3);
    print_set(set);

#ifdef WITH_EXCEPTION
    try
    {
#endif
        // Should break (cannot free an already freed member)
        set.erase(3);
#ifdef WITH_EXCEPTION
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
#endif
    print_set(set);


    return 0;
}