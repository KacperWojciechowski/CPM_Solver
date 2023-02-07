#include <IJobMatrixParser.hpp>
#include <string>

namespace OpRes
{
    class JobMatrixTextFileParser : public IJobMatrixParser
    {
    public:

        static constexpr char separator = ' ';

        virtual auto readSourceAndFillMatrix(JobMatrix& matrix, std::optional<std::string> path = std::nullopt) const -> void override;

        virtual ~JobMatrixTextFileParser() {};
    };
}