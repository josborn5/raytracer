#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>

using std::sqrt;

class vec3
{
	public:
		vec3()
			: e{ 0, 0, 0 }
		{}
		vec3(double e0, double e1, double e2)
			: e{ e0, e1, e2 }
		{}

		double x() const { return e[0]; }
		double y() const { return e[1]; }
		double z() const { return e[2]; }

		vec3 negate()
		{
			return vec3(-e[0], -e[1], -e[3]);
		}

		vec3 multiply_by_scalar(double t)
		{
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		vec3 add_vector(const vec3 v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		double length() const
		{
			return sqrt(length_squared());
		}

		double length_squared() const
		{
			return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
		}

	private:
		double e[3];

};

#endif
