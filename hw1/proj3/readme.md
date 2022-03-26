# Ch3 Programming Project 2

Linux Kernel Modules for Listing Tasks.

## Execute
1. open terminal in ch3_proj_2
2. enter `make`

## Part 1 iterates over the tasks linearly

### Insert ListTaskLinear module
3. enter `sudo insmod ListTasksLinear.ko`

### Remove ListTaskLinear module
4. enter `sudo rmmod ListTasksLinear`

### View kernel log buffer
5. enter `dmesg`
6. If you want to clear the kernel buffer, run `sudo dmesg -c`

## Part 2 iterates over the tasks with DFS

### Insert ListTaskDFS module
3. enter `sudo insmod ListTasksDFS.ko`

### Remove ListTaskDFS module
4. enter `sudo rmmod ListTasksDFS`

### View kernel log buffer
5. enter `dmesg`
6. If you want to clear the kernel buffer, run `sudo dmesg -c`
