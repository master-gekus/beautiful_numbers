#pragma once
#ifndef BEAUTIFUL_NUMBERS_H
#define BEAUTIFUL_NUMBERS_H

#include <vector>

class beautiful_numbers
{
public:
    beautiful_numbers(std::size_t base, std::size_t digits);

    void iterate();
    std::size_t calculate_sum() const;

public:
    const auto& counters() const noexcept
    {
        return counters_;
    }

    auto iteration() const noexcept
    {
        return iteration_;
    }

private:
    std::size_t check_and_calculate_capacity(std::size_t digits) const;
    std::size_t calculate_fill_size(std::size_t digits) const noexcept;
    std::size_t calculate_fill_size() const noexcept
    {
        return calculate_fill_size(digits_);
    }
    bool is_odd() const noexcept;

private:
    const std::size_t base_;
    const std::size_t digits_;
    std::size_t iteration_;
    std::vector<std::size_t> counters_;
};

#endif // BEAUTIFUL_NUMBERS_H
