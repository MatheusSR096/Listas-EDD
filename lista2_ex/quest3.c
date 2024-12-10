/* 3. Implemente em C uma lista de tarefas ordenada por prioridade, um número inteiro entre 1 e 
1.000.000 definido no registro da tarefa. Cada tarefa também deve ter um campo indicando 
se está concluída (sim ou não).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tarefa {
    int prioridade;             // Prioridade da tarefa de 1 a 1M;
    char* descricao;            // Descrição da Tarefa (ponteiro para string alocada dinamicamente);
    int concluida;              // Indicador de conclusão;
    struct tarefa* prox;        // Ponteiro para próxima tarefa;
    struct tarefa* ant;         // Ponteiro para a tarefa anterior;
} Tarefa;

void InserirTarefa(Tarefa** lista, int prioridade, const char* descricao);
void listarConcluidas(Tarefa** lista);
void listarPendentes(Tarefa** lista);
void concluirTarefa(Tarefa** lista, int prioridade);
void liberarLista(Tarefa** lista);

int main() {
    Tarefa* lista = NULL;
    int opcao;
    int prioridade;
    char descricao[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir nova tarefa\n");
        printf("2. Listar tarefas concluídas\n");
        printf("3. Listar tarefas pendentes\n");
        printf("4. Concluir uma tarefa\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Informe a prioridade da tarefa (1 a 1.000.000): ");
                scanf("%d", &prioridade);
                getchar(); // Limpar o buffer de entrada

                printf("Informe a descrição da tarefa: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0'; // Remover o caractere de nova linha

                InserirTarefa(&lista, prioridade, descricao);
                break;
            case 2:
                listarConcluidas(&lista);
                break;
            case 3:
                listarPendentes(&lista);
                break;
            case 4:
                printf("Informe a prioridade da tarefa a ser concluída: ");
                scanf("%d", &prioridade);
                concluirTarefa(&lista, prioridade);
                break;
            case 5:
                liberarLista(&lista);
                return 0;
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}

// Função para adcionar uma nova tarefa
void InserirTarefa(Tarefa** lista, int prioridade, const char* descricao) {
    Tarefa* novaTarefa = (Tarefa*)malloc(sizeof(Tarefa));
    if (!novaTarefa) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    novaTarefa->prioridade = prioridade;
    novaTarefa->descricao = strdup(descricao); // Aloca e copia a descrição
    if (!novaTarefa->descricao) {
        printf("Erro ao alocar memória para descrição\n");
        free(novaTarefa);
        exit(1);
    }
    novaTarefa->concluida = 0; // Sempre inicia a nova Tarefa como pendente
    novaTarefa->prox = NULL;   // O nó para a proxima tarefa com NULL
    novaTarefa->ant = NULL;    // O nó para a tarefa anterior como NULL

    // Se a lista estiver vazia
    if (!*lista) {
        *lista = novaTarefa; // A nova tarefa vai ser o inicio da lista
    } else {
        Tarefa* atual = *lista;     // Inicializa atual como inicio da lista
        Tarefa* anterior = NULL;    // Inicializa anterior como NULL

        // Encontra a posição ordenada
        while (atual && atual->prioridade < prioridade) { // Enquanto a prioridade do nó atual for menor que a prioridade
            anterior = atual;   // O nó anterior será igual ao atual
            atual = atual->prox;    // O nó atual será igual ao proximo
        }
        if (!anterior) { // Insere no início
            novaTarefa->prox = *lista;      // A nova tarefa vai apontar para o inicio da lista
            (*lista)->ant = novaTarefa;     // O ponteiro anterior do inicio da lista vai apontar para a novas tarefa
            *lista = novaTarefa;            // O a nova tarefa agora é o inicio da lista
        } else if (!atual) { // Insere no final
            anterior->prox = novaTarefa;    // O ponteiro prox da tarefa anterior aponta para nova tarefa
            novaTarefa->ant = anterior;     // O ponteiro anterior da nova tarefa irá apontar para a tarefa anterior
        } else { // Insere no meio
            novaTarefa->prox = atual;       // O ponteiro prox da nova tarefa aponta para atual
            novaTarefa->ant = anterior;     // O ponteiro ant da nova tarefa aponta para anterior
            anterior->prox = novaTarefa;    // O ponteiro prox do anterior aponta para nova tarefa
            atual->ant = novaTarefa;        // O ponteiro ant da tarefa atual aponta para nova tarefa
        }
    }
    printf("Tarefa inserida com sucesso!\n");
}

// Função para listar tarefas concluidas
void listarConcluidas(Tarefa** lista) {
    Tarefa* atual = *lista;
    int encontrou = 0;

    while (atual) {
        if (atual->concluida) {
            printf("Prioridade: %d, Descrição: %s\n", atual->prioridade, atual->descricao);
            encontrou = 1;
        }
        atual = atual->prox;
    }

    if (!encontrou) {
        printf("Nenhuma tarefa concluída encontrada.\n");
    }
}

// Função para lisar tarefas pendentes
void listarPendentes(Tarefa** lista) {
    Tarefa* atual = *lista;
    int encontrou = 0;

    while (atual) {
        if (!atual->concluida) {
            printf("Prioridade: %d, Descrição: %s\n", atual->prioridade, atual->descricao);
            encontrou = 1;
        }
        atual = atual->prox;
    }

    if (!encontrou) {
        printf("Nenhuma tarefa pendente encontrada.\n");
    }
}

// Função para marcar tarefa como concluida
void concluirTarefa(Tarefa** lista, int prioridade) {
    Tarefa* atual = *lista;

    while (atual) {
        if (atual->prioridade == prioridade) { // Encontra a tarefa pela prioridade
            if (atual->concluida) {
                printf("A tarefa já está concluída.\n");
            } else {
                atual->concluida = 1; // Marca como concluída
                printf("Tarefa com prioridade %d marcada como concluída.\n", prioridade);
            }
            return;
        }
        atual = atual->prox; // Avança para a próxima tarefa
    }
    printf("Tarefa com prioridade %d não encontrada.\n", prioridade);
}

// Função para liberar memoria da lista
void liberarLista(Tarefa** lista) {
    Tarefa* atual = *lista;
    Tarefa* prox;

    while (atual) {
        prox = atual->prox;
        free(atual->descricao); // Libera a memória alocada para a descrição
        free(atual);            // Libera a memória da tarefa
        atual = prox;
    }
    *lista = NULL;
    printf("Memória liberada!\n");
}
