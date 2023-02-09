#pragma once

#include <IJobMatrixParser.hpp>
#include <JobMatrix.hpp>
#include <Network.h>


namespace OpRes
{
    class NetBuilder
    {
    public:
        NetBuilder()
        : jobMatrix(),
        network()
        {}

        inline auto setDataParser(const IJobMatrixParser* fileParser) -> void
        {
            parser = fileParser;
        }

        [[nodiscard]] auto getJobMatrix() -> JobMatrix&
        {
            return jobMatrix;
        }

        [[nodiscard]] auto createNewNetwork() -> NetBuilder&
        {
            network = {};
            return *this;
        }

        [[nodiscard]] auto appendJob(std::size_t count) -> NetBuilder&
        {
            jobMatrix.appendJob(count);
            return *this;
        }

        [[nodiscard]] auto setJobTransitionCost(std::size_t sourceJobId, std::size_t targetJobId, int cost) -> NetBuilder&
        {
            jobMatrix.setJobTransitionCost(sourceJobId, targetJobId, cost);
            return *this;
        }

        [[nodiscard]] auto eraseJob(std::size_t jobId) -> NetBuilder&
        {
            jobMatrix.eraseJob(jobId);
            return *this;
        }

        [[nodiscard]] inline auto removeTransition(std::size_t sourceJobId, std::size_t targetJobId) -> NetBuilder&
        {
            jobMatrix.setJobTransitionCost(sourceJobId, targetJobId, OpRes::JobMatrix::NO_EDGE);
            return *this;
        }

        [[nodiscard]] auto setJobCount(const std::size_t jobCount) -> NetBuilder&
        {
            jobMatrix.setJobCount(jobCount);
            return *this;
        }

        [[nodiscard]] auto sortIntoNetwork() -> NetBuilder&
        {
            network.sortIntoNetwork(jobMatrix);
            return *this;
        }

        [[nodiscard]] auto sourceDataFile(const std::string& filePath) -> NetBuilder&;

        [[nodiscard]] auto build() -> Network
        {
            return network;
        }

    private:

        const IJobMatrixParser* parser = nullptr;
        JobMatrix jobMatrix;
        Network network;
    };
}