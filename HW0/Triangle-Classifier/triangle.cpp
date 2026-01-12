
#include "triangle.h"
using namespace std;

Triangle::Triangle(double side1, double side2, double side3) {
   a = side1; b = side2; c = side3;
}


//the following code is not complete/correct. You need to find the problems and fix it
string Triangle::getClass() {// possible return values: "equilateral","isosceles","scalene","invalid"  
   if (a < 0 || b < 0 || c < 0) return "invalid";
   if (a + b <= c || a + c <= b || b + c <= a) return "invalid";
   if (a == b && b == c) return "equilateral";
   if (a == b || b == c || a == c) return "isosceles";
   return "scalene";
}