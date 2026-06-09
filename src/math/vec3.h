//
// Created by Klingsor on 2026/5/29.
//

//目的是防止同一个头文件被多次编译，效果类似#pram once
#ifndef RT1WEEK_VEC3_H
#define RT1WEEK_VEC3_H

#include <cmath>
#include <iostream>

#include "random.h"

class vec3 {
public:
    union {
        double e[3];
        struct {double x,y,z;};
        struct {double r,g,b;};
    };

    //构造方法，无参时默认初始化为0，带三个参数时初始化为对应参数
    vec3():e{0,0,0}{}
    vec3(double e0,double e1,double e2):e{e0,e1,e2}{}

    //运算符重载
    //如果是一个const对象调用v3[i]，则自动调用第一个方法，只能读值不能修改
    //如果是一个普通对象，则自动调用第二个，可读可改
    double operator[](int i) const { return e[i];}
    double& operator[](int i) {return e[i];}

    vec3 operator-() const {return vec3(-e[0],-e[1],-e[2]);}
    vec3 operator+=(const vec3& v) {
        e[0]+=v.e[0];
        e[1]+=v.e[1];
        e[2]+=v.e[2];
        return *this;
    }

    //线性乘法
    vec3& operator*=(double v) {
        e[0]*=v;
        e[1]*=v;
        e[2]*=v;
        return *this;
    }
    vec3& operator/=(double v) {
        return *this *= 1/v;
    }

    //模长的平方
    [[nodiscard]]double length_squared() const {
        return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
    }

    //模长
    [[nodiscard]]double length() const {
        return std::sqrt(length_squared());
    }

    //生成随机单位向量
    static vec3 random(){return vec3(random_double(),random_double(),random_double());}
    //生成每个分量在[min,max]范围内的随机单位向量
    static vec3 random(double min,double max){return vec3(random_double(min,max),random_double(min,max),random_double(min,max));}

};

//使用point3作为vec3的别名
using point3=vec3;

//重载输出流
inline std::ostream& operator<<(std::ostream& out,const vec3& v) {
    return out<<v.e[0]<<" "<<v.e[1]<<" "<<v.e[2];
}

//二元运算符重载
//向量加法 为了不必要的拷贝和避免修改操作数使用const
inline vec3 operator+(const vec3& u,const vec3& v) {
    return vec3(u[0]+v[0],u[1]+v[1],u[2]+v[2]);
}

//向量减法
inline vec3 operator-(const vec3& u,const vec3& v) {
    return vec3(u[0]-v[0],u[1]-v[1],u[2]-v[2]);
}

//逐分量乘法
inline vec3 operator*(const vec3& u,const vec3& v) {
    return vec3(u[0]*v[0],u[1]*v[1],u[2]*v[2]);
}

//线性乘法
inline vec3 operator*(const vec3& u,double v) {
    return vec3(u[0]*v,u[1]*v,u[2]*v);
}
inline vec3 operator*(double t,const vec3& v) {
    return v*t;
}
inline vec3 operator/(const vec3& u,double v) {
    return u*(1/v);
}

//点乘
inline double dot(const vec3& u,const vec3& v) {
    return u.e[0]*v.e[0]+u.e[1]*v.e[1]+u.e[2]*v.e[2];
}

//叉乘
inline vec3 cross(const vec3& u,const vec3& v) {
    return vec3(
        u.e[1]*v.e[2]-v.e[2]*u.e[1],
        u.e[2]*v.e[0]-v.e[0]*u.e[2],
        u.e[0]*v.e[1]-v.e[1]*u.e[0]
        );
}

//单位向量
inline vec3 unit_vector(const vec3& v) {
    return v/v.length();
}

//生成随机单位向量
inline vec3 random_unit_vector() {
    while (true) {
        auto p=vec3::random(-1,1);
        auto lensq=p.length_squared();
        if (lensq>1e-160&&lensq<1.0)return unit_vector(p);
    }
}

//生成随机和传入法线向量方向相同的单位向量
inline vec3 random_on_hemishpere(const vec3& normal) {
    auto on_unit_vec=random_unit_vector();
    if (dot(on_unit_vec,normal)>0) return on_unit_vec;    //同向/位于相同半球
    else return -on_unit_vec;
}

#endif //RT1WEEK_VEC3_H
