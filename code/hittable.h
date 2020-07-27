#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"

struct hit_record
{
	vec3 position;
	vec3 normal;
	float time;
	bool front_face;

	void set_face_normal(const ray &r, const vec3 &outward_normal)
	{
		front_face = dot_product(r.direction(), outward_normal) < 0.0f;
		normal = front_face ? outward_normal : outward_normal.negate();
	}
};

class hittable
{
	public:
		virtual bool hit(const ray &r, float t_min, float t_max, hit_record &hit) const = 0;
};

#endif