#include <data/JobList.hpp>

namespace 
{
    using cpm::data::JobList;

    auto printJobInfo(std::ostream& out, JobList::JobInfo& jobInfo) -> void;
    {
        out << "{Id: " << jobInfo->id << ", name: " << jobInfo->name << "}\n";
    }

    auto printConnections(std::ostream& out, std::size_t sourceJobId, JobList::JobConnectionsList& jobConnections)
    {
        for (auto connItr = jobConnections.begin(); connItr != jobConnections.end(); connItr++)
        {
            auto jobInfoPtr = connItr->jobInfo.lock();
            if (jobInfoPtr)
            out << "{Src Id: " << sourceJobId << " Target Id: " << jobInfoPtr->id << "}\n"; 
        }
    }
}

namespace cpm::data
{
    auto operator<< (std::ostream& out, const JobList& jobList) -> std::ostream&
    {
        out << "[JobList]\n";
        out << "Jobs:\n";
        for (auto itr = jobList.jobToIndexMap.begin(); itr != jobList.jobToIndexMap.end(); itr++)
        {
            printJobInfo(out, *(jobList.jobInfo[itr->second]));
        }
        out << "Connections:\n";
        for (auto itr = jobList.jobToIndexMap.begin(); itr != jobList.jobToIndexMap.end(); itr++)
        {
            printConnections(out, itr->first, jobList.list[itr->second]);
        }
        return out;
    }
} // namespace cpm::data