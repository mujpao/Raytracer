#include "readfile.h"

#include "camera.h"
#include "scene.h"
#include "raytracer.h"
#include "image.h"
#include "readfile.h"

#include <cassert>
#include <iostream>

int main(int argc, char * argv[]) {	

	if (argc < 2) {
		std::cerr << "not enough arguments\n";
		exit(-1);
	}

	for (int i = 1; i < argc; ++i) {
		std::string outfile;
		int max_depth = 5;
		Camera cam;
		Scene scene;
		readfile(argv[i], cam, scene, max_depth, outfile);
		Raytracer r(max_depth);
		Image image = r.raytrace(cam, scene);
		image.save(outfile);
	}

	return 0;
}