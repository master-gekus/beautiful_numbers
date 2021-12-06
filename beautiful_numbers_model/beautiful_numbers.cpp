#include "beautiful_numbers.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>

beautiful_numbers::beautiful_numbers(std::size_t base, std::size_t digits)
    : base_ {base}
    , digits_ {digits}
    , counters_(calculate_capacity(base, digits), 0)
{
    std::fill_n(counters_.begin(), std::min(counters_.size(), base_), 1);
}

std::size_t beautiful_numbers::calculate_capacity(std::size_t base, std::size_t digits)
{
    if (base < 2)
    {
        throw std::invalid_argument("beautiful_numbers: 'base' value MUST be at least 2.");
    }

    std::size_t max_digits {(std::numeric_limits<std::size_t>::max() - 1) / (base - 1)};
    if ((digits < 1) || (digits > max_digits))
    {
        throw std::invalid_argument("beautiful_numbers: 'digits' value MUST be in range [1,"
                                    + std::to_string(digits) + "].");
    }
    return ((base - 1) * digits) + 1;
}

void beautiful_numbers::iterate()
{
    std::vector<std::size_t> buffer(base_ + 1, 0);
    std::size_t accumulator {0};
    std::size_t buffer_index {0};
    for (auto& element : counters_)
    {
        buffer[buffer_index % (base_ + 1)] = element;
        accumulator += element;
        accumulator -= buffer[++buffer_index % (base_ + 1)];
        element = accumulator;
    }
}

std::size_t beautiful_numbers::calculate_sum() const
{
    return std::accumulate(counters_.begin(), counters_.end(), static_cast<std::size_t>(0),
                           [](auto a, auto b) {
                               return a + (b * b);
                           });
}
