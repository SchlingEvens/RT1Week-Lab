//
// Created by Klingsor on 2026/6/1.
//

#ifndef RT1WEEK_HITTABLE_H
#define RT1WEEK_HITTABLE_H

#include "../math/vec3.h"
#include "../math/interval.h"
#include "../core/ray.h"

//单次碰撞的切片数据
class hit_record {
public:
    //碰撞交点在世界空间下的坐标
    point3 position;
    //碰撞交点和光线起点的距离
    double t;
    //法线,与光源来源相反
    vec3 normal;
    //光线来源方向
    bool front_face;

    //计算光线来源方向和法线
    void set_face_normal(const ray& r,const vec3& outware_normal) {
        //如果碰撞点向外法线和光线方向相反（夹角大于90度），则点积小于0，记为true
        front_face=dot(r.direction(),outware_normal)<0;
        //如果碰撞点向外法线和光线方向相同，则法线需要反转，以保证法线始终和光线来源相反
        normal=front_face?outware_normal:-outware_normal;
    }
};

//所有可击中对象的父类
class hittable {
public:
    //使用默认的析构函数
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval t, hit_record& rec) const = 0;
};

#endif //RT1WEEK_HITTABLE_H
