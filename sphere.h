#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere : public hitable {
public:
	sphere() {}
	sphere(vec3 c, float r) : center(c), radius(r) {};

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

	vec3 center;
	float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 ac = r.A - center;
	float a = dot(r.B, r.B);
	float b = dot(r.B, ac);
	float c = dot(ac, ac) - radius * radius;
	float d = b * b - a * c;

	if (d > 0) {
		float temp = (-b - sqrt(d)) / a;
		if (t_min < temp && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(d)) / a;
		if (t_min < temp && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}

	return false;
}

#endif