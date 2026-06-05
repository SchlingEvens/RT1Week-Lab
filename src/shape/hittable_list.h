//
// Created by Klingsor on 2026/6/4.
//

#ifndef RT1WEEK_HITTABLE_LIST_H
#define RT1WEEK_HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"
#include "../core/ray.h"
#include "../math/interval.h"
using std::make_shared;
using std::shared_ptr;

//可击中对象列表
//继承hittable是为了可以将列表也视为一个可击中对象，以便在需要时进行嵌套
class hittable_list : public hittable {
public:
    //使用shared指针简化操作，实际项目不推荐
    std::vector<shared_ptr<hittable>> objects;

    //创建一个空的可击中列表在语义上是合理的，因此需要无参构造函数
    hittable_list(){};
    hittable_list(shared_ptr<hittable> object){ add(object); }

    void add(shared_ptr<hittable> object){ objects.push_back(object); }
    void clear(){objects.clear();}

    bool hit(const ray& r, interval t, hit_record& rec) const override {
        hit_record temp_record;
        //当前最近的碰撞点和视点的距离
        double closest_so_f=t.max;
        //当前是否存在能够碰撞的点
        bool isHit=false;

        //遍历当前列表中的所有可击中对象，返回最近的碰撞切片
        for (const auto& object : objects) {
            if (object->hit(r,interval(t.min,closest_so_f),temp_record)) {
                isHit=true;
                rec=temp_record;
                closest_so_f=rec.t;
            }
        }
        return isHit;
    }

};

#endif //RT1WEEK_HITTABLE_LIST_H
