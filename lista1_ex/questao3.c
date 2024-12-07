#include <stdio.h>

#define MAXIMO 11

int main(){
	int vetor[MAXIMO];

	for(int i=0;i<MAXIMO;i++){
		printf("Digite um número : ");
		scanf("%d", &vetor[i]);
	}
	
	printf("Valor inicial : %d\n", vetor[0]);
	printf("Valor Final : %d\n", vetor[MAXIMO-1]);
	printf("Mediana     :  %d\n", vetor[MAXIMO/2]);
	
	return 0;
}
