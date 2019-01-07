#include <cassert>
#include <FreeImage.h>

using namespace std;
#include "transform.h"
#include "geometry.h"
#include "tests.h"
#include "readfile.h"
#include "variables.h"


#define GRADING


void run_grader() {
	/*vector<string> filenames{ "scene4-ambient",
								"scene4-diffuse",
								"scene4-emission",
								"scene4-specular",
								"scene5",
								"scene6",
								"scene7"
								};*/

	/*vector<string> filenames{ "scene4-ambient",
		"scene4-diffuse",
		"scene4-emission",
		"scene4-specular"
		};*/

	vector<string> filenames{ "scene4-specular" };

	for (auto & filename : filenames) {
		string infile = "..\\hw3-submissionscenes\\" + filename + ".test";
		std::string outfile;
		int max_depth = 5;
		Camera cam;
		Scene scene;
		readfile(infile.c_str(), cam, scene, max_depth, outfile);
		Raytracer r(max_depth);
		Image i = r.raytrace(cam, scene);
		i.save(outfile);
	}

}

int main(int argc, char * argv[]) {	

	FreeImage_Initialise();


#ifdef GRADING
	run_grader();
#else
	if (argc < 2) {
		cerr << "not enough arguments\n";
		exit(-1);
	}

	std::string outfile;
	int max_depth = 5;
	Camera cam;
	Scene scene;
	readfile(argv[1], cam, scene, max_depth, outfile);
	Raytracer r(max_depth);
	Image i = r.raytrace(cam, scene);
	i.save(outfile);
#endif

	FreeImage_DeInitialise();
	
	return 0;
}