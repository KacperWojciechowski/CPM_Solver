#include <set>
#include <string>
#include <string_view>
#include <variant>

namespace cpm::data
{
class AttributeTree
{
public:
    using Value = std::variant<std::size_t, int, std::string, double>;

    class Node;

    class NodeSet
    {
    public:
        // dodać iteratory

        // dodać gettery

        // dodać appendy

    private:
        friend AttributeTree;

        std::set<Node> children;
    };

    class Node
    {
    public:
        Node() {}
        Node(std::string name, Value value) : name(name), value(value) {}
        
        // dodać getChildren
        // dodać getvalue

    private:
        friend AttributeTree;

        std::string name;
        Value value;
        NodeSet children;
    };

    // dodać print

    // dodać getchildren

    auto setDataType(std::string dataName) -> void
    {
        root.value = std::move(dataName);
    }

private:
    Node root = {"DataType", ""};
};
} // namespace cpm::data
