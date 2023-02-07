#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>


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
            assertMatrixNotEmpty();
            return matrix.size();
        }

        [[nodiscard]] inline auto getJobTransitionCost(std::size_t prevJobID, std::size_t nextJobID) const
        {
            return matrix[prevJobID][nextJobID];
        }

        inline auto setJobTransitionCost(std::size_t sourceJobID, std::size_t targetJobID, int jobTransitionCost)
        {
            matrix[sourceJobID][targetJobID] = jobTransitionCost;
        }

        inline auto setJobTransitionRow(std::size_t currentJobID, Row&& row)
        {
            matrix[currentJobID] = row;
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

        inline auto assertRowFits(const Row& row)
        {
            if (not (getJobsCount() == row.size()))
            {
                throw std::invalid_argument("Row has different size than the matrix width");
            }
        }

        inline auto appendJob()
        {
            for(auto& row : matrix)
            {
                row.emplace_back(JobMatrix::NO_EDGE);
            }
            Row& row = matrix[0];
            matrix.emplace_back(row.size(), JobMatrix::NO_EDGE);
        }

        auto eraseJob(auto jobId) -> void
        {
            for (auto& row : matrix)
            {
                row.erase(row.begin(), std::next(row.begin(), jobId));
            }
            matrix.erase(matrix.begin(), std::next(matrix.begin(), jobId));
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

        Matrix matrix;
    };
}