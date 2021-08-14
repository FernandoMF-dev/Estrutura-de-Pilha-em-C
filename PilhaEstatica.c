#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CONSTANTES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#define MAX_PILHA 10
#define ERRO_ALOCACAO "\n\tERRO: Falha de alocação de memória!\n"
#define ERRO_PILHA_CHEIA "\n\tERRO: Pilha Cheia!\n"
#define ERRO_PILHA_VAZIA "\n\tERRO: Pilha Vazia!\n"

#define ERRO_ENTRADA "\n\tERRO: Entrada inválido! Apenas valores maiores que 0, por favor.\n"

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
STRUCTS
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

typedef struct Pilha {
    int dados[MAX_PILHA];
    int topo;
} Pilha;

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
DECLARAÇÕES DE FUNÇÕES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

Pilha* criarPilha();
void inicializarPilha(Pilha *pilha);
void empilha(Pilha *pilha, int dado);
int desempilha (Pilha *pilha);
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
    for (int i = 0; i < MAX_PILHA; i++)
        pilha->dados[i] = NULL;
    pilha->topo = 0;
}

void empilha(Pilha *pilha, int dado) {
    if (pilha->topo == MAX_PILHA) {
        printf(ERRO_PILHA_CHEIA);
    } else {
        pilha->dados[pilha->topo] = dado;
        pilha->topo++;
    }
}

int desempilha (Pilha *pilha) {
    if (pilha->topo == 0) {
        printf(ERRO_PILHA_VAZIA);
        return NULL;
    } else {
        pilha->topo--;
        return pilha->dados[pilha->topo];
    }
}

void imprimirPilha(Pilha *pilha) {
    printf("\nPilha[ ");
    for (int i = pilha->topo-1 ; i >= 0; i--) {
        printf("%d", pilha->dados[i]);
        if (i-1 >= 0)
            printf(" | ");
    }
    printf(" ](%d)\n", pilha->topo);
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
