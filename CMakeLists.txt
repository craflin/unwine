
cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0048 NEW)

project(unwine VERSION 0.1.0)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_subdirectory(src)
