#pragma once
#include <string>
#include <iostream>

namespace solver 
{
class NetworkBuilder 
{
public:

    NetworkBuilder& getFromXml(std::string xmlFilePath);

    void printJobList();
};
} // namespace solver