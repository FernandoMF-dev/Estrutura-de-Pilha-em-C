#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CONSTANTES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#define ERRO_ALOCACAO "\n\tERRO: Falha de alocação de memória!\n"
#define ERRO_PILHA_VAZIA "\n\tERRO: Pilha Vazia!\n"

#define ERRO_ENTRADA "\n\tERRO: Entrada inválido! Apenas valores maiores que 0, por favor.\n"

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
STRUCTS
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

typedef struct No {
    int dado;
    struct No *prox;
} No;

typedef struct Pilha {
    No *topo;
    int tamanho;
} Pilha;

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
DECLARAÇÕES DE FUNÇÕES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

Pilha* criarPilha();
void inicializarPilha(Pilha *pilha);
void empilha(Pilha *pilha, int dado);
int desempilha(Pilha *pilha);
void imprimirPilha(Pilha *pilha);

int menu();
int validarEntrada();

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
FUNÇÕES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

Pilha* criarPilha() {
    Pilha *novo = (Pilha*) malloc (sizeof(Pilha));

    if (novo != NULL) {
        inicializarPilha(novo);
    } else {
        printf(ERRO_ALOCACAO);
    }
    
    return novo;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

void empilha(Pilha *pilha, int dado) {
    No *ptr = (No*)malloc(sizeof(No));
    if (ptr == NULL) {
        printf("\n\tERRO: Erro de alocação de nó!\n");
        return;
    }
    ptr->dado = dado;
    ptr->prox = pilha->topo;
    pilha->topo = ptr;
    pilha->tamanho++;
}

int desempilha(Pilha *pilha) {
    No *ptr = pilha->topo;
    int backup;
    if (ptr == NULL){
        printf(ERRO_PILHA_VAZIA);
        return NULL;
    }
    pilha->topo = ptr->prox;
    ptr->prox = NULL;
    backup = ptr->dado;
    free(ptr);
    pilha->tamanho--;
    return(backup);
}

void imprimirPilha(Pilha *pilha) {
    No *ptr = pilha->topo;

    printf("\nPilha[ ");
    while (ptr != NULL) {
       printf("%d", ptr->dado);
       if (ptr->prox != NULL)
           printf(" | ");
       ptr = ptr->prox;
    }
    printf(" ](%d)\n", pilha->tamanho);
}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
MAIN
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

int menu() {
    int select = 0;

    printf("\n===== PILHA =====");
    printf("\n1 - Inserir");
    printf("\n2 - Remover");
    printf("\n3 - Imprimir");
    printf("\n0 - Sair");
    printf("\nEscolha: ");
    scanf("%d", &select);
    printf("\n=================\n");

    return select;
}

int validarEntrada() {
    int valor;

    while (1) {
        printf("\nEntrada: ");
        scanf("%d", &valor);

        if (valor <= NULL) {
            printf(ERRO_ENTRADA);
        } else {
            break;
        }
    }

    return valor;
}

int main(int argc, char const *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    Pilha *pilha = criarPilha();
    int valor;

    if (pilha == NULL) {
        return 0;
    }

    while (1) {
        switch (menu()) {
        case 1:
            valor = validarEntrada();
            empilha(pilha, valor);
            break;
        case 2:
            valor = desempilha(pilha);
            if (valor != NULL) {
                printf("\nSaida: %d\n", valor);
            }
            break;
        case 3:
            imprimirPilha(pilha);
            break;
        default:
            printf("\n\tSaindo...\n\n");
            free(pilha);
            return 0;
            break;
        }
    }
}