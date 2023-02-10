#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace OpRes
{
    struct Job
	{
		std::string jobDesc;
		std::size_t id;
		int earliestEntryBoundary;
		int latestLeaveBoundary;
        std::size_t decidingPredecessorId;
        int decidingPredecessorTransitionCost;
	};

    class Path
    {
        friend auto operator<<(std::ostream& out, const Path& p)
        {
            out << "Path as Jobs IDs: [";
            for (auto index = 0; const auto& job : p.path)
            {
                out << job.id;
                if (index++ < p.path.size())
                {
                    out << ", ";
                }
            }
            out << "]";
            return out;
        }

        inline auto getPathAsVectorOfJobs()
        {
            return path;
        }

        private:

        std::vector<Job> path;
    }
}