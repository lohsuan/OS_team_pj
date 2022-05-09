all: main

.PHONY: exec clean

main: ./VirtualMemoryManager.c
	gcc VirtualMemoryManager.c -o main
	
exec: 
	./main addresses.txt

clean:
	rm ./main