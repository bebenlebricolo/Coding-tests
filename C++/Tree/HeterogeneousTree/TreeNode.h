#ifndef TREE_NODE_HEADER
#define TREE_NODE_HEADER

#include <string>
#include <memory>
#include <vector>
#include <cstring>

#ifdef TESTING
#include <iostream>
#endif

#include <sstream>

/**
 * @brief The TreeNode structure provides an implementation for a tree node, encompassing several underlying types such as int, float, std::string, etc.
 * it also comes with the possibility to store several children nodes.
*/
struct TreeNode
{
public:

    /**
     * @brief The Content structure is essentially a tagged union, which allows
     * to discriminate the active type and handle it correctly
    */
    struct Content
    {
    public:
        /**
         * @brief this enumerate type gives all types supported by this TreeNode
        */
        enum class Type
        {
            Unknown,    /**< No type specified, equivalent to void *             */
            Boolean,    /**< Stores a boolean value                              */
            String,     /**< Stores a std::string                                */
            Float,      /**< Stores a floating point value                       */
            Double,     /**< Stores a double precision floating point value      */
            Int,        /**< Stores an integer value                             */
            UInt,       /**< Stores an unsigned integer value                    */
            List        /**< Indicates that this object packs a list of children */
        };

        /**
         * @brief this union aggregates all types supported by this Content structure, less the list
         * because of its dynamic behavior (Note, this is the same with std::string type; non trivial types allocation/deallocation)
        */
        union Payload
        {
            Payload() {}
            ~Payload() {}

            void * Null {nullptr};  /**< Storage for Unknown types  */
            bool Boolean;           /**< Storage for Boolean types  */
            float Float;            /**< Storage for floating point */
            double Double;          /**< Storage for doubles        */
            int Int;                /**< Storage for integers       */
            unsigned int UInt;      /**< Storage for unsigned int   */
            std::string String;     /**< Storage for String types   */
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
        // Give the possibility to TreeNode to manipulate the internals of this Content structure (to reinforce encapsulation and linkage between the 2 types)
        friend TreeNode;
        Type type {Type::Unknown};
        Payload payload;
        std::vector<std::shared_ptr<TreeNode>> children;

        void initialize_payload();
        void initialize_payload(const Type t);
        void destroy_payload();
        void destroy_payload(const Type t);
        void copy_payload(const Content& other);
        void move_payload(Content&& other);

    }; // End of Content structure

    TreeNode() {}
    TreeNode(const std::string& _name) : name(_name)  {}
    TreeNode(const TreeNode& other) : name(other.name), content(other.content) {}
    ~TreeNode();

    template<typename T>
    TreeNode(const std::string& _name, const T& value) : name(_name)
    {
        set_value(value);
    }

    TreeNode(TreeNode&& other) : name(std::move(other.name)), content(std::move(other.content))
    {}

    void set_name(const std::string& _name) {name = _name;}
    std::string get_name() const {return name;}
    std::ostringstream print(const uint indent = 4, const uint level = 1) const;

    template<typename T>
    T get();

    std::vector<std::shared_ptr<TreeNode>>* get_list();
    std::shared_ptr<TreeNode> add_node();
    std::shared_ptr<TreeNode> get_parent();

    template<typename T>
    void set_value(const T& value);

    template<typename T>
    void set_value(T& value);

    template<typename T>
    void set_value(T&& value);

protected:
    std::shared_ptr<TreeNode> parent_node {nullptr};    /**< This field stores a pointer to a potential parent node*/
    std::string name{"Default"};
    Content content;
};


/*  ##################################################################################
    ############################## Implementation ####################################
    ################################################################################## */

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

template<>
void TreeNode::set_value<unsigned int>(unsigned int&& value)
{
    content.type = Content::Type::UInt;
    content.payload.UInt = std::move(value);
}

template<>
void TreeNode::set_value<int>(int&& value)
{
    content.type = Content::Type::Int;
    content.payload.Int = std::move(value);
}

template<>
void TreeNode::set_value<float>(float&& value)
{
    content.type = Content::Type::Float;
    content.payload.Float = std::move(value);
}

template<>
void TreeNode::set_value<double>(double&& value)
{
    content.type = Content::Type::Double;
    content.payload.Double = std::move(value);
}

TreeNode::~TreeNode()
{
    // Clears payload and recursively calls destructors for everybody
    content.destroy_payload();
}

void TreeNode::Content::initialize_payload()
{
    initialize_payload(type);
}

void TreeNode::Content::destroy_payload()
{
    destroy_payload(type);
}

void TreeNode::Content::destroy_payload(const Type t)
{
    if (t == Type::String)
    {
        using std::string;
        payload.String.~string();
    }
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
            new(&payload.String) std::string();
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

std::string surround_with_quotes(const std::string& input)
{
    std::string out = "\"" + input + "\"";
    return out;
}

std::string generate_indent(const uint indent)
{
    std::string out;
    for (uint i = 0 ;  i < indent ; i++)
    {
        out += ' ';
    }
    return out;
}

std::ostringstream TreeNode::print(const uint indent, const uint level) const
{
    std::ostringstream out;
    std::string indent_str = generate_indent(indent * level);
    out << "{" << std::endl
        << indent_str << surround_with_quotes("name") << " : " << surround_with_quotes(name) << "," << std::endl;

    switch(content.type)
    {
        case Content::Type::Boolean:
            out << indent_str << surround_with_quotes("bool") << " : " << surround_with_quotes(((content.payload.Boolean == true) ? "true" : "false")) << std::endl;
            break;

        case Content::Type::Float:
            out << indent_str << surround_with_quotes("float") << " : " << surround_with_quotes(std::to_string(content.payload.Float)) << std::endl;
            break;

        case Content::Type::UInt:
            out << indent_str << surround_with_quotes("uint") << " : " << surround_with_quotes(std::to_string(content.payload.UInt)) << std::endl;
            break;

        case Content::Type::Int:
            out << indent_str << surround_with_quotes("int") << " : " << surround_with_quotes(std::to_string(content.payload.Int)) << std::endl;
            break;

        case Content::Type::Double:
            out << indent_str << surround_with_quotes("double") << " : " << surround_with_quotes(std::to_string(content.payload.Double)) << std::endl;
            break;

        case Content::Type::String:
            out << indent_str << surround_with_quotes("string") << " : " << surround_with_quotes(content.payload.String) << std::endl;
            break;

        case Content::Type::List:
            {
                std::string indent_str = generate_indent(indent * level);
                out << indent_str << surround_with_quotes("children") << " : " << "[" << std::endl;


                for (const auto& ptr : content.children)
                {
                    // Start object node
                    indent_str = generate_indent(indent * (level + 1));
                    out << indent_str << ptr->print(indent, level + 2).str();

                    // Only add a coma for items in-between children's boundaries.
                    // Skip the last element of the vector
                    if (&ptr != &content.children.back())
                    {
                        out << "," << std::endl;
                    }
                    //out << std::endl << indent_str << "}" << std::endl;
                }
                out << std::endl << generate_indent(indent * level) << "]" << std::endl;
            }
            break;

        case Content::Type::Unknown:
        default:
            out << surround_with_quotes("Null");
            break;
    }

    if (content.type != Content::Type::Unknown)
    {
        indent_str = generate_indent(indent * (level - 1));
        out << indent_str << "}";
    }
    return out;
}


template<>
bool TreeNode::get()
{
    if (content.type == Content::Type::Boolean)
    {
        return content.payload.Boolean;
    }
    return false;
}

template<>
double TreeNode::get()
{
    if (content.type == Content::Type::Double)
    {
        return content.payload.Double;
    }
    return 0.0f;
}

template<>
float TreeNode::get()
{
    if (content.type == Content::Type::Float)
    {
        return content.payload.Float;
    }
    return 0.0f;
}

template<>
unsigned int TreeNode::get()
{
    if (content.type == Content::Type::UInt)
    {
        return content.payload.UInt;
    }
    return 0U;
}

template<>
int TreeNode::get()
{
    if (content.type == Content::Type::Int)
    {
        return content.payload.Int;
    }
    return 0U;
}

template<>
std::vector<std::shared_ptr<TreeNode>> TreeNode::get()
{
    if (content.type == Content::Type::List)
    {
        return *get_list();
    }
    return std::vector<std::shared_ptr<TreeNode>>();
}

template<>
std::string TreeNode::get()
{
    if (content.type == Content::Type::String)
    {
        return content.payload.String;
    }
    return std::string();
}

template<>
void * TreeNode::get()
{
    if (content.type == Content::Type::Unknown)
    {
        return content.payload.Null;
    }
    return nullptr;
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

std::shared_ptr<TreeNode> TreeNode::add_node()
{
    std::shared_ptr<TreeNode>* out = nullptr;
    if (content.type != Content::Type::List)
    {
        content.destroy_payload();
        content.type = Content::Type::List;
        content.initialize_payload();
    }

    std::shared_ptr<TreeNode> pointer = std::make_shared<TreeNode>();
    if (pointer != nullptr)
    {
        content.children.push_back(pointer);
        out = &pointer;
    }

    if (nullptr != out)
    {
        return *out;
    }


    return std::shared_ptr<TreeNode>(nullptr);
}




#endif /* TREE_NODE_HEADER */