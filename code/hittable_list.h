#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>

#include "hittable.h"

class hittable_list : public hittable
{
	public:
		hittable_list() {}
		hittable_list(std::shared_ptr<hittable> object) { add(object); }

		void clear() { objects.clear(); }
		void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

		virtual bool hit(const ray &r, float t_min, float t_max, hit_record &hit) const override;

	public:
		std::vector<std::shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray &r, float t_min, float t_max, hit_record &hit) const
{
	hit_record temp_hit;
	bool hit_anything = false;
	float closest_so_far = t_max;

	for (const std::shared_ptr<hittable>& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_hit))
		{
			hit_anything = true;
			closest_so_far = temp_hit.time;
			hit = temp_hit;
		}
	}
	return hit_anything;
}

#endif