#include <stdio.h>

int main(){
	int num;
	int *pnum; 
	
	printf("Digite um número : ");
	scanf("%d", &num);
	pnum = &num;
	printf("Valor do endereço apontado por pnum : %d\n", *pnum);
	printf("Endereço apontado por pnum : %p\n", pnum);
	printf("Endereço de pnum : %p\n", &pnum);
	
	return 0;
}
