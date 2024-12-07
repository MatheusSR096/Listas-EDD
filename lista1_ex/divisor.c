#include "divisor.h"
#include <stdio.h>

void (*funcao)(float resultado);

void carregafuncao(void (*funcaoresposta)(float resultado)){
	funcao = funcaoresposta;
}

void dividir(float dividendo, float divisor){
	if(funcao!=NULL){
		funcao(dividendo/divisor);
	}else{
		printf("%f\n", dividendo/divisor);
	}
}
