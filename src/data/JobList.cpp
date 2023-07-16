#include <data/JobList.hpp>

namespace cpm::data
{
    auto operator<< (std::ostream& out, const JobList& jobList) -> std::ostream&
    {
        out << "[JobList]\n";
        out << "Jobs:\n";
        for (auto itr = jobList.jobToIndexMap.begin(); itr != jobList.jobToIndexMap.end(); itr++)
        {
            auto jobInfo = jobList.jobInfo[itr->second];
            out << "{Id: " << jobInfo->id << ", name: " << jobInfo->name << "}\n";
        }
        out << "Connections:\n";
        for (auto itr = jobList.jobToIndexMap.begin(); itr != jobList.jobToIndexMap.end(); itr++)
        {
            auto jobConnections = jobList.list[itr->second];
            for (auto connItr = jobConnections.begin(); connItr != jobConnections.end(); connItr++)
            {
                auto jobInfoPtr = connItr->jobInfo.lock();
                if (jobInfoPtr)
                out << "{Src Id: " << itr->first << " Target Id: " << jobInfoPtr->id << "}\n"; 
            }
        }
    }
} // namespace cpm::data