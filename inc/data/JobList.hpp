#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <memory>

namespace cpm::serializers 
{
    class XmlSerializer;
} // namespace cpm::serializers

namespace cpm::data {
class JobList {
    public:

    friend cpm::serializers::XmlSerializer;

    using JobIterator = std::unordered_map<std::size_t, std::size_t>::iterator;

    struct JobInfo {
        std::size_t id;
        std::string name;
    };

    struct JobConnection {
        std::weak_ptr<JobInfo> jobInfo;
        int cost;
    };

    
    inline auto setNodesCount(std::size_t count) -> void
    {
        try {
            list.resize(count);
        } catch (std::length_error e) {
            std::cerr << "[JobList][std::vector] Unable to resize, desired size exceeds list.max_size()" << std::endl;
        } catch (std::exception e) {
            std::cerr << "[JobList] " << e.what() << std::endl;
        }
    }

    [[no_discard]] inline auto getJobsCount() const noexcept -> std::size_t
    {
        return jobInfo.size();
    }

    inline auto connectNeighbourTo(std::size_t sourceJobId, std::size_t jobIdToAppend, int cost) -> void
    {
        auto targetJobItr = validateJob(sourceJobId);
        auto neighbourJobItr = validateJob(jobIdToAppend);

        getJobReferenceFromList(targetJobItr).emplace_back(getJobInfoSharedPtr(neighbourJobItr), cost);
    }

    inline auto appendJob(JobInfo jobToAppend)
    {
        jobInfo.emplace_back(std::make_shared<JobInfo>(jobToAppend));
    }

    inline auto removeJob(std::size_t jobId)
    {
        auto jobItr = validateJob(jobId);
        jobInfo.erase(std::next(jobInfo.begin(), jobItr->second));
    }

    private:

    [[no_discard]] inline auto validateJob(std::size_t jobId) -> JobIterator
    {
        auto jobItr = jobToIndexMap.find(jobId);
        if (jobItr == jobToIndexMap.end()) 
        {
            throw std::invalid_argument("No job of given id exists");
        }
        return jobItr;
    }

    [[no_discard]] inline auto getJobReferenceFromList(JobIterator jobItr) -> std::vector<JobConnection>&
    {
        return list[jobItr->second];
    }

    [[no_discard]] inline auto getJobInfoSharedPtr(JobIterator jobItr) -> std::shared_ptr<JobInfo>
    {
        return jobInfo[jobItr->second];
    }

    std::vector<std::shared_ptr<JobInfo>> jobInfo;
    std::vector<std::vector<JobConnection>> list; 
    std::unordered_map<std::size_t, std::size_t> jobToIndexMap; 
};
} // namespace cpm::data