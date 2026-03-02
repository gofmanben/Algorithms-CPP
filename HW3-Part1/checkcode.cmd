echo off

cd RoboGrader
python robochecker.py Wordrange ../
cd ../Wordrange

make clean
del test-output.txt
cd ..