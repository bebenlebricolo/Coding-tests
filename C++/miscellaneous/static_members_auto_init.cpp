#include <map>
#include <string>
#include <iostream>

struct test_structure
{
    test_structure() = default;
    static int a;
    static std::map<int, std::string> mymap;
    static const std::map<int, std::string> constmap;
};

int test_structure::a = 0;

std::map<int, std::string> test_structure::mymap = {};

const std::map<int, std::string> test_structure::constmap = {
    {0, "0"},
    {1, "1"}
};


int main()
{
    test_structure::a = 36;
    std::cout << "static \"a\" field of test_structure = " << test_structure::a << std::endl;
    std::cout << "static \"mymap\" field of test_structure = " << std::endl;
    for (const auto& item : test_structure::mymap)
    {
        std::cout << item.first << " : " << item.second << std::endl;
    }

    std::cout << "static \"constmap\" field of test_structure = " << std::endl;
    for (const auto& item : test_structure::constmap)
    {
        std::cout << item.first << " : " << item.second << std::endl;
    }

    return 0;
}