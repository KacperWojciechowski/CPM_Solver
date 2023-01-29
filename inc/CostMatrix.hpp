#pragma once

#include <vector>
#include <stdexcept>
#include <ranges>


namespace OpRes {
    constexpr int NO_EDGE = -1;
    constexpr int INVERTED_NO_EDGE = 1;

    using Row = std::vector<int>;
    using Matrix = std::vector<Row>;

    // forward declaration
    class NetBuilder;

    class CostMatrix
    {
    public:
        friend class NetBuilder;
        friend class ICostMatrixParser;

        inline auto setJobCount(std::size_t jobsCount) -> void
        {
            assertJobsCountHigherThanCurrent(jobsCount);
            matrix.reserve(jobsCount);
            for(auto& row : matrix)
            {
                row.reserve(jobsCount);
            }
        }

        inline auto appendJob() -> void
        {
            for (auto& row : matrix)
            {
                row.emplace_back(NO_EDGE);
            }
            Row row(matrix[0].size(), NO_EDGE);
            matrix.emplace_back(std::move(row));
        }

        inline auto removeJob(std::size_t jobID) -> void
        {
            for (auto& row : matrix)
            {
                row.erase(std::next(row.begin(), jobID));
            }
            matrix.erase(std::next(matrix.begin(), jobID));
        }

        [[nodiscard]] inline auto getJobsCount() const -> std::size_t
        {
            assertMatrixNotEmpty();
            return matrix[0].size();
        }

        [[nodiscard]] inline auto getTransitionCost(std::size_t prevJobID, std::size_t nextJobID) const -> int
        {
            return matrix[prevJobID][nextJobID];
        }

        inline auto setJobTransitionCost(std::size_t sourceJobID, std::size_t targetJobID, int jobTransitionCost)
        {
            matrix[sourceJobID][targetJobID] = jobTransitionCost;
        }

    private:

        CostMatrix();

        auto assertMatrixNotEmpty() const -> void
        {
            if (matrix.size() == 0)
            {
                throw std::runtime_error("CostMatrix contains 0 jobs");
            }
        }

        auto assertJobsCountHigherThanCurrent(std::size_t jobsCount) const -> void
        {
            if (matrix.size() < jobsCount)
            {
                throw std::invalid_argument("Attempting to set jobs count smaller than current");
            }
        }

        Matrix matrix;
    };
}