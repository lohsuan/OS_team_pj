import threading
import time

numOfRes = 3
numOfPro = 5
finish = []
available = []
allocation = []
maximum = []
need = []
order = []

class MyThread(threading.Thread):
    def __init__(self, index, lock):
        threading.Thread.__init__(self)
        self.index = index
        self.lock = lock

    def run(self):
        while(finish[self.index] == False):
            isLessOrEqual = True
            for i in range(numOfRes):
                self.lock.acquire()
                string = "Comparing with the allocation of P" + str(self.index) + ", the available: "
                for i in range(numOfRes):
                    string = string + str(available[i]) + " "
                print(string)
                if need[self.index][i] > available[i]:
                    isLessOrEqual = False
                self.lock.release()
            if isLessOrEqual:
                self.lock.acquire()
                string = "\nAfter comparing with the allocation of P" + str(self.index) + ", the new available: "
                for i in range(numOfRes):
                    available[i] = available[i] + allocation[self.index][i]
                    string = string + str(available[i]) + " "
                print(string + "\n")
                order.append(self.index)
                self.lock.release()
                finish[self.index] = True

def main():
    threads = []
    lock = threading.Lock()
    numOfRes = int(input("Enter the number of resources: "))
    numOfPro = int(input("Enter the number of processes: "))
    for i in range(numOfPro):
        element = []
        temp = input("Enter the allocation of P" + str(i) + ": ")
        temp = temp.split()
        for j in range(numOfRes):
            element.append(int(temp[j]))
        allocation.append(element)

    for i in range(numOfPro):
        element = []
        temp = input("Enter the maximum of P" + str(i) + ": ")
        temp = temp.split()
        for j in range(numOfRes):
            element.append(int(temp[j]))
        maximum.append(element)

    temp = input("Enter the available: ")
    temp = temp.split()
    for i in range(numOfRes):
        available.append(int(temp[i]))

    for i in range(numOfPro):
        element = []
        finish.append(False)
        for j in range(numOfRes):
            element.append(maximum[i][j] - allocation[i][j])
        need.append(element)

    print("\nAllocation:")
    for i in range(numOfPro):
        print("P" + str(i), end = " ")
        for j in range(numOfRes):
            print(allocation[i][j], end = " ")
        print("")

    print("\nMaximum:")
    for i in range(numOfPro):
        print("P" + str(i), end = " ")
        for j in range(numOfRes):
            print(maximum[i][j], end = " ")
        print("")

    print("\nNeed:")
    for i in range(numOfPro):
        print("P" + str(i), end = " ")
        for j in range(numOfRes):
            print(need[i][j], end = " ")
        print("")

    print("\nAvailable: ", end = " ")
    for i in range(numOfRes):
        print(available[i], end = " ")
    print("\n")

    for i in range(numOfPro):
        threads.append(MyThread(i, lock))
        threads[i].start()

    for i in range(numOfPro):
        threads[i].join()

    print("The safe-state sequence:", end = " ")
    for x in order:
        print(x, end = " ")
    print("")

main()