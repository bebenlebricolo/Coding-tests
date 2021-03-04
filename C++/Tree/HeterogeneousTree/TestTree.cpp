#include "TreeNode.h"
#include <iostream>
#include <cstdint>

int main()
{
    TreeNode root_node("Root");
    {
        TreeNode child ("Boolean property", true);
        root_node.set_value(child);
    }

    for (uint8_t i = 0U; i < 5U ; i++)
    {
        auto new_node = root_node.add_node();
        if (nullptr != new_node)
        {
            new_node->set_name("child node Nb " + std::to_string(i));
            for (uint8_t j = 0 ;  j < 3U ; j++)
            {
                auto insider = new_node->add_node();
                if (nullptr != insider)
                {
                    insider->set_name("Temp property #" + std::to_string(j));
                    insider->set_value(j*4);
                }
            }
        }
    }

    std::cout << root_node.print(2U, 1U).str() << std::endl;
    return 0;
}