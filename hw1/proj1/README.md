# Linux Kernel Modules

###### Programming project for Chap. 2

### Part I: Creating, loading, and removing kernel modules

#### What is this part doing?

- Create the kernel module and to load and unload the module.
- Be sure to check the counters of the kernel log buffer using `dmesg` to ensure we have properly followed the steps.

#### How to verify?

1. compile code
   ```shell
   make
   ```
2. insert the compiled module
   ```shell
   sudo insmod apple.ko
   ```
3. remove the module
   ```shell
   sudo rmmod apple
   ```
4. Check the kernel log for expected messages
   ```shell
   sudo dmesg
   ```

#### Screenshots
![](https://i.imgur.com/RlrT7dS.png)

---

### Part II: Creating, traversing, and deleting kernel data structures

#### What is this part doing?

- Given a structure named `birthday`:

```c
struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
}
```

- In the module entry point, create a linked list containing five `birthday` structure elements. Traverse the linked list and output its contents to the kernel log buffer. Invoke the `dmesg` command to ensure the list is properly constructed once the kernel module has been loaded.

- In the module exit point, delete the elements from the linked list and return the free memory back to the kernel. Again, invoke the `dmesg` command to check that the list has been removed once the kernel module has been unloaded.

#### How to verify?

1. compile code
   ```shell
   make
   ```
2. insert the compiled module
   ```shell
   sudo insmod banana.ko
   ```
3. remove the module
   ```shell
   sudo rmmod banana
   ```
4. Check the kernel log for expected messages
   ```shell
   sudo dmesg
   ```

#### Screenshots
![](https://i.imgur.com/hZM9sXU.png)
