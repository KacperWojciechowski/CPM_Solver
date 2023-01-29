#pragma once

#include <stdexcept>

#include <Network.h>
#include <ICostMatrixParser.hpp>

namespace OpRes
{
    class NetBuilder
    {
        public:

        auto setFileParser(const ICostMatrixParser* fileParser) -> void;

        [[nodiscard]] auto buildFromFile(const std::string& filePath) -> Network;
        [[nodiscard]] auto buildEmpty() -> Network;

        private:
        auto assertFileParserSet() -> void
        {
            if(!parser)
            {
                throw std::runtime_error("Parser not set");
            }
        }

        auto assertMatrixIsSquare() -> void
        {

        }

        ICostMatrixParser* parser = nullptr;
    };
}