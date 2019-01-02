#include <cassert>
#include <FreeImage.h>

using namespace std;
#include "transform.h"
#include "geometry.h"
#include "tests.h"
#include "readfile.h"
#include "variables.h"


Camera * cam;
Scene scene;
int max_depth = 5;
Vec atten_default(1.0f, 0.0f, 0.0f);
Vec ambient_default(0.2f, 0.2f, 0.2f);
std::string outfile("output.png");

int main(int argc, char * argv[]) {
	//run_tests();
	if (argc < 2) {
		cerr << "not enough arguments\n";
		exit(-1);
	}

	FreeImage_Initialise();

	readfile(argv[1]);

	Raytracer r(max_depth);
	Image i = r.raytrace(*cam, scene);
	i.save(outfile);

	FreeImage_DeInitialise();
	
	return 0;
}