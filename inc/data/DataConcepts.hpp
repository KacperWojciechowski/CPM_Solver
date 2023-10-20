#include <data/AttributeTree.hpp>

#include <concepts>

namespace cpm::data {
    template<typename T>
    concept Unpackable = requires(T t, const AttributeTree& aTree) {
        {t.unpackAttributeTree(aTree)};
    };

    template<typename T>
    concept Packable = requires(T t) {
        {t.packIntoAttributeTree()} -> std::same_as<AttributeTree>;
    };

    template<typename T>
    concept Parsable = Unpackable<T> and Packable<T>;
}

