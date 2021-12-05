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

private:
    static std::size_t calculate_capacity(std::size_t base, std::size_t digits);

private:
    const std::size_t base_;
    const std::size_t digits_;
    std::vector<std::size_t> counters_;
};

#endif // BEAUTIFUL_NUMBERS_H
