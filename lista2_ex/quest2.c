/*2. Escreva um programa em C que permita a criação de uma lista duplamente encadeada 
utilizando alocação de memória dinâmica. Implemente as funções de inserção, deleção e 
exibição de itens da lista.*/

#include <stdio.h>
#include <stdlib.h>

// Definição de uma estrutura para representar um nó de uma lista duplamente encadeada
typedef struct no {
    int elemento;          // Valor armazenado no nó
    struct no* prox;       // Ponteiro para o próximo nó
    struct no* ant;        // Ponteiro para o nó anterior
} No;

void InserirInicio(No** lista, int elemento);
void InserirFinal(No** lista, int elemento);
void InserirMeio(No** lista, int elemento, int ref);
void imprimir(No* no);
void limparLista(No** lista);
No* remover(No** lista, int elemento);

int main() {
    int opcao, elemento, ant;
    No *removido, *lista = NULL;

    do {
        printf("\n\t0 - Sair\n\t1 - Inserir no início\n\t2 - Inserir no fim\n\t3 - Inserir no meio\n\t4 - Imprimir\n\t5 - remover elemento\n");
        printf("Informe sua escolha: ");
        scanf("%i", &opcao);

        switch (opcao) {
        case 1:
            printf("Digite um elemento: ");
            scanf("%i", &elemento);
            InserirInicio(&lista, elemento);
            break;
        case 2:
            printf("Digite um elemento: ");
            scanf("%i", &elemento);
            InserirFinal(&lista, elemento);
            break;
        case 3:
            printf("Digite um elemento e o valor de referência: ");
            scanf("%i %i", &elemento, &ant);
            InserirMeio(&lista, elemento, ant);
            break;
        case 4:
            imprimir(lista);
            break;
        case 5:
            printf("Informe o elemento a ser removido: ");
            scanf("%i", &elemento);
            removido = remover(&lista, elemento);
            if(removido){
                printf("elemento a ser removido: %i\n", removido->elemento);
                free(removido);
            } else {
                printf("Elemento inexistente!\n");
            }
            break;
        default:
            if (opcao != 0) {
                printf("Opção inválida!\n");
            }
        }
    } while (opcao != 0);

    limparLista(&lista);

    return 0;
}

// Função para inserir um elemento no início da lista
void InserirInicio(No** lista, int elemento) {
    // Aloca memória para um novo nó
    No* novoNo = malloc(sizeof(No));
    if (novoNo == NULL) { // Verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória");
        exit(1); // Encerra o programa em caso de falha
    }
    
    // Inicializa os campos do novo nó
    novoNo->elemento = elemento;  // Define o valor do nó
    novoNo->prox = *lista;        // O próximo nó do novo nó é o atual início da lista
    novoNo->ant = NULL;           // Como é o primeiro nó, não há nó anterior
    
    // Atualiza o nó anterior do nó atual, se existir
    if (*lista) {
        (*lista)->ant = novoNo;
    }
    *lista = novoNo; // Atualiza a cabeça da lista para apontar para o novo nó
}

// Função para inserir um elemento no final da lista
void InserirFinal(No** lista, int elemento) {
    // Ponteiros auxiliares para manipular a lista
    No *aux, *novoNo = malloc(sizeof(No));
    if (novoNo == NULL) { // Verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória.");
        exit(1); // Encerra o programa em caso de falha
    }

    // Inicializa o novo nó
    novoNo->elemento = elemento; // Define o valor do nó
    novoNo->prox = NULL;         // Como é o último nó, não há próximo nó

    if (*lista == NULL) { // Se a lista está vazia
        *lista = novoNo;  // O novo nó se torna o primeiro
        novoNo->ant = NULL; // Como é o único nó, não há nó anterior
    } else { // Caso contrário, percorre a lista até o final
        aux = *lista;
        while (aux->prox) { // Enquanto houver próximo nó, avança
            aux = aux->prox;
        }
        aux->prox = novoNo;  // O último nó atualiza seu próximo para o novo nó
        novoNo->ant = aux;   // O novo nó aponta para o nó anterior
    }
}

// Função para inserir um elemento após um nó de referência
void InserirMeio(No** lista, int elemento, int ref) {
    // Ponteiros auxiliares e alocação de memória para o novo nó
    No *aux, *novoNo = malloc(sizeof(No));
    if (novoNo == NULL) { // Verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória");
        exit(1); // Encerra o programa em caso de falha
    }

    novoNo->elemento = elemento; // Define o valor do novo nó

    // Se a lista estiver vazia, o novo nó será o único nó
    if (*lista == NULL) {
        novoNo->prox = NULL; // Como é o único nó, não há próximo
        novoNo->ant = NULL;  // Não há anterior
        *lista = novoNo;     // Atualiza a cabeça da lista
    } else { // Caso contrário, busca o nó de referência
        aux = *lista;
        while (aux->elemento != ref && aux->prox) { // Procura pelo nó de referência
            aux = aux->prox;
        }

        // Insere o novo nó na lista
        novoNo->prox = aux->prox; // O próximo do novo nó será o próximo do nó de referência
        if (aux->prox) { // Se o nó de referência não for o último
            aux->prox->ant = novoNo; // Atualiza o nó seguinte para apontar para o novo nó
        }
        aux->prox = novoNo; // Atualiza o próximo do nó de referência para o novo nó
        novoNo->ant = aux;  // Atualiza o nó anterior do novo nó para o nó de referência
    }
}

void imprimir(No* no){
    printf("Lista: ");
    printf("\n\nNULL -> ");
    while (no){
        printf("%i -> ", no->elemento);
        no = no->prox;
    }
    printf("NULL\n\n");
}  


// Função para remover um nó da lista, a ser implementada
No* remover(No** lista, int elemento) {
    No *aux = *lista, *remover = NULL;

    if (*lista == NULL) {
        printf("A lista está vazia. Nada a remover.\n");
        return NULL;
    }

    // Caso o elemento a ser removido seja o primeiro da lista
    if ((*lista)->elemento == elemento) {
        remover = *lista;
        *lista = remover->prox; // Atualiza o início da lista
        if (*lista) {
            (*lista)->ant = NULL; // Ajusta o ponteiro `ant` do novo primeiro nó
        }
        return remover; // Retorna o nó removido
    }

    // Caso contrário, percorre a lista para encontrar o elemento
    while (aux != NULL && aux->elemento != elemento) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Elemento %d não encontrado.\n", elemento);
        return NULL; // Elemento não encontrado
    }

    remover = aux; // O nó a ser removido é o atual

    // Atualiza os ponteiros para excluir o nó
    if (aux->prox) {
        aux->prox->ant = aux->ant; // Ajusta o `ant` do próximo nó
    }
    if (aux->ant) {
        aux->ant->prox = aux->prox; // Ajusta o `prox` do nó anterior
    }

    return remover; // Retorna o nó removido
}

void limparLista(No** lista){
    No* aux;
    while (*lista){
        aux = *lista;
        *lista = (*lista)->prox;
        free(aux);
    }
    printf("Memoria liberada!");
}