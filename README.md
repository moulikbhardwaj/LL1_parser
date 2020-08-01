# LL(1) Parser

## What does the project Do?
The project implements an LL(1) parser, using first and follow sets to generate the predictive parse table. Then the parser takes input string, and parse it using the parse table. The grammer that the parser handels is :  
```
E -> TE'  
E' -> +TE' | e                   
T -> FT'  
T' -> *FT' | e  
F -> id | (E)  
```
But, this can be changed in main.cpp, by changing the production.  
Note, empty string, i.e. `""` represents a null production, denoted by `epsilon` in some books.

The input string is kept in `input.txt` file, and can be changed as well.

## How to run
Type `make build` in terminal to build the project.
Type `make execute` to execute the file.
Type `make clean` to delete the binary.

## Authors
* __Moulik, Roll No. 185506__
* __Swayam Kaul, Roll No. 185512__
* __Rishabh Denkawat, Roll No. 185519__