// lista duplamente encadeada

#include <stdio.h>
#include <malloc.h>

typedef struct{
    int nusp;
} REGISTRO;

typedef struct no{
    REGISTRO reg;
    struct no* proximo;
    struct no* anterior;
} ELEMENTO, *ponteiro;

typedef struct{
    ponteiro cabeca;
} LISTA;

void inicializarlista(LISTA* a){
    a->cabeca = NULL;
}

bool inserirlistainicio(LISTA* a, REGISTRO reg){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->proximo = a->cabeca;
    if(a->cabeca == NULL){
        a->cabeca = novo;
        novo->anterior = NULL;
        return true;
    }
    a->cabeca->anterior = novo;
    novo->anterior = NULL;
    a->cabeca = novo;
    return true;
}

bool inserirlistafinal(LISTA* a, REGISTRO reg){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = reg;

    if(a->cabeca == NULL){
        novo->proximo = a->cabeca;
        a->cabeca = novo;
        novo->anterior = NULL;
        return true;
    }

    ponteiro ultimo = a->cabeca;
    while(ultimo->proximo != NULL){
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = novo;
    novo->anterior = ultimo;
    novo->proximo =  NULL;
    return true;
}

bool removerinicio(LISTA* a, REGISTRO* reg){
    if(a->cabeca == NULL) return false;

    ponteiro apagar = a->cabeca;
    *reg = a->cabeca->reg;

    if(a->cabeca->proximo == NULL){
        free(apagar);
        return true;
    }

    a->cabeca = a->cabeca->proximo;
    a->cabeca->anterior = NULL;
    free(apagar);
    return true;
}

bool removerfinal(LISTA* a, REGISTRO* reg){
    if(a->cabeca == NULL) return false;
    ponteiro apagar = a->cabeca;
    if(a->cabeca->proximo == NULL){
        *reg = a->cabeca->reg;
        free(apagar);
        return true;
    }

    while(apagar->proximo != NULL){
        apagar = apagar->proximo;
    }
    *reg = apagar->reg;
    apagar->anterior->proximo = NULL;
    free(apagar);
    return true;
}
