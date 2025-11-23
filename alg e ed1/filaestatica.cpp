// aula 11 da univesp
// falaremos de fila estática hoje
// é uma estrutura linear onde as inserções ocorrem no final da fila
// as exclusões ocorrem no início da fila
// segue a lógica de uma fila de pessoas (quem chegou primeiro sai, e quem chegar depois entra no final)

#include <stdio.h>

#define MAX 50

typedef int TIPOCHAVE;  

typedef struct{
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct{
    REGISTRO a[MAX];
    int inicio;
    int numeroelementos;
} FILA;

// as funções serão as mesmas que as outras, com a exceção que a exclusão é sempre no início e a inclusão sempre no final

// inicializar fila
// precisamos acertar o valor do número de elementos(não há nenhum válido) e acertar o início(índice do 1° elemento válido)
void inicializarfila(FILA* f){
    f->inicio=0;
    f->numeroelementos=0;
}

// retornar numero de elementos
// só retornar o valor do campo numeroelementos
int tamanhofila(FILA* f){
    return f->numeroelementos;
}

// exibição/impressão
// vamos ter que iterar pelos elementos válidos, a começar pelo início
// existem numeroelementos de elementos válidos e o primeiro está na posição inicio do arranjo
// após o elemento da última posição do arranjo(posição MAX-1) está o elemento da posição 0, pois tratamos o arranjo como se fosse circular
void exibirfila(FILA* f){
    printf("Fila: \" ");
    int i = f->inicio;
    int temp;
    for(temp = 0; temp < f->numeroelementos; temp++){
        printf("%i, ", f->a[i].chave);
        i = (i+1) % MAX;    // pra não ultrapassar o limite do arranjo
    }
    printf("\"\n");
}