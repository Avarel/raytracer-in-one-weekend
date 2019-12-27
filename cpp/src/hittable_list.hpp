#ifndef HITABLE_LIST_HPP
#define HITABLE_LIST_HPP
#include "hittable.hpp"

class hittable_list : public hittable {
public:
    int list_size;
    hittable **list;

    hittable_list() {}
    hittable_list(hittable **l, int n) : list(l), list_size(n) {}
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
};

bool hittable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif