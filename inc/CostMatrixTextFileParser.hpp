#include <ICostMatrixParser.hpp>
#include <fstream>
#include <string>
#include <algorithm>

namespace OpRes
{
    class CostMatrixTextFileParser : public ICostMatrixParser
    {
    public:

        virtual auto readSourceAndFillMatrix(CostMatrix& matrix, std::string& path) -> void override;

    private:

        auto jumpToBeginning(std::ifstream& file) -> void
        {
            file.clear();
            file.seekg(std::ios_base::beg);
        }

        [[nodiscard]] inline auto countSeparators(std::string& line) -> std::size_t
        {
            char separator = ' ';
            return std::count(line.begin(), line.end(), separator);
        }

        [[nodiscard]] inline auto readJobsCount(std::ifstream& dataFile) -> std::size_t
        {
            std::string line;
            std::getline(dataFile, line);
            std::size_t separatorsCount = countSeparators(line);
            jumpToBeginning(dataFile);
            return separatorsCount + 1;
        }

        [[nodiscard]] auto parseLine(std::ifstream& file, std::size_t jobsCount) noexcept -> Row;
    };
}