#include "readfile.h"

#include "camera.h"
#include "image.h"
#include "raytracer.h"
#include "readfile.h"
#include "scene.h"

#include <iostream>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "not enough arguments\n";
        exit(-1);
    }

    for (int i = 1; i < argc; ++i) {
        std::string outfile;
        int max_depth = 5;
        Camera camera;
        Scene scene;
        int width;
        double aspect;
        readfile(argv[i], camera, scene, width, aspect, max_depth, outfile);
        Raytracer r(max_depth);
        Image image = r.raytrace(scene, camera, width);
        image.save(outfile);
    }

    return 0;
}