#include <iostream>

#include "beautiful_numbers.h"

int main()
{
    try
    {
        // Total digits = 13
        // Used for check 6 + 6 = 12
        // Extra (unused) digits = 13 - (6 + 6) = 1
        std::cout << calculate_beautiful_numbers(13, 6, 1) << std::endl;
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
