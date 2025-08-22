#include <stdio.h>
#include <time.h>
#include "utils.c"

// Declaração das variáveis globais utilizadas no código
int n, alvo, opcao;

// clock_t start, end são utilizadas para saber quando o algoritmo começa e termina
clock_t start, end;
double tempo;

int main(){


	printf("Insira o tamanho do vetor: \n");
	scanf("%d", &n);
	int a[n], b[n];
	 // Nessa implementação um vetor auxiliar b é utilizado como cópia do vetor original
	 // visto que sempre queremos nosso array ordenado de forma crescente para fazermos a binary search

	printf("Insira os %d elementos do vetor: \n", n);

	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}

		while(1){
		printf("\nInsira o algoritmo que deseja rodar:\n[1] Inverter o vetor\n[2] Busca Sequencial no vetor\n[3] Binary Search Iterativa\n[4] Binary Search Recursiva\n");
		scanf("%d", &opcao);
		switch(opcao){

			case 1:
				
				copy_vector(a, b, n); // Copiamos o vetor A para o B
				start = clock(); // Iniciamos o contador
				reverse(b, n); // Aplicamos nosso algoritmo
				end = clock(); // Encerrando o contador
				tempo = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculamos o tempo necessário
				print_vector(b, n); // Imprime o vetor
				printf("Tempo de execução do algoritmo: %.12f segundos", tempo); // Imprime o tempo necessário
				break;


			// A lógica nos comentários do primeiro caso se repete nos próximos
			case 2:
				printf("Insira o elemento que deseja buscar: \n");
				scanf("%d", &alvo);
				start = clock();
				busca_sequencial(a, n, alvo);
				end = clock();
				printf("Tempo de execução do algoritmo: %.12f segundos\n", tempo);
				break;

			case 3:
				printf("Insira o elemento que deseja buscar: \n");
				scanf("%d", &alvo);
				start = clock();
				bb_iterativa(a, n, alvo);
				end = clock();
				printf("Tempo de execução do algoritmo: %.12f segundos\n", tempo);
				break;

			case 4:
				printf("Insira o elemento que deseja buscar: \n");
				scanf("%d", &alvo);
				start = clock();
				bb_recursiva(a, 0, n - 1, alvo);
				end = clock();
				printf("Tempo de execução do algoritmo: %.12f segundos\n", tempo);
				break;

			default:
				printf("Insira uma opção correta!\n");
				break;
			}
		}

		return 0;
	}
