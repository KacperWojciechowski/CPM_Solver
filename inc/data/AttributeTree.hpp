#include <set>
#include <string>

namespace cpm::data
{
class AttributeTree
{
    union Value 
    {
        std::size_t asSizet;
        int asInt;
        std::string asString;
        double asDouble;
    };

    struct Node
    {
        std::string name;
        Value value;
        std::set<Node> children;
    }
}
}