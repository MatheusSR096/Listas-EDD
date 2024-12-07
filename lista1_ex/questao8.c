#include "divisor.h"
#include <stdio.h>

void minhafuncao(float r){
	printf("O resultado encontrado foi : %.3f\n", r);
}

int main(){

	float n1, n2;
	
	n1=4.3;
	n2=2.0;
	
	carregafuncao(minhafuncao);
	
	dividir(n1,n2);
	
	return 0;
}

