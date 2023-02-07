#pragma once

#include <string>
#include <stdexcept>
#include <optional>
#include <algorithm>

#include <JobMatrix.hpp>

namespace OpRes
{
    class IJobMatrixParser
    {
    public:

        virtual auto readSourceAndFillMatrix(JobMatrix& matrix, std::optional<std::string> path) const -> void = 0;
        virtual ~IJobMatrixParser() {};

        [[nodiscard]] static auto countSeparators(std::string& line, const char separator) noexcept
        {
            return std::count(line.begin(), line.end(), separator);
        }
    };
}