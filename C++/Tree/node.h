#ifndef NODE_HEADER
#define NODE_HEADER

#include <string>
#include <vector>
#include <memory>
#include <any>

struct Node
{
    Node (const std::string& _name) : name(_name)
    {}
    Node (const std::string& _name, const Node& _parent) : name(_name), parent(&_parent)
    {}
    Node (const std::string& _name, Node const * _parent) : name(_name), parent(_parent)
    {}

    void add_child(Node& n)
    {
        n.parent = this;
        children.push_back(std::shared_ptr<Node>(&n));
    }

    std::string name;
    Node const * parent = nullptr;
    std::vector<std::shared_ptr<Node>> children;
    std::any value;

};

#endif /* NODE_HEADER */