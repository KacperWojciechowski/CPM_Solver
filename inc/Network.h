#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <list>
#include <vector>

#include <INetworkInstance.hpp>

namespace OpRes
{
	class NetBuilder;
	class JobMatrix;

	struct Job
	{
		std::string jobDesc;
		std::size_t id;
		int earliestEntryBoundary;
		int latestLeaveBoundary;
	};

	class Network : public INetworkInstance
	{
	public:
		using Layer = std::vector<Job>;

		friend NetBuilder;

		[[nodiscard]] inline auto getJob(std::size_t jobId) -> Job&;

	private:

		Network() {};

		auto sortIntoNetwork(const JobMatrix& jobMatrix) noexcept -> void;

		std::list<Layer> layers;

	};
}
