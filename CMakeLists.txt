cmake_minimum_required(VERSION 4.2)
project(RT1Week)

set(CMAKE_CXX_STANDARD 20)

add_executable(RT1Week src/main.cpp
        src/math/vec3.h
        src/core/color.h
        src/core/ray.h
        src/shape/hittable.h
        src/shape/sphere.h
        src/shape/hittable_list.h
        src/math/rtweek.h)
