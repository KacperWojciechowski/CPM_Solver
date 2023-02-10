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

	friend auto operator<< (std::ostream& out, const Network& net) -> std::ostream&
	{
		out << "{\n";
		for (auto index = 0; const auto& layer : net.layers)
		{
			out << "\tLayer " << index << "\n\t\t[";
			for (auto index2 = 0; const auto& job : layer)
			{
				out << job.id;
				if (++index2 < layer.size())
				{
					out << ", ";
				}
			}
			out << "]\n";
			if (++index < net.layers.size())
			{
				out << "\n";
			}
		}
		out << "}\n";
		return out;
	}
}