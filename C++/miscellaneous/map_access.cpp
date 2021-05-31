#include <map>
#include <string>
enum class TestEnum
{
    ValDefault,
    Val1,
    Val2,
    Val3,
};

int main()
{
    const std::map<TestEnum,std::string> myconstmap {
        {TestEnum::ValDefault, "ValDefault"},
        {TestEnum::Val1, "Val1"},
        {TestEnum::Val2, "Val2"},
        {TestEnum::Val3, "Val3"},
    };

    std::map<TestEnum,std::string> mymap {
        {TestEnum::ValDefault, "ValDefault"},
        {TestEnum::Val3, "Val3"},
    };

    auto valdefault = mymap[TestEnum::ValDefault];
    auto constvaldefault = myconstmap[TestEnum::ValDefault];

    return 0;
}