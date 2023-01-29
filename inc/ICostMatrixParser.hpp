#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#include <CostMatrix.hpp>

namespace OpRes
{
    class ICostMatrixParser
    {
        public:

        virtual auto readSourceAndFillMatrix(CostMatrix& matrix, std::string& path) -> void = 0;

        protected:

        auto assertRowFits(const CostMatrix& matrix, const Row& row) -> void
        {
            if (not (matrix.getJobsCount() == row.size()))
            {
                throw std::invalid_argument("Row has different size than the matrix width");
            }
        }
    };
}