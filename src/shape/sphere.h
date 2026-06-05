// Created by Klingsor on 2026/6/2.
//

#ifndef RT1WEEK_SPHERE_H
#define RT1WEEK_SPHERE_H

#include "hittable.h"
#include "../math/rtweek.h"
#include "../core/ray.h"

class sphere:public hittable {       //public:继承访问修饰符
public:
    sphere(const point3 &center,const double radius):center(center),radius(std::fmax(0,radius)){}

    //判断是否击中
    //rec是输出参数
    bool hit(const ray &r, interval t, hit_record &rec) const override {
        auto oc=center-r.origin();
        auto delta_a=dot(r.direction(),r.direction());
        auto h=dot(r.direction(),oc);
        auto delta_c=dot(oc,oc)-radius*radius;

        //判断交点数量
        auto discriminant = h*h - delta_a*delta_c;
        if (discriminant < 0) return false;
        auto sqrt_disc = std::sqrt(discriminant);

        //检查交点是否在range t_min,t_max 内
        auto root = (h - sqrt_disc) / delta_a;
        if (!t.surrounds(root)) {
            //检查较大根
            root = (h + sqrt_disc) / delta_a;
            if (!t.surrounds(root)) return false;
        }
        //这里直接把数据写进函数参数的rec
        rec.t=root;
        rec.position=r.at(root);
        rec.set_face_normal(r,(rec.position-center)/radius);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif //RT1WEEK_SPHERE_H
