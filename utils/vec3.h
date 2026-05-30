//
// Created by Klingsor on 2026/5/29.
//

//目的是防止同一个头文件被多次编译，效果类似#pram once
#ifndef RT1WEEK_VEC3_H
#define RT1WEEK_VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
public:
    union {
        float e[3];
        struct {float x,y,z;};
        struct {float r,g,b;};
    };

    //构造方法，无参时默认初始化为0，带三个参数时初始化为对应参数
    vec3():e{0,0,0}{}
    vec3(float e0,float e1,float e2):e{e0,e1,e2}{}

    //运算符重载
    //如果是一个const对象调用v3[i]，则自动调用第一个方法，只能读值不能修改
    //如果是一个普通对象，则自动调用第二个，可读可改
    float operator[](int i) const { return e[i];}
    float& operator[](int i) {return e[i];}

    vec3 operator-() const {return vec3(-e[0],-e[1],-e[2]);}
    vec3 operator+=(const vec3& v) {
        e[0]+=v.e[0];
        e[1]+=v.e[1];
        e[2]+=v.e[2];
        return *this;
    }

    //线性乘法
    vec3& operator*=(float v) {
        e[0]*=v;
        e[1]*=v;
        e[2]*=v;
        return *this;
    }
    vec3& operator/=(float v) {
        return *this *= 1/v;
    }

    //模场
    [[nodiscard]]float length_squared() const {
        return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
    }

    //模长
    [[nodiscard]]float length() const {
        return std::sqrt(length_squared());
    }
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
inline vec3 operator*(const vec3& u,float v) {
    return vec3(u[0]*v,u[1]*v,u[2]*v);
}
inline vec3 operator*(float t,const vec3& v) {
    return v*t;
}
inline vec3 operator/(const vec3& u,float v) {
    return u*(1/v);
}

//点乘
inline float dot(const vec3& u,const vec3& v) {
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

#endif //RT1WEEK_VEC3_H
