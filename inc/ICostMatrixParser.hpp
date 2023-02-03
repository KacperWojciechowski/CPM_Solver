#pragma once

#include <string>
#include <stdexcept>
#include <optional>
#include <algorithm>

#include <CostMatrix.hpp>

namespace OpRes
{
    class ICostMatrixParser
    {
        public:

        virtual auto readSourceAndFillMatrix(CostMatrix& matrix, std::optional<std::string> path) -> void = 0;
        virtual ~ICostMatrixParser() {};

        [[nodiscard]] static auto countSeparators(std::string& line, const char separator) noexcept -> std::size_t
        {
            return std::count(line.begin(), line.end(), separator);
        }
    };
}