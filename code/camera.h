#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
	public:
		camera()
		{
			float aspect_ratio = 16.0f / 9.0f;
			float viewport_height = 2.0f;
			float viewport_width = aspect_ratio * viewport_height;
			float focal_length = 1.0f;

			origin = vec3(0, 0, 0);
			horizontal = vec3(viewport_width, 0, 0);
			vertical = vec3(0, viewport_height, 0);
			vec3 half_horizontal = multiply_by_scalar(horizontal, -0.5f);
			vec3 half_vertical  = multiply_by_scalar(vertical, -0.5f);

			vec3 lower_left_corner = add_vectors(origin, half_horizontal, half_vertical);
			focal_plane_lower_left_corner = add_vectors(lower_left_corner, vec3(0, 0, -focal_length));
		}

		ray get_ray(float u, float v) const
		{
			vec3 horizontal_offset = multiply_by_scalar(horizontal, u);
			vec3 vertical_offset = multiply_by_scalar(vertical, v);

			vec3 point_on_focal_plane = add_vectors(focal_plane_lower_left_corner, horizontal_offset, vertical_offset);
			vec3 direction = subtract_vectors(point_on_focal_plane, origin);
			return ray(origin, direction);
		}

	private:
		vec3 origin;
		vec3 focal_plane_lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
};

#endif