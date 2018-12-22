#include <stack>
using namespace std;
#include "geometry.h"

// Readfile definitions 

void matransform(stack<Mat4> &transfstack, float * values);
void rightmultiply(const Mat4 & M, stack<Mat4> &transfstack);
bool readvals(stringstream &s, const int numvals, float * values);
void readfile(const char * filename);