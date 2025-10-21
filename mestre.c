#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// =============================
// ======= STRUCT ==============
// =============================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// =============================
// ======= VARIÁVEIS ===========
int comparacoes = 0;

// =============================
// ======= FUNÇÕES AUXILIARES ==
// =============================

// Exibe a lista de componentes
void mostrarComponentes(Componente lista[], int n) {
    printf("\n--- Componentes da Torre ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// Troca dois elementos
void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// =============================
// ======= BUBBLE SORT (por nome)
// =============================
void bubbleSortNome(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                trocar(&lista[j], &lista[j + 1]);
            }
        }
    }
}

// =============================
// ======= INSERTION SORT (por tipo)
// =============================
void insertionSortTipo(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;

        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            lista[j + 1] = lista[j];
            j--;
        }
        comparacoes++;
        lista[j + 1] = chave;
    }
}

// =============================
// ======= SELECTION SORT (por prioridade)
// =============================
void selectionSortPrioridade(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[min].prioridade)
                min = j;
        }
        trocar(&lista[i], &lista[min]);
    }
}

// =============================
// ======= BUSCA BINÁRIA (por nome)
// =============================
int buscaBinariaPorNome(Componente lista[], int n, char chave[]) {
    int inicio = 0, fim = n - 1;
    int meio;
    int comparacoesBusca = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBusca++;
        int cmp = strcmp(chave, lista[meio].nome);

        if (cmp == 0) {
            printf("\nComponente encontrado na posicao %d após %d comparacoes!\n", meio + 1, comparacoesBusca);
            return meio;
        } else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }

    printf("\nComponente nao encontrado após %d comparacoes.\n", comparacoesBusca);
    return -1;
}

// =============================
// ======= MEDIÇÃO DE TEMPO =====
// =============================
double medirTempo(void (*algoritmo)(Componente[], int), Componente lista[], int n) {
    clock_t inicio, fim;
    inicio = clock();
    algoritmo(lista, n);
    fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// =============================
// ======= MENU PRINCIPAL ======
// =============================
int main() {
    Componente torre[MAX];
    int n = 0, opcao;
    double tempo;
    char chave[30];

    do {
        printf("\n=== Sistema de Montagem da Torre de Fuga ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave (Busca Binaria - somente apos ordenar por nome)\n");
        printf("6. Mostrar componentes\n");
        printf("7. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                printf("Quantos componentes deseja cadastrar (max %d)? ", MAX);
                scanf("%d", &n);
                getchar();

                for (int i = 0; i < n; i++) {
                    printf("\nComponente %d:\n", i + 1);
                    printf("Nome: ");
                    fgets(torre[i].nome, 30, stdin);
                    torre[i].nome[strcspn(torre[i].nome, "\n")] = 0;

                    printf("Tipo: ");
                    fgets(torre[i].tipo, 20, stdin);
                    torre[i].tipo[strcspn(torre[i].tipo, "\n")] = 0;

                    printf("Prioridade (1-10): ");
                    scanf("%d", &torre[i].prioridade);
                    getchar();
                }
                printf("\nCadastro concluido!\n");
                break;

            case 2:
                tempo = medirTempo(bubbleSortNome, torre, n);
                printf("\nOrdenado por NOME (Bubble Sort)\n");
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(torre, n);
                break;

            case 3:
                tempo = medirTempo(insertionSortTipo, torre, n);
                printf("\nOrdenado por TIPO (Insertion Sort)\n");
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(torre, n);
                break;

            case 4:
                tempo = medirTempo(selectionSortPrioridade, torre, n);
                printf("\nOrdenado por PRIORIDADE (Selection Sort)\n");
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(torre, n);
                break;

            case 5:
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;
                buscaBinariaPorNome(torre, n, chave);
                break;

            case 6:
                mostrarComponentes(torre, n);
                break;

            case 7:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}