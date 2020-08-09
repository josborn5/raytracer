#ifndef METAL_H
#define METAL_H

#include "material.h"

class metal : public material
{
	public:
		metal(const vec3 &a) : albedo(a) {}

		virtual bool scatter(const ray &in, const hit_record &hit, vec3 &attenuation, ray &scattered) const override
		{
			vec3 reflected = reflect(unit_vector(in.direction()), hit.normal);
			scattered = ray(hit.position, reflected);
			attenuation = albedo;
			float dot = dot_product(scattered.direction(), hit.normal);
			return (dot > 0.0f);
		}

	public:
		vec3 albedo;
};

#endif