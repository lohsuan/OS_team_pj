all: main

.PHONY: exec clean

main: ./SudokuValidator.c
	gcc SudokuValidator.c -lpthread -lm -o main

exec: 
	./main

clean:
	rm ./main