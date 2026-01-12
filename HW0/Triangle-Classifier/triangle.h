#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
using namespace std;// see below about namespace and std

class Triangle {
private: //see comment below about private vs. public
   double a, b, c;

public: //see comment below about private vs. public
   Triangle(double side1, double side2, double side3);// this is a constructor
   string getClass(); // e.g., "equilateral", "isosceles", "scalene"
};

#endif
