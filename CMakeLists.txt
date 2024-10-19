cmake_minimum_required(VERSION 3.29)
project(MasterMind)

set(CMAKE_CXX_STANDARD 20)

add_executable(MasterMind main.cpp
        mastermind.cpp
        mastermind.h)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_compile_options(MasterMind PRIVATE ${OpenMP_CXX_FLAGS})
    target_link_libraries(MasterMind PRIVATE ${OpenMP_CXX_LIBRARIES} gomp)
endif()


