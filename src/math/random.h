//
// Created by Klingsor on 2026/6/7.
//

#ifndef RT1WEEK_RANDOM_H
#define RT1WEEK_RANDOM_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


inline double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

#endif //RT1WEEK_RANDOM_H
