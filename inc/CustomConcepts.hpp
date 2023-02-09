#pragma once

#include <concepts>
#include <ranges>

template <typename A>
concept SortableUnsignedIntegralRange = requires(A a)
{
    {a} -> std::ranges::random_access_range;
    {typename A::value_type()} -> std::unsigned_integral;
};