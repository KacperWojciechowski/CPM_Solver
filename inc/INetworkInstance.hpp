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
    };
}