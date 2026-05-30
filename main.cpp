#include <iostream>
#include <fstream>
#include "utils/utils.h"

color ray_color(const ray& r) {
    return color(0,0,0);
}

int main() {
    //输出流对象
    //使用fstram替代cout标准输出，以避免异常的不可见字符
    std::ofstream out("image.ppm", std::ios::out | std::ios::binary);
    if (!out) {
        std::cerr << R"(创建文件失败)" << std::endl;
        return 1;
    }
    
    //Image
    auto aspect_ratio=16.0/9.0;
    int image_width=400;
    int image_height=image_width/aspect_ratio<1?1:image_width/aspect_ratio;

    //Camera
    auto focal_length=1.0;     //焦距
    auto view_height=2.0;      //视口高度
    auto view_width=view_height*((double)image_width/image_height);  //视口宽度
    auto camera_center=point3(0,0,0);    //相机/视点坐标

    //从视口左边缘到右边缘、上边缘到下边缘的向量
    auto view_u=vec3(view_width,0,0);
    auto view_v=vec3(0,-view_height,0);

    //像素在水平和垂直方向上的步进增量
    //这表示每向右/下移动一个像素，在3d空间中需要移动的距离
    //3d空间是指视口所在的3d空间。我们将焦距设为1，这里的步进增量也是相对这个单位1定义的坐标系
    auto pixel_delta_u=view_u/image_width;
    auto pixel_delta_v=view_v/image_height;

    //获得视口左上角顶点在3d空间中的坐标
    auto view_upper_left=camera_center-vec3(0,0,focal_length)-view_v/2-view_u/2;
    //获得视口左上角顶点像素的像素中心
    auto pixel00_loc=view_upper_left+0.5*(pixel_delta_u+pixel_delta_v);

    //Render && PPMInput
    out<<"P3\n"<<image_width<<' '<<image_height<<'\n'<<"255\n";

    for (int j=0;j<image_height;j++) {
        //输出进度,\r表示光标回到当前行行首
        std::clog<<"\r当前进度："<<(image_height-j)<<' '<<std::flush;
        for (int i=0;i<image_width;i++) {
            //计算当前像素中心，光线会从视点指向当前像素中心
            auto pixel_center=pixel00_loc+i*pixel_delta_u;
            //计算指向当前像素的光线的方向
            auto ray_direction=camera_center-pixel_center;
            //声明当前光线的实例
            ray r(camera_center,ray_direction);
            //使用pixel_color方法得到当前像素的颜色
            auto pixel_color=ray_color(r);
            //将颜色输出到文件
            write_color(out,pixel_color);
        }
    }
    std::clog<<"\r结束                                     \n";
    out.close();
    return 0;
}
