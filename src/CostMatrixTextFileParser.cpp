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

    [[nodiscard]] auto countSeparators(std::string& line) noexcept -> std::size_t
    {
        char separator = ' ';
        return std::count(line.begin(), line.end(), separator);
    }

    [[nodiscard]] auto readJobsCount(std::ifstream& dataFile) noexcept -> std::size_t
    {
        std::string line;
        std::getline(dataFile, line);
        std::size_t separatorsCount = countSeparators(line);
        jumpToBeginning(dataFile);
        return separatorsCount + 1;
    }

    [[nodiscard]] auto parseLine(std::ifstream& file, std::size_t jobsCount) noexcept -> OpRes::Row
    {

        std::string line;
        std::getline(file, line);

        OpRes::Row row(jobsCount, OpRes::CostMatrix::NO_EDGE);

        std::istringstream strStream(line);
        std::string value;

        char separator = ' ';
        while(std::getline(strStream, value, separator))
        {
            row.emplace_back(std::stoi(value));
        }

        return row;
    }
}

namespace OpRes
{
    auto CostMatrixTextFileParser::readSourceAndFillMatrix(CostMatrix& matrix, std::string& path) -> void 
    {
        std::ifstream file(path);

        if(file.good())
        {
            std::size_t jobsCount = readJobsCount(file);
            matrix.setJobCount(jobsCount);

            std::size_t currentJobID = 0;

            while(not file.eof())
            {
                Row costRow = parseLine(file, jobsCount);
                assertRowFits(matrix, costRow);
                for(std::size_t targetJobID = 0; auto& jobCost : costRow)
                {
                    matrix.setJobTransitionCost(currentJobID, targetJobID++, jobCost);
                }
                currentJobID++;
            }
        }
    }
}

