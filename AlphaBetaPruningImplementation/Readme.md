Alpha Beta Pruning

This repository contains the source code for a program that allows you to design a tree of your choice and run an algorithm to determine the best choice. The program is compiled into one executable file, a.out.

Compiling
To compile the program, run the following command:
make
This will compile the program into one executable file, a.out.

Running Tests
To run all the test files, make sure that runTests is already modded by using the following command:
chmod +x runTests
Then, run the tests using the following command:
./runTests a.out Project_tests/
The tests are defined below to ensure that the algorithm is still working if changes are made.

Project Name
This repository contains the source code for a program that allows you to design a tree of your choice and run an algorithm to determine the best choice. The program is compiled into one executable file, a.out.

Compiling
To compile the program, run the following command:

make

This will compile the program into one executable file, a.out.

Running Tests
To run all the test files, make sure that runTests is already modded by using the following command:

chmod +x runTests
Then, run the tests using the following command:

./runTests a.out Project_tests/
The tests are defined below to ensure that the algorithm is still working if changes are made.

Tests
The following tests are included in the project:

t00: Used to test an empty tree along with any commands to define, create, and set the tree.
t01-t03: Used to test the basic setup, generation, and running the algorithms on the inputted tree.
t04: Used to test the possibilities of a tree being entirely negative.
t05: Used to test a mixture of negative and positive values.
t06: Builds upon t03 by also checking to see if the print property works correctly.
t07: Builds upon t02 by checking to see if the change node works properly.
t08: Builds upon t02 by checking to see if deleting the branch works correctly.
t09: Builds upon t02 by checking to see if deleting a leaf node works correctly.
t10: Builds upon t02 by checking to see if inserting the branch works correctly.
t11: Builds upon t02 by checking to see if inserting a leaf works correctly.
t12: A combined test.

Improvements
The following improvements can be made to the program:

Clean up the code so that it is more space and time-efficient.
Add an option to load a file to import a tree or save the current tree to a local file.
Design the algorithm to work with parallels or a more efficient version of the algorithm.

Feedback
We received feedback to write an application section to the report of the algorithm to detail how the algorithm is used in modern-day. This was addressed by adding in a section to the report detailing the history of the algorithm.