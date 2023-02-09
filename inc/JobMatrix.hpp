#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <concepts>

#include <CustomConcepts.hpp>

namespace OpRes {

    using Row = std::vector<int>;
    using Matrix = std::vector<Row>;

    // forward declaration
    class NetBuilder;

    class JobMatrix
    {
    public:

        static constexpr int NO_EDGE = -1;
        static constexpr int INVERTED_NO_EDGE = 1;

        friend class NetBuilder;

        inline auto setJobCount(std::size_t newJobsCount)
        {
            assertJobsCountHigherThanCurrent(newJobsCount);

            auto columnAndRowSize = matrix.size();
            auto jobsCountToAppend = newJobsCount - columnAndRowSize;

            appendJobsToExistingRows(newJobsCount, jobsCountToAppend);
            appendRowsToMatchNewJobsCount(newJobsCount, jobsCountToAppend);

            assertMatrixIsSquare();
        }

        [[nodiscard]] inline auto getJobsCount() const
        {
            return matrix.size();
        }

        [[nodiscard]] inline auto getJobTransitionCost(std::size_t sourceJobId, std::size_t targetJobId) const
        {
            assertIndexWithinRange(sourceJobId);
            assertIndexWithinRange(targetJobId);
            return matrix[sourceJobId][targetJobId];
        }

        inline auto setJobTransitionCost(std::size_t sourceJobId, std::size_t targetJobId, int jobTransitionCost)
        {
            assertIndexWithinRange(sourceJobId);
            assertIndexWithinRange(targetJobId);
            matrix[sourceJobId][targetJobId] = jobTransitionCost;
        }

        inline auto setJobTransitionRow(std::size_t sourceJobId, Row&& row)
        {
            assertIndexWithinRange(sourceJobId);
            assertRowFits(row);
            matrix[sourceJobId] = row;
        }

        friend auto operator<< (std::ostream& out, const JobMatrix& jobMatrix)
        {
            out << "[\n";
            for (const auto& row : jobMatrix.matrix)
            {
                for (const auto& job : row)
                {
                    out << std::right << std::setw(3) << job << " ";
                }
                out << "\n";
            }
            out << "]\n";
        }

        inline auto appendJob(std::size_t count)
        {
            setJobCount(getJobsCount() + count);
        }

        auto eraseJob(SortableUnsignedIntegralRange auto rangeOfJobsToErase)
        {
            std::ranges::sort(rangeOfJobsToErase);

            for (auto rIter = rangeOfJobsToErase.rbegin(); rIter != rangeOfJobsToErase.rend(); rIter++)
            {
                matrix.erase(std::next(matrix.begin(), *rIter));
            }
            for (auto rIter = rangeOfJobsToErase.rbegin(); rIter != rangeOfJobsToErase.rend(); rIter++)
            {
                std::for_each(matrix.begin(), matrix.end(), [rIter](auto& row)
                {
                    row.erase(std::next(row.begin(), *rIter));
                });
            }
        }

        auto eraseJob(std::size_t jobToErase)
        {
            matrix.erase(std::next(matrix.begin(), jobToErase));
            std::for_each(matrix.begin(), matrix.end(), [&jobToErase](auto& row)
            {
                row.erase(std::next(row.begin(), jobToErase));
            });
        }

    private:

        JobMatrix() {};

        inline auto appendRowsToMatchNewJobsCount(std::size_t newJobsCount, std::size_t jobsCountToAppend) -> void
        {
            matrix.reserve(newJobsCount);
            for(auto i = 0; i < jobsCountToAppend; i++)
            {
                matrix.emplace_back(newJobsCount, OpRes::JobMatrix::NO_EDGE);
            }
        }

        inline auto appendJobsToExistingRows(std::size_t newJobsCount, std::size_t jobsCountToAppend) -> void
        {
            for(auto& row : matrix)
            {
                row.reserve(newJobsCount);
                row.insert(row.end(), jobsCountToAppend, OpRes::JobMatrix::NO_EDGE);
            }
        }

        [[nodiscard]] inline auto isRowTheSameSizeAsColumn(const Row& row) const -> bool
        {
            return row.size() != matrix.size();
        }

        inline auto assertMatrixIsSquare() const -> void
        {
            for(const auto& row : matrix)
            {
                if (not isRowTheSameSizeAsColumn(row))
                {
                    throw std::runtime_error("JobMatrix is not square");
                }
            }
        }

        inline auto assertMatrixNotEmpty() const -> void
        {
            if (matrix.size() == 0)
            {
                throw std::runtime_error("JobMatrix contains 0 jobs");
            }
        }

        inline auto assertJobsCountHigherThanCurrent(std::size_t jobsCount) const -> void
        {
            if (matrix.size() < jobsCount)
            {
                throw std::invalid_argument("Attempting to set jobs count smaller than current");
            }
        }

        inline auto assertIndexWithinRange(const auto index) const -> void
        {
            if (not (index < matrix.size()))
            {
                throw std::invalid_argument("Index out of bounds");
            }
        }

        inline auto assertRowFits(const Row& row) -> void
        {
            if (not (getJobsCount() == row.size()))
            {
                throw std::invalid_argument("Row has different size than the matrix width");
            }
        }

        Matrix matrix;
    };
}