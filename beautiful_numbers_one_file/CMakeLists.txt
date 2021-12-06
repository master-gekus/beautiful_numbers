cmake_minimum_required(VERSION 3.17)

project(beautiful_numbers_one_file LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    beautiful_numbers.cpp
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    )
