#include "geometry.h"

#include <stack>

// Readfile definitions 

void matransform(std::stack<Mat4> &transfstack, float * values);
void rightmultiply(const Mat4 & M, std::stack<Mat4> &transfstack);
bool readvals(std::stringstream &s, const int numvals, float * values);
void readfile(const char * filename, Camera & cam, Scene & scene, int & max_depth, std::string & outfile);