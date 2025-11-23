// lista circular

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
    ponteiro cabeca;
} LISTA;

void inicializarlista(LISTA* a){
    a->cabeca = NULL;
}

bool inserirelemento(LISTA* a, REGISTRO reg){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    
    if(a->cabeca == NULL){
        novo->proximo = novo;
        a->cabeca = novo;
        return true;
    }
    ponteiro ultimo = a->cabeca;
    while(ultimo->proximo != a->cabeca){
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = novo;
    novo->proximo = a->cabeca;
    a->cabeca = novo;
    return true;
}

bool removerelemento(LISTA* a, REGISTRO* reg){
    if(a->cabeca == NULL) return false;
    ponteiro apagar = a->cabeca;
    *reg = a->cabeca->reg;
    if(a->cabeca->proximo == a->cabeca) {
        free(apagar);
        a->cabeca = NULL;
        return true;
    }
    ponteiro ultimo = a->cabeca;
    while(ultimo->proximo != a->cabeca){
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = a->cabeca->proximo;
    a->cabeca = a->cabeca->proximo;
    free(apagar);
    return true;
}

