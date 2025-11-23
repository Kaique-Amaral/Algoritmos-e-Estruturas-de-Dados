// pilha

#include <stdio.h>
#include <malloc.h>

typedef struct{
    int nusp;
} REGISTRO;

typedef struct no{
    REGISTRO reg;
    struct no* proximo;
} ELEMENTO, *ponteiro;

typedef struct{
    ponteiro topo;
} PILHA;

void inicializarpilha(PILHA* a){
    a->topo = NULL;
}

bool inserirelemento(PILHA* a, REGISTRO reg){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->proximo = a->topo;
    a->topo = novo;
    return true;
}

bool removerelemento(PILHA* a, REGISTRO* reg){
    if(a->topo == NULL) return false;
    ponteiro apagar = a->topo;
    *reg = a->topo->reg;
    a->topo = a->topo->proximo;
    free(apagar);
}
