#include "beautiful_numbers.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>

beautiful_numbers::beautiful_numbers(std::size_t base, std::size_t digits)
    : base_ {base}
    , digits_ {digits}
    , iteration_ {1}
    , counters_(check_and_calculate_capacity(digits), 0)
{
    std::fill_n(counters_.begin(), std::min(counters_.size(), base_), 1);
}

std::size_t beautiful_numbers::check_and_calculate_capacity(std::size_t digits) const
{
    if (base_ < 2)
    {
        throw std::invalid_argument("beautiful_numbers: 'base' value MUST be at least 2.");
    }

    std::size_t max_digits {(std::numeric_limits<std::size_t>::max() - 1) / (base_ - 1)};
    if ((digits < 1) || ((digits / 2) > max_digits))
    {
        throw std::invalid_argument("beautiful_numbers: 'digits' value MUST be in range [1,"
                                    + std::to_string(max_digits) + "].");
    }

    // digits / 2 = (std::numeric_limits<std::size_t>::max() - 1) / (base_ - 1)

    return calculate_fill_size();
}

inline std::size_t beautiful_numbers::calculate_fill_size(std::size_t digits) const noexcept
{
    return (((base_ - 1) * digits) / 2) + 1;
}

inline bool beautiful_numbers::is_odd() const noexcept
{
    return ((base_ % 2) != 0) || ((iteration_ % 2) == 0);
}

void beautiful_numbers::iterate()
{
    if ((++iteration_) > digits_)
    {
        return;
    }
    std::vector<std::size_t> buffer(base_ + 1, 0);
    std::size_t fill_size {calculate_fill_size(iteration_)};
    std::size_t accumulator {0};
    std::size_t buffer_index {0};
    std::size_t index {0};
    for (; index < fill_size; ++index)
    {
        auto& element {counters_[index]};
        buffer[buffer_index % (base_ + 1)] = element;
        accumulator += element;
        accumulator -= buffer[++buffer_index % (base_ + 1)];
        element = accumulator;
    }

    if (index < counters_.size())
    {
        auto dest {std::next(counters_.begin(), index)};
        auto src {std::next(counters_.rbegin(), counters_.size() - index)};
        auto count {std::min(index, counters_.size() - index)};

        if (is_odd())
        {
            src = std::next(src);
            count = std::min(count, index - 1);
        }

        std::copy_n(src, count, dest);
    }
}

std::size_t beautiful_numbers::calculate_sum() const
{
    std::size_t result {0};
    std::size_t count {calculate_fill_size(iteration_)};
    for (std::size_t i = 0; i < count; ++i)
    {
        std::size_t square {counters_[i] * counters_[i]};
        result += square;
        if ((i != (count - 1)) || (!is_odd()))
        {
            result += square;
        }
    }
    return result;
}
