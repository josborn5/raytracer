#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
	public:
		camera(vec3 look_from, vec3 look_at, vec3 up, float vertical_fov_deg, float aspect_ratio)
		{
			float theta = degrees_to_radians(vertical_fov_deg);
			float h = tan(theta / 2.0f);
			float viewport_height = 2.0f * h;
			float viewport_width = aspect_ratio * viewport_height;

			vec3 w = unit_vector(subtract_vectors(look_from, look_at));
			vec3 u = unit_vector(cross_product(up, w));
			vec3 v = cross_product(w, u);


			float focal_length = 1.0f;

			origin = look_from;
			horizontal = multiply_by_scalar(u, viewport_width);
			vertical = multiply_by_scalar(v, viewport_height);

			vec3 half_horizontal = multiply_by_scalar(horizontal, -0.5f);
			vec3 half_vertical  = multiply_by_scalar(vertical, -0.5f);

			vec3 lower_left_corner = add_vectors(origin, half_horizontal, half_vertical);
			focal_plane_lower_left_corner = subtract_vectors(lower_left_corner, w);
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