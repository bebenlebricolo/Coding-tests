#include "TreeNode.h"


int main()
{
    TreeNode root_node("Root");
    {
        TreeNode child ("Boolean property", true);
        root_node.set_value(child);
    }

    for (uint8_t i = 0U; i < 10U ; i++)
    {
        auto new_node = root_node.add_child();
        if (nullptr != new_node)
        {
            new_node->set_name("child node Nb " + std::to_string(i));
            new_node->set_value("This is my payload : " + std::to_string(i));
        }
    }

    return 0;
}