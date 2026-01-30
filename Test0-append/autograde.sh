# script to automatically grade the LinkedList test.
# This script is available to students.
#
# C. Seshadhri, Jan 2020

cd RoboGrader
cp Rubric/Tests/simple* ../LinkedList

#python robochecker.py LinkedList ../
#cd ../LinkedList
#make clean
#cd ../RoboGrader

echo -e "\nRunning RoboGrader on LinkedList assignment...\n"

python robograder.py -e LinkedList .. # simple running robograder

cat ../LinkedList/LinkedList.log

cd ../LinkedList
make clean

rm  *.txt
rm -f LinkedList.log

cd .. # return to main directory