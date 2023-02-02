#include <NetBuilder.hpp>

namespace
{
    auto assertFileParserSet(OpRes::ICostMatrixParser* parser) -> void
    {
        if(!parser)
        {
            throw std::runtime_error("Parser not set");
        }
    }
}

namespace OpRes
{
    auto NetBuilder::buildFromFile(const std::string& filePath) -> Network
    {
        assertFileParserSet(parser);

    }
}
