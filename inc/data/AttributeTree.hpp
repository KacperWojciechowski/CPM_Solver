#include <string>
#include <variant>
#include <vector>
#include <stdexcept>

namespace cpm::data
{
class AttributeTree
{
public:
    class Node
    {
    public:
        using Subnodes = std::vector<Node>;
        using Value = std::variant<std::size_t, int, std::string, double>;

        Node() = default;
        Node(std::string name, Value value, Subnodes children = {})
        {
            this->name = name;
            this->value = value;
            this->children = children;
        }

        template<typename T>
        T getValue()
        {
            if (std::holds_alternative<T>(value))
            {
                return std::get<T>(value);
            }
            else
            {
                throw std::invalid_argument("[Attribute Tree] The node does not hold this alternative");
            }
        }

        std::string getName()
        {
            return name;
        }

        Subnodes& getChildren()
        {
            return children;
        }

        Node& setName(std::string name)
        {
            this->name = name;
            return *this;
        }

        template<typename T>
        Node& setValue(T value)
        {
            this->value = value;
            return *this;
        }

        template<typename T>
        Node& appendChild(std::string name, T value)
        {
            children.emplace_back(name, value);
            return *this;
        }
    private:

        std::string name;
        Value value;
        Subnodes children;
    };

    Node& getRoot()
    {
        return root;
    }

    void reset()
    {
        root = {};
    }

private:
    Node root = {};
};
} // namespace cpm::data
