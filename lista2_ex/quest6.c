/* 5. Implemente em C um simulador de escalonador de tarefas baseado em prioridade. A lista 
principal deve ser ordenada e ter nós com os seguintes campos:
 1. Prioridade original
2. Prioridade relativa (inicialmente igual à original, mas ordenada onde o menor valor 
tem maior prioridade).
 Cada nó da lista principal deve conter uma lista circular com os campos:
 1. Prioridade original
 2. Prioridade relativa (ordenada como na lista principal)
 3. Nome da tarefa (string de até 50 caracteres).
 Regras de escalonamento:
 1. Escolha o item com maior prioridade relativa na lista principal.
 2. Escolha o item com maior prioridade relativa na lista circular (essa é a tarefa 
escolhida).
 3. A prioridade relativa da tarefa escolhida deve ser incrementada para dar oportunidade 
às tarefas de menor prioridade.
 4. Se a tarefa escolhida for a última da fila, sua prioridade relativa deve igualar a 
prioridade original*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50  // Define o tamanho máximo do nome da tarefa

// Estrutura para cada tarefa na lista circular
typedef struct Tarefa {
    int prioridadeOriginal;    // Prioridade original da tarefa
    int prioridadeRelativa;    // Prioridade relativa da tarefa
    char nome[MAX_NAME_LEN];   // Nome da tarefa
    struct Tarefa* prox;       // Ponteiro para a próxima tarefa (lista circular)
} Tarefa;

// Estrutura para a lista principal
typedef struct ListaPrincipal {
    int prioridadeOriginal;    // Prioridade original do nó da lista principal
    int prioridadeRelativa;    // Prioridade relativa do nó da lista principal
    Tarefa* listaCircular;     // Ponteiro para a lista circular de tarefas
    struct ListaPrincipal* prox; // Ponteiro para o próximo nó da lista principal
} ListaPrincipal;

// Função para criar uma nova tarefa
Tarefa* criarTarefa(int prioridadeOriginal, const char* nome) {
    Tarefa* nova = (Tarefa*)malloc(sizeof(Tarefa)); // Aloca memória para uma nova tarefa
    nova->prioridadeOriginal = prioridadeOriginal;  // Define a prioridade original
    nova->prioridadeRelativa = prioridadeOriginal;  // Inicialmente a prioridade relativa é igual à original
    strncpy(nova->nome, nome, MAX_NAME_LEN);        // Copia o nome da tarefa para o campo 'nome'
    nova->nome[MAX_NAME_LEN - 1] = '\0';            // Garante a terminação nula do nome
    nova->prox = nova;                              // Como é uma lista circular, a próxima tarefa é ela mesma
    return nova;                                    // Retorna a tarefa criada
}

// Função para adicionar uma tarefa na lista circular ordenada por prioridade relativa
void adicionarTarefaOrdenada(Tarefa** lista, Tarefa* nova) {
    if (*lista == NULL) {
        *lista = nova;  // Se a lista estiver vazia, a nova tarefa é a primeira
        nova->prox = nova;  // Lista circular, aponta para ela mesma
        return;
    }

    Tarefa* atual = *lista;
    Tarefa* anterior = NULL;
    do {
        // Se a prioridade relativa do nó atual for maior que a da nova tarefa, insere antes
        if (atual->prioridadeRelativa > nova->prioridadeRelativa) break;
        anterior = atual;  // Mover para o próximo nó
        atual = atual->prox;
    } while (atual != *lista);  // Enquanto não voltar ao primeiro nó da lista

    nova->prox = atual;  // A nova tarefa aponta para o nó atual
    if (anterior) {
        anterior->prox = nova;  // Se encontrou um nó anterior, o anterior aponta para a nova tarefa
    } else {
        *lista = nova;  // Caso contrário, a nova tarefa é a primeira
    }

    // Garantir que a lista continue circular
    Tarefa* ultimo = *lista;
    while (ultimo->prox != atual) {
        ultimo = ultimo->prox;  // Encontrar o último nó da lista
    }
    ultimo->prox = *lista;  // Último nó aponta para o primeiro
}

// Função para criar um nó da lista principal
ListaPrincipal* criarListaPrincipal(int prioridadeOriginal) {
    ListaPrincipal* nova = (ListaPrincipal*)malloc(sizeof(ListaPrincipal));  // Aloca memória para a lista principal
    nova->prioridadeOriginal = prioridadeOriginal;  // Define a prioridade original
    nova->prioridadeRelativa = prioridadeOriginal;  // Inicialmente, a prioridade relativa é igual à original
    nova->listaCircular = NULL;  // Inicializa a lista circular como vazia
    nova->prox = NULL;  // Não há próximo nó no momento
    return nova;  // Retorna o nó da lista principal criado
}

// Função para adicionar um nó à lista principal ordenada por prioridade relativa
void adicionarListaPrincipalOrdenada(ListaPrincipal** lista, ListaPrincipal* nova) {
    if (*lista == NULL || (*lista)->prioridadeRelativa > nova->prioridadeRelativa) {
        nova->prox = *lista;  // Adiciona na frente da lista se estiver vazia ou se a prioridade for menor
        *lista = nova;  // A lista principal agora começa com a nova tarefa
        return;
    }

    ListaPrincipal* atual = *lista;
    while (atual->prox && atual->prox->prioridadeRelativa <= nova->prioridadeRelativa) {
        atual = atual->prox;  // Encontra a posição correta para inserir a nova tarefa
    }

    nova->prox = atual->prox;  // Aponta o novo nó para o próximo
    atual->prox = nova;  // Insere o novo nó na lista
}

// Função para executar o escalonamento
void executarEscalonamento(ListaPrincipal* lista) {
    if (!lista) {
        printf("Nenhuma tarefa para escalonar.\n");
        return;
    }

    // Escolher o nó com maior prioridade relativa na lista principal
    ListaPrincipal* maiorPrioridade = lista;  // Assume-se que a lista já esteja ordenada

    // Escolher a tarefa com maior prioridade relativa na lista circular
    Tarefa* tarefaEscolhida = maiorPrioridade->listaCircular;
    Tarefa* atual = tarefaEscolhida->prox;
    while (atual != maiorPrioridade->listaCircular) {
        // Encontrar a tarefa com a menor prioridade relativa (maior prioridade)
        if (atual->prioridadeRelativa < tarefaEscolhida->prioridadeRelativa) {
            tarefaEscolhida = atual;
        }
        atual = atual->prox;
    }

    // Exibe a tarefa escolhida
    printf("Tarefa escolhida: %s (Prioridade: %d)\n",
           tarefaEscolhida->nome, tarefaEscolhida->prioridadeRelativa);

    // Incrementar a prioridade relativa da tarefa escolhida
    tarefaEscolhida->prioridadeRelativa++;

    // Se a tarefa for a última da fila, sua prioridade relativa volta à original
    if (tarefaEscolhida->prox == maiorPrioridade->listaCircular) {
        tarefaEscolhida->prioridadeRelativa = tarefaEscolhida->prioridadeOriginal;
    }
}

// Função para liberar memória da lista circular
void liberarListaCircular(Tarefa* lista) {
    if (!lista) return;

    Tarefa* atual = lista;
    do {
        Tarefa* temp = atual;
        atual = atual->prox;  // Avança para o próximo nó
        free(temp);  // Libera o nó atual
    } while (atual != lista);  // Quando voltar ao início, encerra
}

// Função para liberar memória da lista principal
void liberarListaPrincipal(ListaPrincipal* lista) {
    while (lista) {
        ListaPrincipal* temp = lista;
        liberarListaCircular(lista->listaCircular);  // Libera a lista circular associada
        lista = lista->prox;  // Avança para o próximo nó
        free(temp);  // Libera o nó atual da lista principal
    }
}

// Função principal
int main() {
    ListaPrincipal* listaPrincipal = NULL;

    // Criar nós da lista principal
    ListaPrincipal* lp1 = criarListaPrincipal(1);
    adicionarListaPrincipalOrdenada(&listaPrincipal, lp1);

    ListaPrincipal* lp2 = criarListaPrincipal(2);
    adicionarListaPrincipalOrdenada(&listaPrincipal, lp2);

    // Adicionar tarefas às listas circulares
    adicionarTarefaOrdenada(&lp1->listaCircular, criarTarefa(1, "Tarefa A"));
    adicionarTarefaOrdenada(&lp1->listaCircular, criarTarefa(2, "Tarefa B"));

    adicionarTarefaOrdenada(&lp2->listaCircular, criarTarefa(1, "Tarefa C"));
    adicionarTarefaOrdenada(&lp2->listaCircular, criarTarefa(2, "Tarefa D"));

    // Executar escalonamento
    executarEscalonamento(listaPrincipal);

    // Limpar memória
    liberarListaPrincipal(listaPrincipal);
    return 0;
}
