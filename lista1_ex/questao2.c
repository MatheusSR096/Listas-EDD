#include <stdio.h>

typedef struct estrutura{
	double x;
	int y;
	char z;
}Estrutura;

typedef union uniao{
	double x;
	int y;
	char z;
}Uniao;
	

int main(){
	
	printf("Tamanho da estrutura = %ld\n", sizeof(Estrutura));
	printf("Tamanho da união     = %ld\n", sizeof(Uniao));
	
	return 0;
}
