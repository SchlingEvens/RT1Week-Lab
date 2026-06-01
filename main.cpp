#include <iostream>
#include <fstream>
#include "utils/utils.h"

/**
 *
 * @param center 球体中心
 * @param radius 球半径
 * @param r 光线
 * @return 是否在球上/内部
 */
bool hit_sphere(const point3& center,double radius,const ray& r) {
    auto delta_a=dot(r.direction(),r.direction());
    auto delta_b=-2*dot(r.direction(),(center-r.origin()));
    auto delta_c=dot(center-r.origin(),r.direction())-radius*radius;
    return sqrt(delta_b*delta_b-4*delta_a*delta_c)>=0;
}

color ray_color(const ray& r) {
    if (hit_sphere(point3(0,0,-1),0.5,r))return color(1.0,0.0,0.0);

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
            auto pixel_center=pixel00_loc+i*pixel_delta_u+j*pixel_delta_v;
            //计算指向当前像素的光线的方向
            auto ray_direction=pixel_center-camera_center;
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
