echo off

cd RoboGrader
python robochecker.py Sixdegrees ../
cd ../Sixdegrees

make clean
del test-output.txt
cd ..