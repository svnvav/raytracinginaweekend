#include <iostream>
#include <fstream>
#include "sphere.h"
#include "camera.h"
#include "hitable_list.h"
#include "float.h"

using namespace std;

vec3 color(const ray& r, hitable *world) {
	hit_record rec;

	if (world->hit(r, 0.0f, FLT_MAX, rec)) {
		return 0.5f * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}

	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main() {
	int nx = 256;
	int ny = 128;
	int ns = 64;

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
				float u = float(i + ((double)rand() / (RAND_MAX + 1))) / float(nx);
				float v = float(j + ((double)rand() / (RAND_MAX + 1))) / float(ny);

				ray r = cam.get_ray(u, v);

				col += color(r, world);
				//vec3 p = r.point_at_parameter(2.0f);
			}
			col /= float(ns);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outfile << ir << " " << ig << " " << ib << "\n";
		}

	outfile.close();

}