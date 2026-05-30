#include <iostream>
#include <fstream>
#include "utils/utils.h"

int main() {
    int image_width=256,image_height=256;

    //使用fstram替代cout标准输出，以避免异常的不可见字符
    std::ofstream out("image.ppm", std::ios::out | std::ios::binary);
    if (!out) {
        std::cerr << "无法创建文件！" << std::endl;
        return 1;
    }

    out<<"P3\n"<<image_width<<' '<<image_height<<'\n'<<"255\n";

    for (int j=0;j<image_height;j++) {
        //输出进度,\r表示光标回到当前行行首
        std::clog<<"\r当前进度："<<(image_height-j)<<' '<<std::flush;
        for (int i=0;i<image_width;i++) {
            auto pixel_color=color(float(i)/(image_width-1),float(j)/(image_height-1),0.0f);
            write_color(out,pixel_color);
        }
    }
    std::clog<<"\r结束                                     \n";
    out.close();
    return 0;
}
