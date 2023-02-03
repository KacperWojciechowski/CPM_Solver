#pragma once

#include <CostMatrix.hpp>
#include <ICostMatrixParser.hpp>
#include <Network.h>


namespace OpRes
{
    class NetBuilder
    {
    public:
        NetBuilder()
        : costMatrix(),
        network()
        {}

        inline auto setDataParser(const ICostMatrixParser* fileParser) -> void
        {
            parser = fileParser;
        }

        [[nodiscard]] auto getCostMatrix() -> CostMatrix&
        {
            return costMatrix;
        }

        [[nodiscard]] auto createNewNetwork() -> NetBuilder&
        {
            network = {};
        }

        [[nodiscard]] auto appendJob(Job&& job) -> NetBuilder&
        {
            costMatrix.appendJob(std::move(job));
        }

        [[nodiscard]] auto changeJobTransitionCost(std::size_t sourceJobId, std::size_t targetJobId, int cost) -> NetBuilder&;
        {
            costMatrix.changeJobTransitionCost(sourceJobId, targetJobId, cost);
        }

        [[nodiscard]] auto eraseJob(std::size_t jobId) -> NetBuilder&
        {
            costMatrix.eraseJob(jobId);
        }

        [[nodiscard]] inline auto removeTransition(std::size_t sourceJobId, std::size_t targetJobId)
        {
            costMatrix.changeTransitionCost(sourceJobId, targetJobId, OpRes::CostMatrix::NO_EDGE);
        }

        [[nodiscard]] auto setJobCount(const std::size_t jobCount) -> NetBuilder&
        {
            costMatrix.setJobCount(jobCount);
        }

        [[nodiscard]] auto sortIntoNetwork() -> NetBuilder&
        {
            network.sortIntoNetwork(costMatrix);
        }

        [[nodiscard]] auto sourceDataFile(const std::string& filePath) -> NetBuilder&;

        [[nodiscard]] auto build() -> Network
        {
            auto tempNetwork = std::move(network);
            createNewNetwork();
            return tempNetwork;
        }

    private:

        ICostMatrixParser* parser = nullptr;
        CostMatrix costMatrix;
        Network network;
    };
}