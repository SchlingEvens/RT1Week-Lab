cmake_minimum_required(VERSION 4.2)
project(RT1Week)

set(CMAKE_CXX_STANDARD 20)

add_executable(RT1Week main.cpp
        utils/vec3.h
        utils/color.h
        utils/utils.h
        utils/ray.h)
