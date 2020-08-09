#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

class lambertian : public material
{
	public:
		lambertian(const vec3 &color) : albedo(color) {}

		virtual bool scatter(const ray &in, const hit_record &hit, vec3 &attenuation, ray &scattered) const override
		{
			vec3 scatter_direction = add_vectors(hit.normal, random_unit_vec3());
			scattered = ray(hit.position, scatter_direction);
			attenuation = albedo;
			return true;
		}

	public:
		vec3 albedo;
};

#endif