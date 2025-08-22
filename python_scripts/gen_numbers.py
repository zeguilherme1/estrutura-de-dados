import math
import numpy as np
import random



# tô presumindo que o lucas espera que o input já esteja ordenado

def bubble(a):
    for i in range(0, len(a) - 1):
        for j in range(0, len(a) - i - 1):
            if(a[j] > a[j + 1]):
                temp = a[j]
                a[j] = a[j + 1]
                a[j + 1] = temp

array = []
def main():
    for i in range(0, 10):
        random_int = random.randint(1, 100)
        array.append(random_int)

    bubble(array)
    for i in range(0, 10):
        print(array[i], end=" ")

if __name__ == "__main__":
    main()