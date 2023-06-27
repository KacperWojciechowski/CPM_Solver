#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

namespace data {
class JobList {
    public:

    struct JobConnection {
        std::size_t targetId;
        std::string name;
        int cost;
    };

    void setNodesCount(std::size_t count)
    {
        try {
            list.resize(count);
        } catch (std::length_error e) {
            std::cerr << "[JobList][std::vector] Unable to resize, desired size exceeds list.max_size()" << std::endl;
        } catch (std::exception e) {
            std::cerr << "[JobList] " << e.what() << std::endl;
        }
    }

    private:
    std::vector<std::vector<JobConnection>> list; 
};
} // namespace data