# Programming project for Chap. 9

## Designing a Virtual Memory Manager
- A program that **translates logical to physical addresses for a virtual address** space of size 2^16=65,536 bytes.
- The program should read from a file, addresses.txt, containing logical addresses and, using a TLB as well as a page table, will translate each logical address to its corresponding physical address and output the value of the byte stored at the translated physical address.
- The program should implement demand paging. The backing store is represented by the file BACKING_STORE.bin, a binary file of size 65,536 bytes

### How to Run
1. open terminal in this directory
1. enter `make` to compile
1. enter `make exec` or `./main addresses.txt` to execute
1. enter `make clean` to clean up (optional)