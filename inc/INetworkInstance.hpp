#pragma once

namespace OpRes
{
    class INetworkInstance
    {
    public:
        virtual auto getJobCount() const noexcept -> std::size_t
        {
            return jobCount;
        }

        virtual ~INetworkInstance() {};

    protected:

        virtual auto setJobCount(std::size_t targetJobCount) noexcept -> void
        {
            jobCount = targetJobCount;
        }

    private:
        std::size_t jobCount;
    };
}