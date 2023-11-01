#include "serializer/XmlSerializer.hpp"

#include <algorithm>

namespace cpm::serializers {
auto XmlSerializer::dfsDeserializeTraverse(cpm::data::AttributeTree::Node& currentPatternNode,
                cpm::data::AttributeTree::Node& currentResultNode,
                pugi::xml_document& doc)
    const noexcept -> void
{
    for (auto& node : currentPatternNode.getChildren())
    {
        for(auto child = doc.child(node.getName().c_str()); child; child.next_sibling(node.getName().c_str()))
        {
            child.value() == "" ? currentResultNode.appendChild(node.getName())
                                : currentResultNode.appendChild(node.getName(), child.value());
        }
        std::ranges::for_each(currentResultNode.getChildren(), [this, &node, &doc](auto& resultNode) {
            dfsDeserializeTraverse(node, resultNode, doc);
        });
    }
}
}