#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
	public:
		ray() {}
		ray(const vec3 &origin, const vec3 &direction)
			: orig(origin), dir(direction)
		{}

		vec3 origin() const { return orig; }
		vec3 direction() const { return dir; }

		vec3 point_at_time(float t) const
		{
			vec3 delta = multiply_by_scalar(dir, t);
			vec3 result = add_vectors(orig, delta);
			return result;
		}

	private:
		vec3 orig;
		vec3 dir;
};

#endif
