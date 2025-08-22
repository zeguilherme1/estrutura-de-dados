#ifndef UTILS_H
#define UTILS_H
// reverses a int array
void reverse(int a[], int n);

// do a sequencial search in o(n)
void busca_sequencial(int a[], int n, int alvo);

// iterativa binary search

void bb_iterativa(int a[], int n, int alvo);

// recursive binary search

void bb_recursiva(int a[], int l, int r, int alvo);

void print_vector(int a[], int n);

void copy_vector(int a[], int b[], int n);

#endif