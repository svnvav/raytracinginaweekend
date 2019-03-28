#include <iostream>
#include <fstream>
#include "sphere.h"
#include "material.h"
#include "camera.h"
#include "hitable_list.h"
#include "float.h"

using namespace std;

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;

	if (world->hit(r, 0.001f, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		return vec3(0, 0, 0);
	}

	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main() {
	int nx = 1024;
	int ny = 768;
	int ns = 32;

	ofstream outfile;
	outfile.open("HelloWorld.ppm");
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	hitable *list[5];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f, new lambertian(vec3(0.8f, 0.3f, 0.3f)));
	list[1] = new sphere(vec3(0, -100.5f, -1), 100, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f), 0.5f));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5f, new dielectric(1.5f));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45f, new dielectric(1.5f));
	hitable *world = new hitable_list(list, 5);
	
	camera cam(vec3(-2.0f, 2.0f, 1.0f), vec3(0, 0, -1), vec3(0, 1, 0), 90, float(nx)/float(ny));
	for (int j = ny - 1; j >= 0; --j)
		for(int i = 0; i < nx; ++i)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; ++s) {
				float u = float(i + rand01()) / float(nx);
				float v = float(j + rand01()) / float(ny);

				ray r = cam.get_ray(u, v);

				col += color(r, world, 0);
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