/* Escreva um programa em C que implemente uma lista circular duplamente encadeada.
    1. Devem ser implementadas as funções de inserção, deleção e listagem da lista; 
    2. A lista deve ser ordenada por um campo de sua escolha;
    3. Deve oferecer duas opções de listagem: 
        1. Ordem crescente 
        2. Ordem decrescente*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int elemento;
    struct no *prox;
    struct no *ant;
} No;

void inserir(No **lista, int elemento);
void deletar(No **lista, int elemento);
void listarCrescente(No *lista);
void listarDecrescente(No *lista);
void liberarLista(No **lista);

int main() {
    No *lista = NULL; // Ponteiro para o início da lista
    int opcao, valor;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Listar em ordem crescente\n");
        printf("4. Listar em ordem decrescente\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir(&lista, valor);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                deletar(&lista, valor);
                break;
            case 3:
                listarCrescente(lista);
                break;
            case 4:
                listarDecrescente(lista);
                break;
            case 5:
                liberarLista(&lista);
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}

// Função para inserir Nó de forma ordenada
void inserir(No **lista, int elemento) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    novoNo->elemento = elemento;

    if (!*lista) {
        novoNo->prox = novoNo->ant = novoNo;
        *lista = novoNo;
        return;
    }

    No *atual = *lista;

    // Procurar posição para inserir
    do {
        if (atual->elemento >= elemento) {
            break;
        }
        atual = atual->prox;
    } while (atual != *lista);

    novoNo->prox = atual;       // O ponteiro prox do novoNo aponta para para o atual
    novoNo->ant = atual->ant;   // O ponteiro ant do novoNo aponta para o anterior 
    atual->ant->prox = novoNo;  // O ponteiro prox do anterior aponta para o novoNo
    atual->ant = novoNo;        // O ponteiro ant do atual aponta para o novoNo

    // adiciona no inicio da lista
    if (atual == *lista && elemento < atual->elemento) { // Se o atual for o inicio da lista e o elemento do novoNo for menor que o elemento do atual
        *lista = novoNo;    // O inicio da lista será o novoNo
    }
}

// Função para remover um nó
void deletar(No **lista, int elemento) {
    if (!*lista) { // Verifica se a lista está vazia
        printf("Lista vazia\n");
    }

    No *atual = *lista;
    do {
        if (atual->elemento == elemento) { // Se o elemento do atual for igual ao elemento a ser deletado
            if (atual->prox == atual) {  // Se o atual apontar para si memso
                free(atual);    // Libera a memoria do atual
                *lista = NULL;  // O inicio da lista agora é NULL
                printf("Elemento %d removido.\n", elemento);
            }

            atual->ant->prox = atual->prox; // O anterior vai apontar para o proximo do atual
            atual->prox->ant = atual->ant;  // O anterior do proximo vai apontar para o anterior do atual

            if (atual == *lista) { // Se o atual for igual ao inicio da lista
                *lista = atual->prox; // O inicio da lista será o proximo do atual
            }

            free(atual); // Libera a memoria do atual
            printf("Elemento %d removido.\n", elemento);
            return;
        }
        atual = atual->prox; // Atualiza o atual
    } while (atual != *lista);

    printf("Elemento %d não encontrado.\n", elemento);
}

// Função para listar em ordem crescente
void listarCrescente(No *lista) {
    if (!lista) {
        printf("Lista vazia.\n");
        return;
    }

    No *atual = lista;
    printf("Lista em ordem crescente: ");
    do {
        printf("%d -> ", atual->elemento);
        atual = atual->prox;
    } while (atual != lista);
    printf("\n");
}

// Função para listar em ordem decrescente
void listarDecrescente(No *lista) {
    if (!lista) {
        printf("Lista vazia.\n");
        return;
    }

    No *atual = lista->ant;
    printf("Lista em ordem decrescente: ");
    do {
        printf("%d <- ", atual->elemento);
        atual = atual->ant; // Inicio da lista apontando para o anterior
    } while (atual != lista->ant); // Enquanto atual for diferente do inicio da lista apontando para o anterior 
    printf("\n");
}

// Função para liberar a lista
void liberarLista(No **lista) {
    if (!*lista) return;

    No *atual = *lista;
    No *prox;
    do {
        prox = atual->prox;
        free(atual);
        atual = prox;
    } while (atual != *lista);

    *lista = NULL;
    printf("Memória liberada.\n");
}
