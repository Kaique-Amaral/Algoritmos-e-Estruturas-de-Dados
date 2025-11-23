// fila simplesmente encadeada
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

bool inserirelementoinicio(LISTA* a, REGISTRO reg){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = reg;

    if(a->cabeca == NULL){
        a->cabeca = novo;
        novo->proximo = NULL;
        return true;
    }
    novo->proximo = a->cabeca;
    a->cabeca = novo;
    return true;
}

bool inserirelementofinal(LISTA* a, REGISTRO reg){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = reg;

    novo->proximo = NULL;
    if(a->cabeca == NULL){
        a->cabeca = novo;
        return true;
    }
    ponteiro ultimo = a->cabeca;
    while(ultimo->proximo != NULL){
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = novo;
    novo->proximo = NULL;
    return true;
}

bool removerelementoinicio(LISTA* a, REGISTRO* reg){
    if(a->cabeca == NULL) return false;
    ponteiro apagar = a->cabeca;
    *reg = a->cabeca->reg;
    a->cabeca = a->cabeca->proximo;
    free(apagar);
    return true;
}

bool removerelementofinal(LISTA* a, REGISTRO* reg){
    if(a->cabeca == NULL) return false;
    ponteiro ultimo = a->cabeca;
    
    ponteiro penultimo;
    while(ultimo->proximo != NULL){
        if(ultimo->proximo->proximo == NULL){
            penultimo = ultimo;
        }
        ultimo = ultimo->proximo;
    }
    *reg = ultimo->reg;
    penultimo->proximo = NULL;
    free(ultimo);
}
