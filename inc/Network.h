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

	class Network : public INetworkInstance
	{
	public:
		enum class CPMMode
		{
			MinimalTransitionCostSequence,
			MaximalTransitionCostSequence`
		}

		using Layer = std::vector<Job>;

		friend NetBuilder;

		[[nodiscard]] inline auto getJob(std::size_t jobId) const noexcept -> Job&;
		[[nodiscard]] auto criticalPathMethod() noexcept -> std::list<Path>;

		friend auto operator<< (std::ostream& out, const Network& net) -> std::ostream&;
	private:

		Network() {};

		auto sortIntoNetwork(const JobMatrix& jobMatrix, CPMMode mode) noexcept -> void;
		auto prepareWeightsAccordingToMode() noexcept -> void;

		std::list<Layer> layers;

	};
}
