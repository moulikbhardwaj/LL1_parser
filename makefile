build: a.out

execute: a.out
	./a.out

a.out: main.cpp parseTable.h firstAndFollow.h
	g++ main.cpp

clean: 
	rm a.out