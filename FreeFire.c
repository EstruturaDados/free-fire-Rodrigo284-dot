#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 // Capacidade máxima da mochila

// ============================
// Estrutura que representa um item do inventário
// ============================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ============================
// Funções principais
// ============================

// Cadastra um novo item na mochila
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n⚠️  A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== CADASTRO DE ITEM ===\n");

    printf("Nome do item: ");
    getchar(); // limpa o buffer do teclado
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove \n

    printf("Tipo (arma, munição, cura, ferramenta...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    // Adiciona o item no vetor
    mochila[*total] = novo;
    (*total)++;

    printf("\n✅ Item '%s' adicionado à mochila!\n", novo.nome);
}

// Remove um item da mochila pelo nome
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n⚠️  A mochila está vazia. Nada a remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== REMOVER ITEM ===\n");
    printf("Digite o nome do item a remover: ");
    getchar();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Move os itens seguintes uma posição para trás
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("\n🗑️  Item '%s' removido com sucesso!\n", nomeBusca);
            return;
        }
    }

    printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
}

// Lista todos os itens da mochila
void listarItens(Item mochila[], int total) {
    printf("\n=== ITENS NA MOCHILA ===\n");
    if (total == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Busca um item pelo nome (busca sequencial)
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\n⚠️  A mochila está vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== BUSCAR ITEM ===\n");
    printf("Digite o nome do item: ");
    getchar();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
}

// ============================
// Função principal (menu interativo)
// ============================
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n==============================\n");
        printf("     🎒 SISTEMA DE INVENTÁRIO\n");
        printf("==============================\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                listarItens(mochila, total);
                break;
            case 2:
                removerItem(mochila, &total);
                listarItens(mochila, total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("\n👋 Encerrando o sistema. Boa sorte no jogo!\n");
                break;
            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
