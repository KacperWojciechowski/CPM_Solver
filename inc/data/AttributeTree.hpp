#include <set>
#include <string>
#include <variant>

namespace cpm::data
{
class AttributeTree
{
    using Value = std::variant<std::size_t, int, std::string, double>;

    struct Node
    {
        std::string name;
        Value value;
        std::set<Node> children;
    };
};
} // namespace cpm::data