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
        auto getValue() -> T
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

        auto getName() -> std::string
        {
            return name;
        }

        auto getChildren() -> Subnodes&
        {
            return children;
        }

        auto setName(std::string name) -> Node&
        {
            this->name = name;
            return *this;
        }

        template<typename T>
        auto setValue(T value) -> Node&
        {
            this->value = value;
            return *this;
        }

        template<typename T>
        auto appendChild(std::string name, T value) -> Node&
        {
            children.emplace_back(name, value);
            return *this;
        }
    private:

        std::string name;
        Value value;
        Subnodes children;
    };

    auto getRoot() -> Node&
    {
        return root;
    }

    auto reset() -> void
    {
        root = {};
    }

private:
    Node root = {};
};
} // namespace cpm::data
