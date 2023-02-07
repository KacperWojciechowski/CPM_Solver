#pragma once

#include <memory>

#include <JobMatrix.hpp>

namespace OpRes 
{
    class JobMatrixLazyProcessor
    {
        auto setForProcessing(auto jobMatrix)
        {
            matrix = jobMatrix;
        }

        // use priority queue and command pattern for realizing operations

        // appendJob
        // removeJob
        // changeJobTransitionCost
        // disconnectJobs

        private:

        std::weak_ptr<JobMatrix> matrix;
    }
}