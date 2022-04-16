all: main

.PHONY: exec clean

main: ./main.c
	gcc main.c -lpthread -lm -o main

exec: 
	./main

clean:
	rm ./main