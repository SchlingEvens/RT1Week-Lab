#include <iostream>
#include <fstream>
#include "math/rtweek.h"
#include "core/camera.h"
#include "shape/hittable_list.h"
#include "shape/sphere.h"
#include "shape/hittable.h"


color ray_color(const ray& r,const hittable& world) {
    //检查当前射线是否和实体对象相交
    hit_record temp_rec;
    if (world.hit(r,interval(0,infinity),temp_rec)) {
        //返回交点的法线映射的颜色
        return 0.5*(temp_rec.normal+color(1.0,1.0,1.0));
    }

    //如果没有交点，则绘制渐变背景
    //将光线转换为单位向量
    vec3 unit_direction=unit_vector(r.direction());
    //将y坐标的范围从[-1,1]映射到[0,1]，便于之后按比例混合颜色
    //由于主函数规定的视口高度为2，以视口中心为0，则高度的范围就是【-1，1】
    auto a=0.5*(unit_direction.y+1.0);
    //返回白色和蓝色混合后的颜色
    return (1.0-a)*color(1.0,1.0,1.0)+a*color(0.5,0.7,1.0);
}

int main() {
    //输出流对象
    //使用fstram替代cout标准输出，以避免异常的不可见字符
    std::ofstream out("image.ppm", std::ios::out | std::ios::binary);
    if (!out) {
        std::cerr << R"(创建文件失败)" << std::endl;
        return 1;
    }

    //world
    //创建可击中对象列表并添加两个shpere
    hittable_list world;
    world.add(make_shared<sphere>(point3(0.0,0.0,-1.0),0.5));
    world.add(make_shared<sphere>(point3(0.0,-100.5,-1.0),100));

    //camera
    //创建相机和世界
    camera cam;
    cam.image_width=400;
    cam.aspect_ratio=16.0/9.0;

    //渲染
    cam.render(out,world);

    //关闭输出流
    out.close();
    return 0;
}
