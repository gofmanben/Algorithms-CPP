echo off

cd RoboGrader
python robochecker.py StackRecursion ../
cd ../StackRecursion

make clean
del student-output.txt
cd ..