import math
import numpy as np
import random
import matplotlib.pyplot as plt

tamanhos = [10, 100, 1000, 5000]
tempos = [1,2,3,4]

def main():
    plt.figure(figsize=(8, 5))
    plt.plot(tamanhos, tempos, marker="o", linestyle="-", linewidth=2)
    plt.xlabel("Tamanho do input (n)")
    plt.ylabel("Tempo de execução (s)")
    plt.title("Tempo de execução vs Tamanho do input")
    plt.grid(True)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()