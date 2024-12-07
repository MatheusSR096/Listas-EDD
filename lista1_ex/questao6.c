#include <stdio.h>

int main() {
    int num;
    float fnum;
    void *pnum;
    char op;

    num = 4;
    fnum = 4.5;
    op = 0;
    
    while (op != '1' && op != '2') {
        printf("Digite 1 para int e 2 para float: ");
        op = getchar();
        getchar();  // Limpa o caractere '\n' do buffer de entrada
    }

    if (op == '1'){
        pnum = (int*) &num;
    }
    else{ 
        pnum = (float*) &fnum;
    }
        
	printf("Endereço de num = %p\n", &num);
	printf("Endereço de fnum = %p\n", &fnum);
    printf("Endereço apontado por pnum = %p\n", pnum);
    printf("Endereço de pnum = %p\n", &pnum);

    return 0;
}
