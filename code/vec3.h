#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>
#include "constants.h"

using std::sqrt;

class vec3
{
	public:
		vec3()
			: e{ 0, 0, 0 }
		{}
		vec3(float e0, float e1, float e2)
			: e{ e0, e1, e2 }
		{}

		float x() const { return e[0]; }
		float y() const { return e[1]; }
		float z() const { return e[2]; }

		vec3 negate() const
		{
			return vec3(-e[0], -e[1], -e[3]);
		}

		vec3 multiply_current(float t)
		{
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		vec3 add_current(const vec3 &v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		float length() const
		{
			return sqrt(length_squared());
		}

		float length_squared() const
		{
			return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
		}

		static vec3 random(float min, float max)
		{
			return vec3(random_float(min, max), random_float(min, max), random_float(min, max));
		}

	private:
		float e[3];

};

vec3 add_vectors(const vec3 &v1, const vec3 &v2)
{
	return vec3(
		v1.x() + v2.x(),
		v1.y() + v2.y(),
		v1.z() + v2.z()
	);
}

vec3 add_vectors(const vec3 &v1, const vec3 &v2, const vec3 &v3)
{
	return vec3(
		v1.x() + v2.x() + v3.x(),
		v1.y() + v2.y() + v3.y(),
		v1.z() + v2.z() + v3.z()
	);
}

vec3 subtract_vectors(const vec3 &v1, const vec3 &v2)
{
	return vec3(
		v1.x() - v2.x(),
		v1.y() - v2.y(),
		v1.z() - v2.z()
	);
}

vec3 multiply_vectors(const vec3 &v1, const vec3 &v2)
{
	return vec3(
		v1.x() * v2.x(),
		v1.y() * v2.y(),
		v1.z() * v2.z()
	);
}

vec3 multiply_by_scalar(const vec3 &v, float t)
{
	return vec3(
		v.x() * t,
		v.y() * t,
		v.z() * t
	);
}

vec3 unit_vector(const vec3 &v)
{
	float scale_factor = 1 / v.length();
	return multiply_by_scalar(v, scale_factor);
}

float dot_product(const vec3 &v1, const vec3 &v2)
{
	return
		(v1.x() * v2.x()) +
		(v1.y() * v2.y()) +
		(v1.z() * v2.z());
}

vec3 random_in_unit_sphere()
{
	while (true)
	{
		vec3 p = vec3::random(-1, 1);
		if (p.length_squared() < 1) return p;
	}
}

vec3 random_unit_vec3()
{
	float a = random_float(0, 2 * pi);
	float z = random_float(-1, 1);
	float r = sqrt(1 - (z * z));
	return vec3(r * cos(a), r * sin(a), z);
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
	float factor = 2.0f * dot_product(v, n);
	return subtract_vectors(v, multiply_by_scalar(n, factor));
}

#endif
