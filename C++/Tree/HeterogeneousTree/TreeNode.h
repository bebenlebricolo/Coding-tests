#ifndef TREE_NODE_HEADER
#define TREE_NODE_HEADER

#include <string>
#include <memory>
#include <vector>
#include <cstring>

#ifdef TESTING
#include <iostream>
#endif

struct TreeNode
{
    struct Content
    {
    public:
        enum class Type
        {
            Unknown,
            Boolean,
            String,
            Float,
            Double,
            Int,
            UInt,
            List
        };

        union Payload
        {
            Payload() {}
            ~Payload() {}

            bool Boolean;
            std::string String;
            float Float;
            double Double;
            int Int;
            unsigned int UInt;
        };

        Content() : type(Type::Unknown)
        {
            initialize_payload(type);
        }

        Content(const Type _type) : type(_type)
        {
            initialize_payload(type);
        }

        Content(const Content& other) : type(other.type)
        {
            copy_payload(other);
        }

        Content(Content&& other) : type(std::move(other.type))
        {
            move_payload(std::move(other));
        }

    protected:
        friend TreeNode;
        Type type {Type::Unknown};
        Payload payload;
        std::vector<std::shared_ptr<TreeNode>> children;

        void initialize_payload();
        void initialize_payload(const Type t);
        void copy_payload(const Content& other);
        void move_payload(Content&& other);

    };

    TreeNode() {}
    TreeNode(const std::string& _name) : name(_name)  {}
    TreeNode(const TreeNode& other) : name(other.name), content(other.content) {}
    ~TreeNode()
    {
        // Clears payload and recursively calls destructors for everybody
        content.initialize_payload();
    }

    template<typename T>
    TreeNode(const std::string& _name, const T& value) : name(_name)
    {
        set_value(value);
    }

    TreeNode(TreeNode&& other) : name(std::move(other.name)), content(std::move(other.content))
    {}

    void set_name(const std::string& _name) {name = _name;}
    std::string get_name() const {return name;}
    std::vector<std::shared_ptr<TreeNode>>* get_list();
    std::shared_ptr<TreeNode> add_child();

    template<typename T>
    void set_value(const T& value);
    //{
    //    (void) value;
    //}

    template<typename T>
    void set_value(T& value);
    //{
    //    (void) value;
    //}

    template<typename T>
    void set_value(T&& value);
    //{
    //    (void) value;
    //}

protected:
    std::string name{"Default"};
    Content content;
};

template<>
void TreeNode::set_value<bool>(const bool& value)
{
    content.payload.Boolean = value;
    content.type = Content::Type::Boolean;
}

template<>
void TreeNode::set_value<std::string>(const std::string& value)
{
    content.payload.String = value;
    content.type = Content::Type::String;
}

template<>
void TreeNode::set_value<std::string>(std::string&& value)
{
    content.initialize_payload(Content::Type::String);
    content.payload.String = std::move(value);
    content.type = Content::Type::String;
}

template<>
void TreeNode::set_value<float>(const float& value)
{
    content.payload.Float = value;
    content.type = Content::Type::Float;
}

template<>
void TreeNode::set_value<TreeNode>(const TreeNode& value)
{
    auto pointer = std::make_shared<TreeNode>(value);
    if (pointer != nullptr)
    {
        content.type = Content::Type::List;
        content.initialize_payload();
        content.children.push_back(pointer);
    }
}

template<>
void TreeNode::set_value<TreeNode>(TreeNode& value)
{
    auto pointer = std::make_shared<TreeNode>(value);
    if (pointer != nullptr)
    {
        content.type = Content::Type::List;
        content.initialize_payload();
        content.children.push_back(pointer);
    }
}

template<>
void TreeNode::set_value<TreeNode>(TreeNode&& value)
{
    auto pointer = std::make_shared<TreeNode>(std::move(value));
    if (pointer != nullptr)
    {
        content.type = Content::Type::List;
        content.initialize_payload();
        content.children.push_back(pointer);
    }
}


void TreeNode::Content::initialize_payload()
{
    initialize_payload(type);
}

void TreeNode::Content::initialize_payload(const Type t)
{
    switch(t)
    {
        case Type::Boolean:
            payload.Boolean = false;
            break;

        case Type::Float:
            payload.Float = 0.0f;
            break;

        case Type::UInt:
            payload.UInt = 0U;
            break;

        case Type::Int:
            payload.Int = 0U;
            break;

        case Type::Double:
            payload.Double = false;
            break;

        case Type::String:
            payload.String = "";
            break;

        case Type::List:
        case Type::Unknown:
        default:
            break;
    }
}

void TreeNode::Content::copy_payload(const Content& other)
{
    switch(other.type)
    {
        case Type::Boolean:
            payload.Boolean = other.payload.Boolean;
            break;

        case Type::Float:
            payload.Float = other.payload.Float;
            break;

        case Type::UInt:
            payload.UInt = other.payload.UInt;
            break;

        case Type::Int:
            payload.Int = other.payload.Int;
            break;

        case Type::Double:
            payload.Double = other.payload.Double;
            break;

        case Type::String:
            payload.String = other.payload.String;
            break;

        case Type::List:
            children = other.children;
            break;

        case Type::Unknown:
        default:
            break;
    }
}

void TreeNode::Content::move_payload(Content&& other)
{
    switch(other.type)
    {
        case Type::Boolean:
            payload.Boolean = std::move(other.payload.Boolean);
            break;

        case Type::Float:
            payload.Float =  std::move(other.payload.Float);
            break;

        case Type::UInt:
            payload.UInt =  std::move(other.payload.UInt);
            break;

        case Type::Int:
            payload.Int =  std::move(other.payload.Int);
            break;

        case Type::Double:
            payload.Double =  std::move(other.payload.Double);
            break;

        case Type::String:
            payload.String =  std::move(other.payload.String);
            break;

        case Type::List:
            children =  std::move(other.children);
            break;

        case Type::Unknown:
        default:
            break;
    }
}

std::vector<std::shared_ptr<TreeNode>>* TreeNode::get_list()
{
    std::vector<std::shared_ptr<TreeNode>>* out = nullptr;
    if (content.type == Content::Type::List)
    {
        out = &content.children;
    }
    return out;
}

std::shared_ptr<TreeNode> TreeNode::add_child()
{
    std::shared_ptr<TreeNode>* out = nullptr;
    if (content.type == Content::Type::List)
    {
        std::shared_ptr<TreeNode> pointer = std::make_shared<TreeNode>();
        if (pointer != nullptr)
        {
            content.children.push_back(pointer);
            out = &pointer;
        }
    }

    if (nullptr != out)
    {
        return *out;
    }

    return std::shared_ptr<TreeNode>(nullptr);
}




#endif /* TREE_NODE_HEADER */