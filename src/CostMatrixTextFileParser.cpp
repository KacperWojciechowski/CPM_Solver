#include <CostMatrixTextFileParser.hpp>

#include <algorithm>
#include <fstream>
#include <sstream>

namespace
{
    auto jumpToBeginning(std::ifstream& file) -> void
    {
        file.clear();
        file.seekg(std::ios_base::beg);
    }

    [[nodiscard]] auto readJobsCount(std::ifstream& dataFile) noexcept -> std::size_t
    {
        using TextParser = OpRes::CostMatrixTextFileParser;

        std::string line;
        std::getline(dataFile, line);
        std::size_t separatorsCount = TextParser::countSeparators(line, TextParser::separator);
        jumpToBeginning(dataFile);
        return separatorsCount + 1;
    }

    [[nodiscard]] auto parseLine(std::ifstream& file, std::size_t jobsCount) noexcept -> OpRes::Row
    {
        using TextParser = OpRes::CostMatrixTextFileParser;

        std::string line;
        std::getline(file, line);

        OpRes::Row row;
        row.reserve(jobsCount);

        std::istringstream strStream(line);
        std::string value;

        while(std::getline(strStream, value, TextParser::separator))
        {
            row.emplace_back(std::stoi(value));
        }

        return row;
    }

    auto fillCostMatrix(OpRes::CostMatrix& matrix, std::ifstream& file, std::size_t jobsCount) -> void
    {
        std::size_t currentJobID = 0;

        while(not file.eof())
        {
            OpRes::Row costRow = parseLine(file, jobsCount);
            matrix.assertRowFits(costRow);
            matrix.setJobTransitionRow(currentJobID++, std::move(costRow));
        }
    }
}

namespace OpRes
{
    auto CostMatrixTextFileParser::readSourceAndFillMatrix(CostMatrix& matrix, std::optional<std::string> path) -> void
    {
        std::ifstream file(*path);

        if(file.good())
        {
            std::size_t jobsCount = readJobsCount(file);
            matrix.setJobCount(jobsCount);
            fillCostMatrix(matrix, file, jobsCount);
        }
    }
}

