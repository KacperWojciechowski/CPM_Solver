#include <ICostMatrixParser.hpp>
#include <string>

namespace OpRes
{
    class CostMatrixTextFileParser : public ICostMatrixParser
    {
    public:

        virtual auto readSourceAndFillMatrix(CostMatrix& matrix, std::string& path) -> void override;
    };
}