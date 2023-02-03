#include <NetBuilder.hpp>

#include <CostMatrix.hpp>

#include <stdexcept>

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

        CostMatrix costMatrix;
        parser->readSourceAndFillMatrix(costMatrix, filePath);

        // create new network instance
        network = {};

        // add filling network with data

        return network;
    }
}
