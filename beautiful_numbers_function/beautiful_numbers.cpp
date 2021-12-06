#include "beautiful_numbers.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
inline std::size_t calculate_buffer_size(uint64_t base, uint64_t digits) noexcept
{
    return (((base - 1) * digits) / 2) + 1;
}

inline bool is_odd(uint64_t base, uint64_t iteration) noexcept
{
    return ((base % 2) != 0) || ((iteration % 2) == 0);
}
} // namespace

uint64_t calculate_beautiful_numbers(uint64_t base, uint64_t digits)
{
    if (base < 2)
    {
        throw std::invalid_argument("calculate_beautiful_numbers: 'base' value MUST be at least 2.");
    }

    uint64_t max_digits {(std::numeric_limits<uint64_t>::max() - 1) / (base - 1)};
    if ((digits < 1) || (digits > max_digits))
    {
        throw std::invalid_argument("calculate_beautiful_numbers: 'digits' value MUST be in range [1,"
                                    + std::to_string(digits) + "].");
    }

    std::vector<uint64_t> counters(calculate_buffer_size(base, digits), 1);
    std::fill_n(counters.begin(), std::min<uint64_t>(counters.size(), base), 1);

    std::vector<uint64_t> buffer(base + 1, 0);
    for (uint64_t iteration = 1; iteration < digits; ++iteration)
    {
        std::fill(buffer.begin(), buffer.end(), 0);

        uint64_t fill_size {calculate_buffer_size(base, iteration + 1)};
        uint64_t accumulator {0};
        std::size_t buffer_index {0};
        std::size_t index {0};
        for (; index < fill_size; ++index)
        {
            auto& element {counters[index]};
            buffer[buffer_index % (base + 1)] = element;
            accumulator += element;
            accumulator -= buffer[++buffer_index % (base + 1)];
            element = accumulator;
        }

        if (index < counters.size())
        {
            auto dest {std::next(counters.begin(), index)};
            auto src {std::next(counters.rbegin(), counters.size() - index)};
            auto count {std::min(index, counters.size() - index)};

            if (is_odd(base, iteration + 1))
            {
                src = std::next(src);
                count = std::min(count, index - 1);
            }

            std::copy_n(src, count, dest);
        }
    }

    // Final accumulate
    {
        uint64_t result {0};
        std::size_t count {calculate_buffer_size(base, digits)};
        for (std::size_t i = 0; i < count; ++i)
        {
            uint64_t square {counters[i] * counters[i]};
            result += square;
            if ((i != (count - 1)) || (!is_odd(base, digits)))
            {
                result += square;
            }
        }
        return result;
    }
}

uint64_t calculate_beautiful_numbers(uint64_t base, uint64_t digits, uint64_t extra_digits)
{
    auto result {calculate_beautiful_numbers(base, digits)};

    while (extra_digits--)
    {
        result *= base;
    }

    return result;
}
