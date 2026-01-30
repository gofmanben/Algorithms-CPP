cp Bard/Tests/shakespeare-cleaned.txt Bard/shakespeare-cleaned.txt
cp Bard/Tests/simple-input.txt Bard/simple-input.txt
cp Bard/Tests/simple-output.txt Bard/simple-output.txt

cd RoboGrader
python robochecker.py Bard ../
cd ../Bard

make clean
rm shakespeare-cleaned.txt
rm simple-input.txt
rm simple-output.txt
rm test-output.txt
rm -f test-more-output.txt
rm -f test-shakespeare-output.txt
cd ..