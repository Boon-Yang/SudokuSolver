
sudoku: sudoku.o main.o
	g++ -g sudoku.o main.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -Wall -g -c main.cpp -o main.o

sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -g -c sudoku.cpp -o sudoku.o

clean:
	rm -f *.o execute
