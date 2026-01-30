echo off

copy Bard\Tests\shakespeare-cleaned.txt Bard\shakespeare-cleaned.txt
copy Bard\Tests\simple-input.txt Bard\simple-input.txt
copy Bard\Tests\simple-output.txt Bard\simple-output.txt

cd RoboGrader
python robochecker.py Bard ../
cd ../Bard

make clean
del shakespeare-cleaned.txt
del simple-input.txt
del simple-output.txt
del test-output.txt
if exist test-more-output.txt del test-more-output.txt
if exist test-shakespeare-output.txt del test-shakespeare-output.txt
cd ..