#include <stdio.h>
#include <memory.h>

int main(){
	char vetor[100];
	int j;
	
	memset(vetor, 0, 100);
	for(int i=1; i<=50; i++){
		printf("Digite um número %d: ", i);
		scanf("%d", &j);
		if(j < 100 && j >= 0 && vetor[j] != 'X') vetor[j] = 'X';
		else i--;
	}
	printf("Aposta espelho!!\n");
	for(int i=0;i<100;i++) if(vetor[i] != 'X') printf("%d ",i);
	printf("\n");
}
