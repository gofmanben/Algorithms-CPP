echo off

cd RoboGrader
python robochecker.py LinkedList ../
cd ../LinkedList

make clean
del student-output.txt
cd ..