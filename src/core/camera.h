//
// Created by Klingsor on 2026/6/5.
//

#ifndef RT1WEEK_CAMERA_H
#define RT1WEEK_CAMERA_H

#include "../shape/hittable.h"
#include "../shape/hittable_list.h"
#include "../shape/sphere.h"
#include "../math/rtweek.h"

class camera {
public:
    //将输出图像宽度和宽高比作为成员变量，此处的初始值仅作为默认，实际渲染时可以在调用render方法前修改为实际值
    double aspect_ratio=1.0;
    int image_width=100;

    //接收可击中对象列表，初始化世界空间和摄像机，逐像素发射光线计算渲染结果
    void render(std::ostream& out ,const hittable& world) {
        init();

        //PPM文件头
        out<<"P3\n"<<image_width<<' '<<image_height<<'\n'<<"255\n";

        //逐像素渲染
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
                //使用ray_color方法得到当前像素的颜色
                auto pixel_color=ray_color(r,world);
                //将颜色输出到文件
                write_color(out,pixel_color);
            }
        }
        std::clog<<"\r结束                                     \n";

    }
private:
    int image_height=100;
    point3 camera_center;

    //像素在水平和垂直方向上的步进增量
    point3 pixel_delta_u;
    point3 pixel_delta_v;

    //视口左上角顶点像素的像素中心
    point3 pixel00_loc;


    void init() {
        image_height=image_width/aspect_ratio<1?1:image_width/aspect_ratio;

        //Camera
        auto focal_length=1.0;     //焦距
        auto view_height=2.0;      //视口高度
        auto view_width=view_height*((double)image_width/image_height);  //视口宽度
        camera_center=point3(0,0,0);    //相机/视点坐标

        //从视口左边缘到右边缘、上边缘到下边缘的向量
        auto view_u=vec3(view_width,0.0,0.0);
        auto view_v=vec3(0.0,-view_height,0.0);

        //像素在水平和垂直方向上的步进增量
        //这表示每向右/下移动一个像素，在3d空间中需要移动的距离
        //3d空间是指视口所在的3d空间。我们将焦距设为1，这里的步进增量也是相对这个单位1定义的坐标系
        pixel_delta_u=view_u/image_width;
        pixel_delta_v=view_v/image_height;

        //获得视口左上角顶点在3d空间中的坐标
        auto view_upper_left=camera_center-vec3(0,0,focal_length)-view_v/2-view_u/2;
        //获得视口左上角顶点像素的像素中心
        pixel00_loc=view_upper_left+0.5*(pixel_delta_u+pixel_delta_v);

    }


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

};

#endif //RT1WEEK_CAMERA_H
