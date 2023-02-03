#include <Network.h>

#include <stdexcept>

namespace
{
	auto assertJobExists(const OpRes::Network& network, std::size_t jobId) -> void
	{
		if (network.getJobCount() < jobId)
		{
			throw std::invalid_argument("Job with given ID is not present in the network");
		}
	}
}

namespace OpRes {

	auto Network::getJob(std::size_t jobId) -> Job&
	{
		assertJobExists(*this, jobId);

		auto jobIdFilter = [jobId](auto& job) -> bool
		{
			return job.id == jobId;
		};

		for(auto& layer : layers)
		{
			auto foundJob = std::ranges::find_if(layer.begin(), layer.end(), jobIdFilter);
			if(foundJob != layer.end())
			{
				return *foundJob;
			}
		}
	}
}