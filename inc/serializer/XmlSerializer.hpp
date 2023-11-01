#pragma once

#include <data/AttributeTree.hpp>
#include <data/DataConcepts.hpp>

#include <pugixml/src/pugixml.hpp>

namespace cpm::serializers {

template <cpm::data::Parsable DataType>
class XmlSerializer
{
public:
    auto traverseDocumentAndCreateTree(pugi::xml_parse_result parsedFile, cpm::data::AttributeTree pattern)
        -> cpm::data::AttributeTree
    {
        cpm::data::AttributeTree result;
        bool patternProcessed()
    }

    auto deserialize(std::string_view input) -> DataType
    {
        pugi::xml_document doc;
        auto parsedFile = doc.load_file(input.get());

        if (not parsedFile)
        {
            throw std::runtime_error("[XmlSerializer] Failed to parse file: " + input.get());
        }

        auto attrTreePattern = DataType::getAttributeTreePattern();
        auto attrTree = traverseDocumentAndCreateTree(parsedFile, attrTreePattern);
        DataType result = {};
        result.unpackAttributeTree(attrTree);
    }

    auto serialize(const DataType& outputData, std::string_view output) -> void
    {

    }
};
} // namespace cpm::serializers