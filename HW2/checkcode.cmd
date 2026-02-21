echo off

cd RoboGrader
python robochecker.py NQueens ../
cd ../NQueens

make clean
del test-output.txt
cd ..