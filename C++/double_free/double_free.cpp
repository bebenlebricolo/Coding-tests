#include <iostream>
#include <string>

int main()
{
    char* toto;
    std::cout << "Toto value is : " << static_cast<void*>(toto) << std::endl;
    toto = new char[28];
    std::cout << "Toto value after allocation is : " << static_cast<void*>(toto) << std::endl;
    
    delete toto;
    std::cout << "Toto value after delete is : " << static_cast<void*>(toto) << std::endl;
   
    char* old_toto = toto;
    toto = nullptr;
    delete toto;
    std::cout << "Toto value after double delete is : " << static_cast<void*>(toto) << std::endl;

    // Uncomment the line below to trigger a segmentation fault : double free detected
    // delete old_toto;
    return 0;
}

