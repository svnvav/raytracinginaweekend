#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
public:
	camera(vec3 &lookfrom, vec3 &lookat, vec3 &vup, float vfov, float aspect) {

		vec3 w, u, v;

		float theta = vfov * M_PI / 180.0f;
		float half_height = tan(theta/2.0f);
		float half_width = aspect * half_height;

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		//lower_left_corner = vec3(-half_width, -half_height, -1.0f);
		origin = lookfrom;
		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2.0f * half_width * u;
		vertical = 2.0f * half_height * v;

	}

	ray get_ray(float u, float v) {
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

#endif
