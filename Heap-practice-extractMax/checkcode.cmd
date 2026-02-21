echo off

cd RoboGrader
python robochecker.py BinHeap ../
cd ../BinHeap

make clean
del student-output.txt
cd ..