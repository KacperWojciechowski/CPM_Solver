#include <NetBuilder.hpp>

#include <stdexcept>

namespace
{
    auto assertFileParserSet(const OpRes::IJobMatrixParser* parser) -> void
    {
        if(!parser)
        {
            throw std::runtime_error("Parser not set");
        }
    }
}

namespace OpRes
{
    auto NetBuilder::sourceDataFile(const std::string& filePath) -> NetBuilder&
    {
        assertFileParserSet(parser);
        parser->readSourceAndFillMatrix(jobMatrix, filePath);
        return *this;
    }
}
