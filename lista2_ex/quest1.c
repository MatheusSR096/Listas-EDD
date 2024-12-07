#include <stdio.h>
#include <stdlib.h>


typedef struct no{
    int elemento;
    struct no* prox;
} No;


void inserirInicio(No** lista, int elemento);
void inserirFim(No** lista, int elemento);
void inserirMeio(No** lista, int elemento, int ant);
void imprimirLista(No* no);


int main(){
    int opcao, elemento, ant;
    No* lista = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - InserirI\n\t2 - inserirF\n\t3 - inserirM\n\t4 - Imprimir\n");
        printf("\nInforme sua escolha: ");
        scanf("%i", &opcao);


        switch (opcao)
        {
        case 1:
            printf("Digite um elemento: ");
            scanf("%i", &elemento);
            inserirInicio(&lista, elemento);
            break;
        case 2:
            printf("Digite um elemento: ");
            scanf("%i", &elemento);
            inserirFim(&lista, elemento);
            break;
        case 3:
            printf("Digite um elemento e o valor de referencia: ");
            scanf("%i %i", &elemento, &ant);
            inserirMeio(&lista, elemento, ant);
            break;
        case 4:
            imprimirLista(lista);
            break;
        default:
            if (opcao!=0){
                printf("Opção invalida!\n");
            }
        }
    }while(opcao!=0);
    return 0;
}


// Função para inserir um elemento no início da lista
void inserirInicio(No** lista, int elemento){
    No* novo_no = malloc(sizeof(No));


    if(novo_no==NULL){
        printf("Erro ao alocar memória");
        exit(1);
    }
    novo_no->elemento = elemento; // Atribui o valor do elemento ao novo nó
    novo_no->prox = *lista;       // Faz o novo nó apontar para o início atual da lista
    *lista = novo_no;             // Atualiza o ponteiro da lista para o novo nó
}


// Função para inserir um elemento no final da lista
void inserirFim(No** lista, int elemento){
    No *aux, *novo_no = malloc(sizeof(No));
    if(novo_no==NULL){
        printf("Erro ao alocar memória");
        exit(1);
    }
   novo_no->elemento = elemento; // Atribui o valor do elemento ao novo nó
    novo_no->prox = NULL;         // Define o próximo nó como NULL (final da lista)


    if (*lista == NULL) { // Verifica se a lista está vazia
        *lista = novo_no; // O novo nó será o primeiro elemento da lista
    } else {
        aux = *lista; // Inicializa um ponteiro auxiliar no início da lista


        while (aux->prox) { // Percorre a lista até encontrar o último nó
            aux = aux->prox;
        }


        aux->prox = novo_no; // Faz o último nó apontar para o novo nó
    }
}


void inserirMeio(No** lista, int elemento, int ant){
    No *aux, *novo_no=malloc(sizeof(No));


    if(novo_no==NULL){
        printf("Erro ao alocar memória");
    }
    novo_no->elemento = elemento; // Atribui o valor do elemento ao novo nó


    if (*lista == NULL) { // Verifica se a lista está vazia
        novo_no->prox = NULL; // Faz o próximo nó do novo elemento ser NULL
        *lista = novo_no;     // O novo nó será o primeiro elemento da lista
    } else {
        aux = *lista; // Inicializa um ponteiro auxiliar no início da lista


        // Percorre a lista até encontrar o valor de referência ou o final da lista
        while (aux->elemento != ant && aux->prox) {
            aux = aux->prox;
        }


        novo_no->prox = aux->prox; // Faz o novo nó apontar para o próximo nó do valor de referência
        aux->prox = novo_no;       // Faz o nó de referência apontar para o novo nó
    }
}


void imprimirLista(No* no){
    printf("\n\tLista:  ");
    while(no!=NULL){
        printf("%i -> ", no->elemento);
        no = no->prox;
    }
    printf("NULL\n\n");
}
