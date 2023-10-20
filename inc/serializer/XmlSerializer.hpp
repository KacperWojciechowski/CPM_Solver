#pragma once

#include <serializer/Serializer.hpp>

#include <pugixml/src/pugixml.hpp>

namespace cpm::serializers {

template <cpm::data::Parsable DataType>
class XmlSerializer : public Serializer<XmlSerializer, DataType>
{
public:
    auto deserialize(std::string_view input) -> DataType
    {
        pugi::xml_document doc;
        auto parsedFile = doc.load_file(input.get());

        if (not parsedFile)
        {
            throw std::runtime_error("[XmlSerializer] Failed to parse file: " + input.get());
        }

        data::AttributeTree attrTree;

    }

    auto serialize(const DataType& outputData, std::string_view output) -> void
    {

    }
};
} // namespace cpm::serializers