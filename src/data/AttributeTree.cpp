#include <data/AttributeTree.hpp>

#include <ranges>
#include <stdexcept>

namespace cpm::data {

template<typename T>
T AttributeTree::Node::getValue()
{
    if (std::holds_alternative<T>(value))
    {
        return value;
    }
    else
    {
        throw std::invalid_argument("[Attribute Tree] The node does not hold this alternative");
    }
}
} // namespace cpm::data