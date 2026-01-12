# HW0: Getting Started — Codio, C++ Basics, and HW Expectations


- All code must be written in C or C++. Trying C++ is encouraged in this simple assignment.
- Please always be careful about using built-in libraries or data structures. The
assignment instructions will tell you what is acceptable, and what is not. If
  you have any doubts, please ask the instructors or TAs.

## 1. Problem Description

### Main objective
This assignment is quite simple and actually not related to any data structures. All you have to do is to write a program that 
reads a bunch of triangles from a file and classifies them as equilateral, isosceles or scalene.

The purpose of this practice assignment is to familiarize you with the structure of homeworks in this course. In particular:
1. In HWs, you shall develop the **entire program from scratch** (in tests, we give you most of the code and ask you to just implement one functionality but Homeworks are from scratch)
2. In HWs, you shall handle **input and output** yourself (in tests, we do it for you but in Homeworks you should handle it yourself. )
3. In HWs, you shall include a **README file with the correct name and extension** (no need for a README in tests).  
4. In HWs, you shall **test your code thoroughly** by thinking about **all possible edge cases and exceptions**. We give you a few simple test cases in the form of input, gold-output files but those are **not enough**. When we grade your code, **we test it with additional test cases**. (Same thing for tests)


### Setup

Everyone gets their own copy of the assignment inside their own Codio unit (also called a Codio box).
There is an assignment directory (For this one, it is called `Triangle-Classifier`). You **must write all your code in that directory**. 
There are also some **example input/ideal output files** inside this folder. Please don't modify them.


### Format and Output

You **should always provide a Makefile**. On running make, it should create an executable “main”. 
You should run the executable with **two command line arguments: the first is an input file, the second is the output file**. 
You **must provide a README (with NO EXTENSION) that contains a short explanation of the usage and a description of the files involved**. 
All your files must be of the form *.c, *.cpp, or *.h. When we grade, all other code files will be deleted. (So do not try to script some part in another language.)

Each line of the input file should/will consist of 3 numbers (sides of triangle), separated by space. 
You may get numbers that cannot possibly make a valid triangle (e.g., if one side is zero, or if one of the sides equals to the sum of the other two sides, etc.)
**so your code must be prepared to handle such cases.**

The output line corresponding to each input line (triangle sides) should be the type of the the triangle:
"invalid", "equilateral", "isosceles", "scalene". For example, if the input file is:
3 3 3
3 4 5
5 5 3

The output file should be:

equilateral
scalene
isosceles


### Data Structure Instructions
For this assignment you actually don't use any fancy data structure. 
To get familiar with C++, **we recommend** that you implement a **Triangle class** with a method called **getClass**. 
Please check **H0's worksheet** where we **provided the solution for this introductory HW**.

## 2. Grading
Your grade depends on how many of **OUR** test cases you pass. If you pass all, you get 100. Otherwise you get **partial credit** for each of **OUR** test that you pass.
Again, note that we test your code on **OUR** (hidden) test cases. **The one(s) we provide** you with are only **a fraction of our test cases**.

### README file
You **must provide a README** with a short explanation of the usage and a description of
the files involved.
Please note that the name of the README should be exactly like this (capital letters and no extensions) otherwise the autograder will exit.

## 3. Editing files in Codio
As I said earlier, the best method is through the terminal, using an editor like vi or vim. Alternately, you can click on a file in the left pane, and you will get a tab with the file. You can directly edit the file in that tab. While the editor is decent, sometimes changes you make do not immediately update the file in the actual container (stored on the cloud). (What you see in the editor tab is stored in your browser, which periodically syncs with the cloud.) To force an update, click on the small double arrow icon in the left pane, right above the file tree. That will force all updates. If you are editing your code through the tabs as described above, please click on that icon before you compile your code (just to be on the safe side).

## 4. More Codio Details

Codio is really cool! You get an easily configurable personal box that you have full control over. Feel free to play around with it. Some details from Codio below.

### GUI Applications and the Virtual Desktop
The Virtual Desktop allows you auto develop GUI based applications using any programming language. You can install a Virtual Desktop in your Box. You can then start the desktop and view it within the Codio IDE or in a new browser tab.

[Virtual Desktop documentation](https://www.codio.com/blog/virtual-machines)

### Command line access and the Terminal window
All Codio Boxes provide sudo level privileges to the underlying Ubuntu server. This means you can install and configure any component you like. You access the terminal from the Tools->Terminal menu item.

### Debugger
The Codio IDE comes with a powerful visual debugger. Currently we support Python, Java, C, C++ and NodeJS.

[Debugger documentation](https://docs.codio.com/common/develop/ide/debugger/create-debug-target.html#:~:text=Click%20the%20Tools%20tab%20on,Click%20Create%20Target.)