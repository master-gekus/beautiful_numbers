#include <algorithm>
#include <iomanip>
#include <iostream>

#include "beautiful_numbers.h"

template <typename ValueType>
std::ostream& operator<<(std::ostream& os, const std::vector<ValueType>& value)
{
    os << "{";
    auto start = value.begin();
    auto end = value.end();
    if (start != end)
    {
        os << (*start);
        for (start = std::next(start); start != end; ++start)
        {
            os << "," << (*start);
        }
    }
    os << "}";
    return os;
}

void output_calculation_for(std::size_t base, std::size_t digits)
{
    beautiful_numbers bn {base, digits};

    std::cout << "Calculation for {" << base << "; " << digits << "} (buffer size "
              << bn.counters().size() << "):" << std::endl;

    std::cout << " 1: " << bn.counters() << "; sum = " << bn.calculate_sum() << std::endl;
    for (std::size_t iteration = 1; iteration < digits; ++iteration)
    {
        bn.iterate();
        std::cout << std::setw(2) << bn.iteration() << ": " << bn.counters()
                  << "; sum = " << bn.calculate_sum() << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    try
    {
        output_calculation_for(2, 1);
        output_calculation_for(2, 8);
        output_calculation_for(3, 6);
        output_calculation_for(4, 6);
        output_calculation_for(5, 6);
        output_calculation_for(10, 4);
        output_calculation_for(13, 6);
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception." << std::endl;
        return 1;
    }
}
