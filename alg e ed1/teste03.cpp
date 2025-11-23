// lista encadeada dinâmica

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

    novo->proximo = a->cabeca;
    a->cabeca = novo;
    return true;
}

bool inserirelementofinal(LISTA* a, REGISTRO reg){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->proximo = NULL;

    ponteiro ultimo = a->cabeca;
    while(ultimo->proximo != NULL){
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = novo;

    return true;
}

bool removerelementoinicio(LISTA* a, REGISTRO reg){
    
}
