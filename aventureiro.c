#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100 // Tamanho máximo da mochila (versão vetor)

// =============================
// ======= STRUCTS =============
// =============================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =============================
// ======= VARIÁVEIS GLOBAIS ===
// =============================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// =============================
// ======= FUNÇÕES VETOR =======
// =============================

// Inserir item no vetor
void inserirItemVetor(Item mochila[], int *n) {
    if (*n >= MAX) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*n] = novo;
    (*n)++;
    printf("Item inserido com sucesso!\n");
}

// Remover item do vetor por nome
void removerItemVetor(Item mochila[], int *n, char nome[]) {
    int i, j, encontrado = 0;
    for (i = 0; i < *n; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            for (j = i; j < *n - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*n)--;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) printf("Item nao encontrado!\n");
}

// Listar itens do vetor
void listarItensVetor(Item mochila[], int n) {
    if (n == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    printf("\n--- Itens da Mochila (Vetor) ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item mochila[], int n, char nome[], int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordenar vetor por nome (Bubble Sort)
void ordenarVetor(Item mochila[], int n) {
    Item temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados com sucesso!\n");
}

// Busca binária no vetor (assume vetor já ordenado)
int buscarBinariaVetor(Item mochila[], int n, char nome[], int *comparacoes) {
    int inicio = 0, fim = n - 1, meio;
    *comparacoes = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}

// =============================
// ======= FUNÇÕES LISTA =======
// =============================

// Inserir item na lista encadeada
No* inserirItemLista(No *inicio) {
    No *novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocacao!\n");
        return inicio;
    }

    printf("Nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicio;
    printf("Item inserido com sucesso!\n");
    return novo;
}

// Remover item da lista por nome
No* removerItemLista(No *inicio, char nome[]) {
    No *atual = inicio, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido com sucesso!\n");
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado!\n");
    return inicio;
}

// Listar itens da lista
void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("Mochila vazia!\n");
        return;
    }
    printf("\n--- Itens da Mochila (Lista Encadeada) ---\n");
    No *aux = inicio;
    int i = 1;
    while (aux != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

// Busca sequencial na lista
int buscarSequencialLista(No *inicio, char nome[], int *comparacoes) {
    *comparacoes = 0;
    No *aux = inicio;
    while (aux != NULL) {
        (*comparacoes)++;
        if (strcmp(aux->dados.nome, nome) == 0)
            return 1;
        aux = aux->proximo;
    }
    return 0;
}

// =============================
// ======= MENUS ===============
// =============================

void menuVetor() {
    Item mochila[MAX];
    int n = 0, opcao;
    char nome[30];
    clock_t inicio, fim;
    double tempo;
    int indice;

    do {
        printf("\n=== Mochila com Vetor ===\n");
        printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar item (Sequencial)\n5. Ordenar e Buscar Binaria\n6. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItemVetor(mochila, &n);
                break;
            case 2:
                printf("Nome do item para remover: ");
                scanf(" %[^\n]", nome);
                removerItemVetor(mochila, &n, nome);
                break;
            case 3:
                listarItensVetor(mochila, n);
                break;
            case 4:
                printf("Nome do item para buscar: ");
                scanf(" %[^\n]", nome);
                inicio = clock();
                indice = buscarSequencialVetor(mochila, n, nome, &comparacoesSequencial);
                fim = clock();
                tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                if (indice != -1)
                    printf("Item encontrado! Comparacoes: %d | Tempo: %.5f s\n", comparacoesSequencial, tempo);
                else
                    printf("Item nao encontrado! Comparacoes: %d | Tempo: %.5f s\n", comparacoesSequencial, tempo);
                break;
            case 5:
                ordenarVetor(mochila, n);
                printf("Nome do item para buscar: ");
                scanf(" %[^\n]", nome);
                inicio = clock();
                indice = buscarBinariaVetor(mochila, n, nome, &comparacoesBinaria);
                fim = clock();
                tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                if (indice != -1)
                    printf("Item encontrado! Comparacoes: %d | Tempo: %.5f s\n", comparacoesBinaria, tempo);
                else
                    printf("Item nao encontrado! Comparacoes: %d | Tempo: %.5f s\n", comparacoesBinaria, tempo);
                break;
        }
    } while (opcao != 6);
}

void menuLista() {
    No *inicio = NULL;
    int opcao;
    char nome[30];
    clock_t inicioT, fimT;
    double tempo;
    int achou;

    do {
        printf("\n=== Mochila com Lista Encadeada ===\n");
        printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar item (Sequencial)\n5. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inicio = inserirItemLista(inicio);
                break;
            case 2:
                printf("Nome do item para remover: ");
                scanf(" %[^\n]", nome);
                inicio = removerItemLista(inicio, nome);
                break;
            case 3:
                listarItensLista(inicio);
                break;
            case 4:
                printf("Nome do item para buscar: ");
                scanf(" %[^\n]", nome);
                inicioT = clock();
                achou = buscarSequencialLista(inicio, nome, &comparacoesSequencial);
                fimT = clock();
                tempo = (double)(fimT - inicioT) / CLOCKS_PER_SEC;
                if (achou)
                    printf("Item encontrado! Comparacoes: %d | Tempo: %.5f s\n", comparacoesSequencial, tempo);
                else
                    printf("Item nao encontrado! Comparacoes: %d | Tempo: %.5f s\n", comparacoesSequencial, tempo);
                break;
        }
    } while (opcao != 5);

    // Libera memória ao final
    No *aux;
    while (inicio != NULL) {
        aux = inicio;
        inicio = inicio->proximo;
        free(aux);
    }
}

// =============================
// ======= MAIN ================
// =============================

int main() {
    int escolha;
    printf("=== Sistema de Mochila ===\n");
    printf("1. Mochila com Vetor\n");
    printf("2. Mochila com Lista Encadeada\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    if (escolha == 1)
        menuVetor();
    else
        menuLista();

    printf("\nPrograma encerrado.\n");
    return 0;
}