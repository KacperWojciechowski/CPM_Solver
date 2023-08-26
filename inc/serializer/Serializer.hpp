#include <data/DataConcepts.hpp>

#include <iostream>
#include <string_view>

namespace cpm::serializers {

template<class SerializerType, cpm::data::Parsable DataType>
class Serializer
{
public:
    auto deserialize(std::string_view input) -> DataType
    {
        serializerHandler->deserialize(input);
    }

    auto serialize(const DataType& outputData, std::string_view output) -> void
    {
        serializerHandler->serialize(outputData, output);
    }

private:
    SerializerType serializerHandler;
}
} // namespace cpm::serializers