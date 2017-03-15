This is the source folder for the satsolver.

The folder contains an executable binary (satsolver). To recompile, you may need to delete/replace the existing binary. 

Compile instructions:

1. From this location, compile it as:
	g++-4.8 -std=c++11 -Wall -Wextra -O3 main.cpp -o satsolver

2. To run the newly compiled or previously present binary, run it as:
	./satsolver <dimacs_filename>


