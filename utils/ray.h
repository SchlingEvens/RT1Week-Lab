//
// Created by Klingsor on 2026/5/29.
//

#ifndef RT1WEEK_RAY_H
#define RT1WEEK_RAY_H

class ray {
public:
    //构造函数
    ray(){}
    ray(const vec3& origin, const vec3& direction):orig(origin), dir(direction){}

    //返回方向和光线的起点，const的目的是让它们为只读。
    //此方法类似于get
    const vec3& origin() const {return orig;}
    const vec3& direction() const {return dir;}

    //射线方程P=A+tb
    //const是为了让const实例也能调用该方法，而不是仅允许const实例调用该方法
    [[nodiscard]] point3 at(double t) const {
        return orig+t*dir;
    }

private:
    point3 orig;
    vec3 dir;
};

#endif //RT1WEEK_RAY_H
