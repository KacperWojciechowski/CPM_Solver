#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <list>
#include <vector>

namespace OpRes
{
	class Network
	{
		public:

		struct Job
		{
			std::string jobDesc;
			std::size_t id;
			int earliestEntryBoundary;
			int latestLeaveBoundary;
		};

		using Layer = std::vector<Job>;

		[[nodiscard]] inline auto getJobCount() const noexcept -> std::size_t
		{
			return jobCount;
		}

		[[nodiscard]] inline auto getJob(std::size_t jobId) -> Job&;

		private:

		Network() {};

		std::size_t jobCount;
		std::list<Layer> layers;

	};
}
