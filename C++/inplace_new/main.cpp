#include <string>
#include <cstring>
#include <filesystem>

union TestUnion
{
    TestUnion() {}
    ~TestUnion(){}
    struct
    {
        char name[90];
    } reg;

    struct
    {
        std::string name;
    } std;

    struct
    {
        std::filesystem::path path;
    } p;
};

void build_test(TestUnion& p_test)
{
    const std::string yolo = "yolo";
    const std::string yalaa = "yalaa";
    const std::filesystem::path path = std::filesystem::temp_directory_path() / "titi";

    new(&p_test.std.name) std::string(yolo);
    new(&p_test.std.name) std::string(yalaa);
    new(&p_test.p.path) std::filesystem::path(path);
    strncpy(p_test.reg.name, "Rewrite name ! with a supeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeer long string", 80 );
}

int main()
{
    TestUnion test;
    build_test(test);

    return 0;
}