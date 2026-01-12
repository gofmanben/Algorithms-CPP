
#include <iostream>
#include <fstream>
#include "triangle.h"

using namespace std;

int main(int argc, char** argv)
{
   if (argc < 3) // must provide two arguments as input
   {
       cerr << "Usage: ./main <INPUT FILE> <OUTPUT FILE>" << endl;
       return 1;  // non-zero return means error
   }
   ifstream infile(argv[1]);  // open input file
   ofstream outfile(argv[2]); // open output file

   double x, y, z;

   while (infile >> x >> y >> z) {
       Triangle t(x, y, z);
       cout << x << ','  << y << ',' << z << " = " << t.getClass() << endl; // ADDED: Output to display
       outfile << t.getClass() << "\n" << flush;
   }
   infile.close(); outfile.close(); //close input and output streams
   return 0;
}