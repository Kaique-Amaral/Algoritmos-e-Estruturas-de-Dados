// fila dinâmica
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
    ponteiro inicio;
    ponteiro fim;
} FILA;

void inicializarfila(FILA* a){
    a->fim = NULL;
    a->inicio = NULL;
}

bool inserirelemento(FILA* a, REGISTRO reg){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->proximo = NULL;
    if(a->fim == NULL && a->inicio == NULL) a->fim = a->inicio = novo;
    else{
        a->fim->proximo = novo;
        a->fim = novo;
    }
    return true;
}

bool removerelemento(FILA* a, REGISTRO* reg){
    if(a->fim == NULL && a->inicio == NULL) return false;
    ponteiro apagar = a->inicio;
    *reg = a->inicio->reg;
    a->inicio = a->inicio->proximo;
    free(apagar);
    return true;
}
