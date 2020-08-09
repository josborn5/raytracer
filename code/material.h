#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"

struct hit_record;

class material
{
	public:
		virtual bool scatter(const ray &in, const hit_record &hit, vec3 &attenuation, ray &scattered) const = 0;
};

#endif