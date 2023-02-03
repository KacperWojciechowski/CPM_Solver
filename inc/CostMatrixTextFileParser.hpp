#include <ICostMatrixParser.hpp>
#include <string>

namespace OpRes
{
    class CostMatrixTextFileParser : public ICostMatrixParser
    {
    public:

        static constexpr char separator = ' ';

        virtual auto readSourceAndFillMatrix(CostMatrix& matrix, std::optional<std::string> path = std::nullopt) -> void override;

        virtual ~CostMatrixTextFileParser() {};
    };
}