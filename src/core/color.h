//
// Created by Klingsor on 2026/5/29.
//

#ifndef RT1WEEK_COLOR_H
#define RT1WEEK_COLOR_H

#include "../math/vec3.h"
#include "../math/interval.h"
#include <iostream>

//使用color作为vec3的别名
using color=vec3;

//将单个像素输出到输出流
void write_color(std::ostream& out, const color& pixel_color) {
    auto r=pixel_color.r;
    auto g=pixel_color.g;
    auto b=pixel_color.b;

    //转换为ppm格式支持的颜色参数[0,255]
    static const interval color_interval=interval(0.0,0.99999);
    int ir=int(255.999*color_interval.clamp(r));
    int ig=int(255.999*color_interval.clamp(g));
    int ib=int(255.999*color_interval.clamp(b));

    out<<ir<<' '<<ig<<' '<<ib<<'\n';
}

#endif //RT1WEEK_COLOR_H
