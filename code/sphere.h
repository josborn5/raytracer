#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
	public:
		sphere() {}
		sphere (const vec3 center, float radius) : center(center), radius(radius) {};

		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& hit) const override;

	public:
		vec3 center;
		float radius;
};

void populate_hit_record(hit_record& hit, float collision_time,const ray& r, const vec3& sphere_center)
{
	hit.time = collision_time;
	hit.position = r.point_at_time(hit.time);
	vec3 outward_normal = subtract_vectors(hit.position, sphere_center);
	hit.set_face_normal(r, outward_normal);
}

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& hit) const
{
	vec3 origin_to_sphere_center = subtract_vectors(r.origin(), center);
	float a = r.direction().length_squared();
	float half_b = dot_product(origin_to_sphere_center, r.direction());
	float c = dot_product(origin_to_sphere_center, origin_to_sphere_center) - (radius * radius);
	float discriminant = (half_b * half_b) - (a * c);

	if (discriminant > 0.0f)
	{
		float root = sqrt(discriminant);

		float collision_time = (-half_b - root) / a;
		if (collision_time < t_max && collision_time > t_min)
		{
			populate_hit_record(hit, collision_time, r, center);
			return true;
		}

		collision_time = (-half_b + root) / a;
		if (collision_time < t_max && collision_time > t_min)
		{
			populate_hit_record(hit, collision_time, r, center);
			return true;
		}
	}

	return false;
}

#endif