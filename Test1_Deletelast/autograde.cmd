echo off

cd RoboGrader
copy Rubric\Tests\simple* ..\LinkedList

REM python robochecker.py LinkedList ../
REM cd ../LinkedList
REM make clean
REM cd ../RoboGrader

echo.
echo Running RoboGrader on LinkedList assignment...
echo.

python robograder.py -e LinkedList ..

type ..\LinkedList\LinkedList.log

cd ../LinkedList
make clean

del *.txt
del LinkedList.log

cd ..