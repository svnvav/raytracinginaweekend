#include <iostream>
#include <fstream>
#include "sphere.h"
#include "camera.h"
#include "hitable_list.h"
#include "float.h"

using namespace std;

float rand01() {
	return ((float)rand() / (RAND_MAX + 1));
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0f * vec3(rand01(), rand01(), rand01()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0f);
	return p;
}

vec3 color(const ray& r, hitable *world) {
	hit_record rec;

	if (world->hit(r, 0.001f, FLT_MAX, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5f * color(ray(rec.p, target - rec.p), world);
	}

	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main() {
	int nx = 512;
	int ny = 256;
	int ns = 32;

	ofstream outfile;
	outfile.open("HelloWorld.ppm");
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f);
	list[1] = new sphere(vec3(0, -100.5f, -1), 100);
	hitable *world = new hitable_list(list, 2);
	
	camera cam;
	for (int j = ny - 1; j >= 0; --j)
		for(int i = 0; i < nx; ++i)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; ++s) {
				float u = float(i + rand01()) / float(nx);
				float v = float(j + rand01()) / float(ny);

				ray r = cam.get_ray(u, v);

				col += color(r, world);
				//vec3 p = r.point_at_parameter(2.0f);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outfile << ir << " " << ig << " " << ib << "\n";
		}

	outfile.close();

}