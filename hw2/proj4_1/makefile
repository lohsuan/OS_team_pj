all: main

.PHONY: exec clean

main: ./SudokuValidator.c
	gcc SudokuValidator.c -lpthread -lm -o main

valid: 
	./main valid

invalid: 
	./main invalid

clean:
	rm ./main