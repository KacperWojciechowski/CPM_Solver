#pragma once

#include <Network.h>
#include <ICostMatrixParser.hpp>

namespace OpRes
{
    class NetBuilder
    {
    public:

        auto setFileParser(const ICostMatrixParser* fileParser) -> void;

        [[nodiscard]] auto buildFromFile(const std::string& filePath) -> Network;

    private:

        ICostMatrixParser* parser = nullptr;
        Network network;
    };
}