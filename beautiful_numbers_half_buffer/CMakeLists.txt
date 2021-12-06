cmake_minimum_required(VERSION 3.17)

project(beautiful_numbers_half_buffer LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
    beautiful_numbers.h
    beautiful_numbers.cpp
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    )
