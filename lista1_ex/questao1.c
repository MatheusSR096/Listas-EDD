#include <stdio.h>

int main(){

	printf("Tamanho dos tipos primitivos\n");
	printf("int = %ld bytes (%ld bits)\n", sizeof(int), sizeof(int)*8);
	printf("short int = %ld bytes (%ld bits)\n", sizeof(short int), sizeof(short int)*8);
	printf("long int = %ld bytes (%ld bits)\n", sizeof(long int), sizeof(long int)*8);
	printf("float = %ld bytes (%ld bits)\n", sizeof(float), sizeof(float)*8);
	printf("double = %ld bytes (%ld bits)\n", sizeof(double), sizeof(double)*8);
	printf("long double = %ld bytes (%ld bits)\n", sizeof(long double), sizeof(long double)*8);
	printf("char = %ld bytes (%ld bits)\n", sizeof(char), sizeof(char)*8);
}
