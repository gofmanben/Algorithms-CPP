echo off

cd RoboGrader
python robochecker.py Triangle-Classifier ../
cd ../Triangle-Classifier

make clean
del test-output1.txt
cd ..