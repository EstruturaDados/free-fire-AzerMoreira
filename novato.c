#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ----------------------------------------------------
// Estrutura principal que representa um item do inventário
// ----------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ----------------------------------------------------
// Protótipos das funções
// ----------------------------------------------------
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTÁRIO =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

// ----------------------------------------------------
// Função para inserir um item na mochila
// ----------------------------------------------------
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("\n--- Cadastro de Item ---\n");
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // remove \n

    printf("Tipo do item (arma, municao, cura, etc): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar(); // limpar buffer

    mochila[*qtd] = novoItem;
    (*qtd)++;

    printf("Item adicionado com sucesso!\n");
    listarItens(mochila, *qtd);
}

// ----------------------------------------------------
// Função para remover item pelo nome
// ----------------------------------------------------
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            // mover os próximos itens uma posição para trás
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }

    listarItens(mochila, *qtd);
}

// ----------------------------------------------------
// Função para listar todos os itens
// ----------------------------------------------------
void listarItens(Item mochila[], int qtd) {
    printf("\n--- Itens na Mochila (%d) ---\n", qtd);
    if (qtd == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// ----------------------------------------------------
// Função de busca sequencial por nome
// ----------------------------------------------------
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}