/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix
// transformations for a stack (matransform) and to rightmultiply the
// top of a stack.  These functions are given to aid in setting up the
// transformations properly, and to use glm functions in the right way.
// Their use is optional in your program.

// The functions readvals and readfile do basic parsing.  You can of course
// rewrite the parser as you wish, but we think this basic form might be
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE.
// Read the other parts to get a context of what is going on.

/*****************************************************************************/

#include "readfile.h"

#include "camera.h"
#include "image.h"
#include "light.h"
#include "math/mat4.h"
#include "math/transform.h"
#include "phongmaterial.h"
#include "raytracer.h"
#include "scene.h"
#include "shape.h"

#include <fstream>
#include <iostream>
#include <sstream>

// The function below applies the appropriate transform to a 4-vector
void matransform(std::stack<Mat4>& transfstack, float* values) {
    Mat4 transform = transfstack.top();
    Vec valvec = Vec(values[0], values[1], values[2], values[3]);
    Vec newval = transform * valvec;
    for (int i = 0; i < 4; i++)
        values[i] = newval[i];
}

void rightmultiply(const Mat4& M, std::stack<Mat4>& transfstack) {
    Mat4& T = transfstack.top();
    T = T * M;
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.
bool readvals(std::stringstream& s, const int numvals, float* values) {
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            std::cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

void readfile(const char* filename, Camera& camera, Scene& scene,
    int& max_depth, std::string& outfile) {
    std::string str, cmd;
    std::ifstream in;
    Vec eye;
    Vec up;
    Vec center;
    int w, h;
    float fov;
    Vec diffuse, specular, emission;
    Vec color, direction;
    Vec light_location;
    int i;

    // set values to defaults
    max_depth = 5;
    Vec attenuation(1.0, 0.0, 0.0);
    Vec ambient(0.2, 0.2, 0.2);
    outfile = "output.png";
    float shininess = 0; // default shininess value of 0

    std::vector<Vec> vertices;

    in.open(filename);
    if (in.is_open()) {

        // I need to implement a matrix stack to store transforms.
        // This is done using standard STL Templates
        std::stack<Mat4> transfstack;
        transfstack.push(Mat4(1.0)); // identity
        getline(in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
                && (str[0] != '#')) {
                // Ruled out comment and blank lines

                std::stringstream s(str);
                s >> cmd;
                // int i;
                float values[10]; // Position and color for light, colors for
                                  // others
                // Up to 10 params for cameras.
                bool validinput; // Validity of input

                // Process the light, add it to database.
                // Lighting Command
                if (cmd == "directional") {
                    validinput
                        = readvals(s, 6, values); // Position/color for lts.
                    if (validinput) {
                        direction[0] = values[0];
                        direction[1] = values[1];
                        direction[2] = values[2];
                        color[0] = values[3];
                        color[1] = values[4];
                        color[2] = values[5];
                        color[3] = 1.0;

                        scene.lights.push_back(
                            std::make_shared<DirectionalLight>(
                                color, direction));
                    }

                } else if (cmd == "point") {
                    validinput
                        = readvals(s, 6, values); // Position/color for lts.
                    if (validinput) {
                        light_location[0] = values[0];
                        light_location[1] = values[1];
                        light_location[2] = values[2];
                        light_location[3] = 1.0;
                        color[0] = values[3];
                        color[1] = values[4];
                        color[2] = values[5];
                        color[3] = 1.0;

                        scene.lights.push_back(std::make_shared<PointLight>(
                            attenuation, color, light_location));
                    }
                    // reset attenuation regardless of whether input was valid
                    // attenuation = atten_default;

                } else if (cmd == "attenuation") {
                    validinput
                        = readvals(s, 3, values); // Position/color for lts.
                    if (validinput) {
                        attenuation[0] = values[0];
                        attenuation[1] = values[1];
                        attenuation[2] = values[2];
                    }
                }

                // Material Commands
                // Ambient, diffuse, specular, shininess properties for each
                // object. Filling this in is pretty straightforward, so I've
                // left it in the skeleton, also as a hint of how to do the more
                // complex ones. Note that no transforms/stacks are applied to
                // the colors.

                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            ambient[i] = values[i];
                        }
                        ambient[3] = 1.0;
                    }
                } else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            diffuse[i] = values[i];
                        }
                        diffuse[3] = 1.0;
                    }
                } else if (cmd == "specular") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            specular[i] = values[i];
                        }
                        specular[3] = 1.0;
                    }
                } else if (cmd == "emission") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            emission[i] = values[i];
                        }
                        emission[3] = 1.0;
                    }
                } else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        shininess = values[0];
                    }
                } else if (cmd == "size") {
                    validinput = readvals(s, 2, values);
                    if (validinput) {
                        w = (int)values[0];
                        h = (int)values[1];
                    }
                }
                // process ray depth
                else if (cmd == "maxdepth") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        max_depth = (int)values[0];
                    }
                } else if (cmd == "output") {
                    s >> outfile; // TODO validate input
                } else if (cmd == "camera") {
                    validinput
                        = readvals(s, 10, values); // 10 values eye cen up fov
                    if (validinput) {

                        eye[0] = values[0];
                        eye[1] = values[1];
                        eye[2] = values[2];
                        center[0] = values[3];
                        center[1] = values[4];
                        center[2] = values[5];
                        center[3] = 1.0;
                        up[0] = values[6];
                        up[1] = values[7];
                        up[2] = values[8];
                        fov = values[9];
                    }
                }

                else if (cmd == "maxverts") {
                    validinput = readvals(s, 1, values);

                    if (validinput) {
                        vertices.reserve(values[0]);
                    }
                } else if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);

                    if (validinput) {
                        vertices.emplace_back(
                            values[0], values[1], values[2], 1.0);
                    }
                } else if (cmd == "sphere" || cmd == "tri") {

                    if (cmd == "sphere") {
                        validinput = readvals(s, 4, values);

                        if (validinput) {
                            scene.objects.push_back(std::make_shared<Sphere>(
                                Vec(values[0], values[1], values[2]), values[3],
                                transfstack.top(),
                                std::make_shared<PhongMaterial>(ambient,
                                    diffuse, specular, shininess, emission)));
                        }
                    } else if (cmd == "tri") {
                        validinput = readvals(s, 3, values);

                        if (validinput) {
                            scene.objects.push_back(std::make_shared<Triangle>(
                                vertices[values[0]], vertices[values[1]],
                                vertices[values[2]], transfstack.top(),
                                std::make_shared<PhongMaterial>(ambient,
                                    diffuse, specular, shininess, emission)));
                        }
                    }

                    // reset ambient to default
                    // ambient = ambient_default;
                }

                else if (cmd == "translate") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE.
                        // Think about how the transformation stack is affected
                        // You might want to use helper functions on top of
                        // file. Also keep in mind what order your matrix is!

                        rightmultiply(Transform::translate(
                                          values[0], values[1], values[2]),
                            transfstack);
                    }
                } else if (cmd == "scale") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE.
                        // Think about how the transformation stack is affected
                        // You might want to use helper functions on top of
                        // file. Also keep in mind what order your matrix is!

                        rightmultiply(
                            Transform::scale(values[0], values[1], values[2]),
                            transfstack);
                    }
                } else if (cmd == "rotate") {
                    validinput = readvals(s, 4, values);
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE.
                        // values[0..2] are the axis, values[3] is the angle.
                        // You may want to normalize the axis (or in
                        // Transform::rotate) See how the stack is affected, as
                        // above. Note that rotate returns a mat3. Also keep in
                        // mind what order your matrix is!
                        Vec axis(values[0], values[1], values[2]);
                        axis = Vec::normalize(axis);
                        Mat4 rotated = Transform::rotate(values[3], axis);

                        rightmultiply(rotated, transfstack);
                    }
                }

                // I include the basic push/pop code for matrix stacks
                else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top());
                } else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        std::cerr << "Stack has no elements.  Cannot Pop\n";
                    } else {
                        transfstack.pop();
                    }
                }

                else {
                    std::cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
        }

        camera = Camera(eye, center, up, fov, w, h);
    } else {
        std::cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2; // TODO change
    }
}
