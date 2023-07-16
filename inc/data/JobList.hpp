#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <iostream>

namespace cpm::serializers 
{
    class XmlSerializer;
} // namespace cpm::serializers

namespace cpm::data 
{
class JobList 
{
public:

    struct JobInfo 
    {
        std::size_t id;
        std::string name;
    };

    struct JobConnection 
    {
        std::weak_ptr<JobInfo> jobInfo;
        int cost;
    };
    
    using JobIterator = std::vector<std::shared_ptr<JobInfo>>::iterator;
    using JobConnectionsList = std::vector<JobConnection>;

    
    inline auto setNodesCount(std::size_t count) -> void
    {
        try 
        {
            list.resize(count);
        } 
        catch (std::exception e) 
        {
            std::cerr << "[JobList] " << e.what() << std::endl;
        }
    }

    [[nodiscard]] inline auto getJobsCount() const noexcept -> std::size_t
    {
        return jobInfo.size();
    }

    inline auto connectNeighbourTo(std::size_t sourceJobId, std::size_t jobIdToAppend, int cost) -> void
    {
        auto jobToAppendItr = getJobItr(jobIdToAppend);
        if (jobToAppendItr != jobInfo.end())
        {
            try 
            {
                getConnectionReference(sourceJobId).emplace_back(*getJobItr(jobIdToAppend), cost);
            } 
            catch (std::exception e) 
            {
                std::cerr << "[JobList] " << e.what() << std::endl;
            }
        }
    }

    inline auto appendJob(JobInfo jobToAppend) -> void
    {
        jobInfo.emplace_back(std::make_shared<JobInfo>(jobToAppend));
    }

    inline auto removeJob(std::size_t jobId) -> void
    {
        auto jobItr = getJobItr(jobId);
        if (jobItr != jobInfo.end())
        {
            jobInfo.erase(jobItr);
        }
    }

    inline auto editJob(std::size_t jobId, JobInfo editedJob) -> void
    {
        auto jobItr = getJobItr(jobId);
        if (jobItr != jobInfo.end())
        {
            **jobItr = std::move(editedJob);
        }
    }

    friend auto operator<< (std::ostream& out, const JobList& jobList) -> std::ostream&;

private:

    [[nodiscard]] inline auto getJobItr(std::size_t jobId) -> JobIterator
    {
        auto jobItr = jobToIndexMap.find(jobId);
        if (jobItr == jobToIndexMap.end()) 
        {
            throw std::invalid_argument("No job of given id exists");
        }
        return std::next(jobInfo.begin(), jobItr->second);
    }

    [[nodiscard]] inline auto getConnectionReference(std::size_t jobId) -> JobConnectionsList&
    {
        return list[jobToIndexMap.at(jobId)];
    }

    std::vector<std::shared_ptr<JobInfo>> jobInfo;
    std::vector<JobConnectionsList> list; 

    using JobIndex = std::size_t;
    using VectorIndex = std::size_t;

    std::unordered_map<JobIndex, VectorIndex> jobToIndexMap; 
};
} // namespace cpm::data