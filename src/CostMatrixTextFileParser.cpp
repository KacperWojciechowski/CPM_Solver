#include <CostMatrixTextFileParser.hpp>

#include <sstream>

namespace OpRes
{
    
    auto CostMatrixTextFileParser::readSourceAndFillMatrix(CostMatrix& matrix, std::string& path) -> void 
    {
        std::ifstream file(path);

        Matrix tempMatrix;

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

    auto CostMatrixTextFileParser::parseLine(std::ifstream& file, std::size_t jobsCount) noexcept -> Row
    {
        std::string line;
        std::getline(file, line);

        Row row(jobsCount, NO_EDGE);

        std::istringstream strStream(line);
        std::string value;

        while(std::getline(strStream, value, ' '))
        {
            row.emplace_back(std::stoi(value));
        }

        return row;
    }
}

