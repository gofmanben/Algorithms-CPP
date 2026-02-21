echo off

cd RoboGrader
python robochecker.py BST ../
cd ../BST

make clean
del student-output.txt
cd ..