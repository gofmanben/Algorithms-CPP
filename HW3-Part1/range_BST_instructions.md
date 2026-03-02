### HW3-Part 1: Range Searching with BST

• All code must be written in C/C++.
• Please be careful about using built-in libraries or data structures. The assignment instructions will tell you what is acceptable, and what is not. If you have any doubts, please ask the instructors or TAs.

### 1. Problem description 

**Main objective:** We need to design a fast data structure to perform insertions and range queries on text. Basically, your input file will have a (long) list of words to insert, interspersed with range queries. The latter determines the number of words seen so far in a given range. For example, if the range is “ab” and “bc”, you have to find the number of words that are lexicographically between “ab” and “bc”.
You cannot use any built in data structures for storing the words and answering range queries. You can use libraries for I/O and string processing.

**This HW is divided into two parts**: 
- Part 1 (this Codio box) is really easy: you will implement a BST and a simple traversal algorithm and secure 50/100 points.
- Part 2 (AVL + efficient search) is hard. You have been forewarned! But you will learn **a lot** trying to get full credit. In part 2, you have to implement an AVL and an efficient range search algorithm.

Read this document carefully. Half the questions on Ed Discussion can be answered by just reading the instructions. Also, the algorithm for this assignment requires a fair bit of thought, so read my suggestions carefully.


Start with **Part 1 (half credit solution) and make sure it works**. It should not be too hard to get a correct (but ineﬃcient) solution building oﬀ my BST codes.
Then, if you’re in the mood for serious coding, continue to part 2 (In another Codio box: Range Searching with AVL).


**Setup:** You can access a Codio unit for this assignment. There is a directory “Wordrange” that contains a number of test input/output files, which shall be explained later. You must write all your code in that directory, and not in any subdirectory. There are also some testing scripts. Please check out the README for more details on that.

**Format and Output:** You should provide a Makefile. On running make, it should create an executable **"main"**. You should run the executable with two command line arguments: the first is an **input file**, the second is the **output file**. You must provide a **README** with an explanation of the usage and a description of the files involved. Please cite any sources you used, such as online code, code from a previous course (that you may have written), or extensive discussions with someone.
All your files must be of the form *.c, *.cpp, *.h, *.hpp. When we grade, all other code files will be deleted. (So do not try to script some part in another language.)
Each line of the input file will be of the following two forms:
```txt
i <STRING>
or
r <STRING1> <STRING2>
```
The first line above means insert the string into your data structure. If the string is already present, do not insert again. Each word should only appear once in the data structure.
The second line above means: count the number of strings (currently stored) that are lexicographically between STRING1 and STRING2. In other words, we want the number of all strings STR such that STRING1 ≤ STR ≤ STRING2, where comparison is lexicographic (in C++, this is just comparing by < or >).
This number, also called the **range size**, should be printed in the **output file**, in a separate line. You can assume that STRING1 < STRING2. For more clarity, **look at the small test input/output files.**

**Data structure instructions:** You cannot use inbuilt data structures in C++. (Actually, there probably isn’t an inbuilt data structure that solves this assignment.)
For **half credit**, you can simply store the words in a standard **BST**.
For **full credit** (part 2), you need to build a **self-balancing tree** that stores the words.
Note that you **do not need to implement deletions**, just insert, find, and range queries.

**How to do range queries?** (I’m glad you asked.) A naive method would be to simply traverse the tree and find all keys in the given range. This would be a **Θ(n)** algorithm, where n is the number of nodes in the tree. For **half credit, this is enough**.
For **full credit** (part 2), you need to process a **million such queries** (and n is at least a few hundred thousand), this is not feasible with BSTand a simple search algorithm. You will need a balanced tree and a more sophisticated search algorithm that doesn't spend time exploring irrelevant parts of the tree.


**The test cases:**
- simple-input.txt, simple-output.txt: This just inserts a few numbers, and is an excellent way to check if at least everything is working correctly.
I have also included larger test cases from part 2 (under Tests folder) so you can try them with the simple search + BST and see where it starts to struggle.

### 2. Grading
(50 points) If you pass only pass some tiny test cases. You could get these points by simply coding up a standard BST, and range searching by reading the entire tree.

To get full credit (100 points), proceed to part 2. To pass part 2's test cases, you code should terminate within 1 minute for any input file with at most three million operations.