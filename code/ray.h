#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
	public:
		ray() {}
		ray(vec3& origin, vec3& direction)
			: orig(origin), dir(direction)
		{}

		vec3 origin() { return orig; }
		vec3 direction() { return dir; }

		vec3 point_at_time(float t)
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
