#include <stdio.h>
#include <time.h>
#include "utils.h"

void reverse(int a[], int n){

	/*
		Reverse recursivo utilizando 2pointers;

		A técnica se baseia em inicializar um ponteiro no começo e no final do array, utilizando uma variável temporária
		para armazenar a primeira posição e conseguir efetuar a troca.
	*/

	int i = 0;
	int j = n - 1;

	while(i < j){
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
		i++;
		j--;
	}
}

void busca_sequencial(int a[], int n, int alvo){


	/*
		Busca sequencial em O(n)

		A busca sequencial se baseia em percorrer todo o Array com um único for, no pior caso precisamos percorrer todos
		os N elementos do array para encontrar nosso alvo.
	*/

	for(int i = 0; i < n; i++){
		if(a[i] == alvo){
			printf("Alvo encontrado no índice i = %d\n", i);
		
			return;
		}
	}

	printf("Alvo não encontrado!\n");
}

void bb_iterativa(int a[], int n, int alvo){

	/*
		Binary Search iterativa, complexidade O(log n);

		B
	*/

	int l = 0;
	int r = n - 1;
	while(l <= r){
		int m = l + (r - l) / 2;
		if(a[m] == alvo){
			printf("Alvo encontrado no índice i = %d\n", m);
			return;
		}

		if(a[m] < alvo){
			l = m + 1;
		}else{
			r = m - 1;
		}

	}
	printf("Alvo não encontrado\n");
}

void bb_recursiva(int a[], int l, int r, int alvo){


	/*

		Binary Search recursiva, complexidade também sendo O(log n);

	*/

    int m;
	if(l <= r){
		m = l + (r - l) / 2;

		if(a[m] == alvo){
			printf("Alvo encontrado no índice i = %d\n", m);
            return;
		}

		if(a[m] > alvo){
			return bb_recursiva(a, l, m - 1, alvo);

		}else{
		return bb_recursiva(a, m + 1, r, alvo);
		}
	}else{
        printf("Alvo não encontrado\n", m);
	    return;
    }
}



void print_vector(int a[], int n){

    /*
        Imprime nosso vetor
    */

    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

void copy_vector(int a[], int b[], int n){

    /*
        Armazena nosso vetor A em um vetor temporário B
    */
    
    for(int i = 0; i < n; i++){
        b[i] = a[i];
    }
}
