#include <data/AttributeTree.hpp>

namespace {
using NodeSet = std::set<cpm::data::AttributeTree::Node>;

auto contains(const NodeSet& nodeSet, std::string_view nodeName) -> bool
{
    return false;
}
} // namespace

namespace cpm::data {
auto AttributeTree::contains(std::string_view nodeName) const noexcept -> bool
{
    if (root.name == nodeName) return true;
    return ::contains(root.children, nodeName);
}
} // namespace cpm::data
