//
// Created by Klingsor on 2026/6/4.
//

#ifndef RT1WEEK_INTERVAL_H
#define RT1WEEK_INTERVAL_H

#include "rtweek.h"

class interval {
public:
    double min;
    double max;

    //不带参数时构造一个空集
    interval():min(+infinity),max(-infinity){}
    interval(double min, double max):min(min),max(max){}

    //区间长度
    double size()const{return max-min;}
    //判断区间是否包含某个值（闭区间）
    bool contains(double x)const{return min<=x && x<=max;}
    //判断区间是否包含某个值（开区间）
    bool surrounds(double x)const{return min<x && x<max;}
    //钳制区间
    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty,universe;
};

const interval interval::empty=interval(+infinity,-infinity);
const interval interval::universe=interval(-infinity,+infinity);

#endif //RT1WEEK_INTERVAL_H
