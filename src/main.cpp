#include "geometry.h"
#include "readfile.h"

#include <cassert>
#include <iostream>

// void run_grader() {
// 	std::vector<std::string> filenames{ "scene4-ambient",
// 								"scene4-diffuse",
// 								"scene4-emission",
// 								"scene4-specular",
// 								"scene5",
// 								"scene6",
// 								"scene7"
// 								};

// 	// std::vector<std::string> filenames{ "scene4-ambient" };

// 	//vector<string> filenames{ "scene6" };

// 	for (auto & filename : filenames) {
// 		std::string infile = "..\\hw3-submissionscenes\\" + filename + ".test";
// 		std::string outfile;
// 		int max_depth = 5;
// 		Camera cam;
// 		Scene scene;
// 		readfile(infile.c_str(), cam, scene, max_depth, outfile);
// 		Raytracer r(max_depth);
// 		Image i = r.raytrace(cam, scene);
// 		i.save(outfile);
// 	}

// }

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