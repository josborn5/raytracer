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

		vec3 origin() const { return orig; }
		vec3 direction() const { return dir; }

		vec3 point_at_time(double t)
		{
			vec3 delta = dir.multiply_by_scalar(t);
			vec3 result = orig.add_vector(delta);
			return result;
		}

	private:
		vec3 orig;
		vec3 dir;
};

#endif
