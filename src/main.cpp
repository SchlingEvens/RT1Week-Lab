#include <iostream>
#include <fstream>
#include "math/rtweek.h"
#include "core/camera.h"
#include "shape/hittable_list.h"
#include "shape/sphere.h"
#include "shape/hittable.h"

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
    cam.sample=100;
    cam.max_depth=10;

    //渲染
    cam.render(out,world);

    //关闭输出流
    out.close();
    return 0;
}
