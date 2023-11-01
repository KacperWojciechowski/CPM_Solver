#pragma once

#include <data/AttributeTree.hpp>
#include <data/DataConcepts.hpp>

#include <pugixml/src/pugixml.hpp>

namespace cpm::serializers {

class XmlSerializer
{
public:
    template <cpm::data::Parsable DataType>
    auto deserialize(std::string_view input) -> DataType
    {
        pugi::xml_document doc;
        auto parsedFile = doc.load_file(input.data());

        if (not parsedFile)
        {
            throw std::runtime_error(std::string("[XmlSerializer] Failed to parse file: ") + input.data());
        }

        auto attrTreePattern = DataType::getAttributeTreePattern();
        auto attrTree = traverseDocumentAndCreateTree(parsedFile, attrTreePattern);
        DataType result = {};
        result.unpackAttributeTree(attrTree);
        return result;
    }

    template <cpm::data::Parsable DataType>
    auto serialize(const DataType& outputData, std::string_view output) -> void
    {

    }

private:
    auto traverseDocumentAndCreateTree(pugi::xml_document doc, cpm::data::AttributeTree pattern)
        -> cpm::data::AttributeTree
    {
        cpm::data::AttributeTree result(pattern.getRoot().getName());
        dfsDeserializeTraverse(pattern.getRoot(), result.getRoot(), doc);
        return result;
    }

    auto dfsDeserializeTraverse(cpm::data::AttributeTree::Node& currentPatternNode,
                                cpm::data::AttributeTree::Node& currentResultNode,
                                pugi::xml_document& doc) const noexcept -> void;
};
} // namespace cpm::serializers