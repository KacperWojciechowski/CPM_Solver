#include <string>
#include <variant>
#include <vector>
#include <stdexcept>
#include <optional>

namespace cpm::data
{
class AttributeTree
{
public:
    AttributeTree(std::string rootName)
    {
        root.setName(rootName);
    }

    class Node
    {
    public:
        using Subnodes = std::vector<Node>;
        using Value = std::variant<std::size_t, int, std::string, double>;

        Node() = default;
        Node(std::string name, std::optional<Value> value, Subnodes children = {})
        {
            this->name = name;
            this->value = value;
            this->children = children;
        }

        template<typename T>
        auto getValue() -> std::optional<T>
        {
            if (value && std::holds_alternative<T>(value.value()))
            {
                return std::get<T>(value.value());
            }
            return std::nullopt;
        }

        auto getName() const noexcept -> std::string
        {
            return name;
        }

        auto getChildren() noexcept -> Subnodes&
        {
            return children;
        }

        auto getAttributes() noexcept -> Subnodes&
        {
            return attributes;
        }

        auto getChildren() const noexcept -> const Subnodes&
        {
            return children;
        }

        auto getAttributes() const noexcept -> const Subnodes&
        {
            return attributes;
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

        template<typename T, typename OptVal = std::optional<T>>
        auto appendChild(std::string name, OptVal value = std::nullopt) -> Node&
        {
            children.emplace_back(name, value);
            return *this;
        }
    private:
        std::string name;
        std::optional<Value> value;
        Subnodes children;
        Subnodes attributes;
    };

    auto getRoot() -> Node&
    {
        return root;
    }

    auto reset() -> void
    {
        Node newRoot = {};
        newRoot.setName(root.getName());
        root = std::move(newRoot);
    }

private:
    Node root = {};
};
} // namespace cpm::data
