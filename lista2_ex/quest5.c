#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int dados;
    char bitR; // 0 ou 1
    struct No* prox;
} No;

// Funções auxiliares para criar, inserir e listar nós
void inserir(No** lista, int dados, char bitR);
void listar(No* lista);
No* buscarCandidato(No** lista);
void moverParaFim(No** lista, No* no);
void trocar(No** listaPrimaria, No** listaSecundaria);

int main() {
    system("chcp 65001 > nul"); //configura o terminal para UTF-8
    No* listaPrimaria = NULL;
    No* listaSecundaria = NULL;

    // Inserindo valores nas listas primária e secundária
    inserir(&listaPrimaria, 10, 0);
    inserir(&listaPrimaria, 20, 1);
    inserir(&listaPrimaria, 30, 0);
    inserir(&listaSecundaria, 40, 1);
    inserir(&listaSecundaria, 50, 0);

    printf("Lista Primária antes da troca:\n");
    listar(listaPrimaria);

    printf("Lista Secundária antes da troca:\n");
    listar(listaSecundaria);

    trocar(&listaPrimaria, &listaSecundaria);

    printf("Lista Primária após a troca:\n");
    listar(listaPrimaria);

    printf("Lista Secundária após a troca:\n");
    listar(listaSecundaria);

    return 0;
}

// Função para inserir nós na lista
void inserir(No** lista, int dados, char bitR) {
    // Aloca memória para um novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) { 
        printf("Erro ao alocar memória.\n"); 
        exit(1); // Encerra o programa em caso de falha na alocação
    }

    // Inicializa o novo nó com os dados e o bitR fornecidos
    novoNo->dados = dados; 
    novoNo->bitR = bitR;

    if (*lista == NULL) { // Se a lista está vazia
        // Faz o novo nó apontar para ele mesmo (circularidade)
        novoNo->prox = novoNo; 
        *lista = novoNo; // Atualiza a lista para apontar para o novo nó
    } else { 
        No* atual = *lista;
        // Encontra o último nó da lista
        while (atual->prox != *lista) {
            atual = atual->prox;
        }
        // Insere o novo nó no final e mantém a circularidade
        atual->prox = novoNo; 
        novoNo->prox = *lista;
    }
}


// Função para listar os elementos de uma lista
void listar(No* lista) {
    if (!lista) { // Verifica se a lista está vazia
        printf("Lista vazia.\n");
        return;
    }

    No* atual = lista;
    do {
        // Imprime os dados e o valor do bitR do nó atual
        printf("(%d, %d) -> ", atual->dados, atual->bitR); 
        atual = atual->prox; // Avança para o próximo nó
    } while (atual != lista); // Continua até retornar ao início
    printf("\n"); // Nova linha após imprimir a lista
}

// Função para buscar um nó candidato na lista primária
No* buscarCandidato(No** lista) {
    No* atual = *lista; // Inicia a busca a partir do início da lista
    do {
        if (atual->bitR == 0) { 
            // Retorna o nó atual se o bitR for 0
            return atual;
        }
        // Move o nó com bitR = 1 para o final da lista
        moverParaFim(lista, atual); 
        atual = *lista; // Reinicia a busca a partir do início da lista
    } while (atual != *lista); // Continua enquanto não completa um ciclo
    return NULL; // Retorna NULL se nenhum nó com bitR = 0 for encontrado
}


// Função para mover um nó para o final da lista e ajustar bitR para 0
void moverParaFim(No** lista, No* no) {
    if (!no || !*lista || no->prox == no) return; // Se a lista está vazia ou tem um único nó, retorna

    No* anterior = NULL; // Para armazenar o nó anterior ao nó atual
    No* atual = *lista; 
    do {
        if (atual == no) break; // Encontra o nó a ser movido
        anterior = atual; // Atualiza o nó anterior
        atual = atual->prox; // Avança para o próximo nó
    } while (atual != *lista);

    if (anterior) { 
        // Remove o nó atual da sua posição original
        anterior->prox = atual->prox; 
        // Coloca o nó no final da lista, antes do início
        atual->prox = *lista; 
        (*lista)->prox = atual; 
        atual->bitR = 0; // Ajusta bitR para 0
    }
}


// Função para realizar a troca entre as listas
void trocar(No** listaPrimaria, No** listaSecundaria) {
    if (!*listaPrimaria || !*listaSecundaria) { // Verifica se alguma lista está vazia
        printf("Uma das listas está vazia. Não é possível realizar a troca.\n");
        return;
    }

    // Busca um nó candidato com bitR = 0 na lista primária
    No* candidatoPrimaria = buscarCandidato(listaPrimaria);
    if (!candidatoPrimaria) { // Se nenhum candidato for encontrado
        printf("Nenhum nó com bitR = 0 encontrado na lista primária.\n");
        return;
    }

    // Seleciona o nó no início da lista secundária como candidato
    No* candidatoSecundaria = *listaSecundaria;

    // Ajusta os ponteiros para remover o nó da lista primária
    No* anteriorPrimaria = NULL; 
    No* atualPrimaria = *listaPrimaria;
    do {
        if (atualPrimaria == candidatoPrimaria) break; // Encontra o nó candidato
        anteriorPrimaria = atualPrimaria; 
        atualPrimaria = atualPrimaria->prox;
    } while (atualPrimaria != *listaPrimaria);

    if (anteriorPrimaria) { 
        anteriorPrimaria->prox = candidatoPrimaria->prox; // Remove o nó da lista
    }
    if (candidatoPrimaria == *listaPrimaria) { 
        *listaPrimaria = candidatoPrimaria->prox; // Atualiza o início da lista, se necessário
    }

    // Ajusta os ponteiros para remover o nó da lista secundária
    No* anteriorSecundaria = NULL;
    No* atualSecundaria = *listaSecundaria;
    do {
        if (atualSecundaria == candidatoSecundaria) break; 
        anteriorSecundaria = atualSecundaria;
        atualSecundaria = atualSecundaria->prox;
    } while (atualSecundaria != *listaSecundaria);

    if (anteriorSecundaria) {
        anteriorSecundaria->prox = candidatoSecundaria->prox; 
    }
    if (candidatoSecundaria == *listaSecundaria) { 
        *listaSecundaria = candidatoSecundaria->prox; 
    }

    // Troca os nós entre as listas
    candidatoPrimaria->prox = *listaSecundaria; 
    *listaSecundaria = candidatoPrimaria; 

    candidatoSecundaria->prox = *listaPrimaria; 
    *listaPrimaria = candidatoSecundaria; 

    // Ajusta o bitR conforme necessário
    candidatoPrimaria->bitR = 1; 
    candidatoSecundaria->bitR = 0; 

    printf("Troca realizada com sucesso!\n"); // Mensagem de sucesso
}
