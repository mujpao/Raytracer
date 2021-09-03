#ifndef READFILE_H
#define READFILE_H

#include <iosfwd>
#include <stack>
#include <string>

class Mat4;
class Camera;
class Scene;

void matransform(std::stack<Mat4>& transfstack, float* values);
void rightmultiply(const Mat4& M, std::stack<Mat4>& transfstack);
bool readvals(std::stringstream& s, const int numvals, float* values);
void readfile(const char* filename, Camera& camera, Scene& scene, int& width,
    double& aspect, int& max_depth, std::string& outfile);

#endif
