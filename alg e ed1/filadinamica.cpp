// aula 12 da univesp
// hoje faremos uma fila, porém dinâmica
// a fila é uma estrutura onde as inserções ocorrem no final
// e as exclusões ocorrem no começo
// nesse caso, vamos alocar e desalocar a memória para os elementos sempre que adicionarmos/removermos eles
// cada elemento indicará quem é seu sucessor
#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

// os registros de exemplo
typedef struct{
    TIPOCHAVE chave;
    // outros campos
} REGISTRO;

// cada elemento com um registro aponta para o próximo
typedef struct aux{
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

// ponteiros para elemento
typedef ELEMENTO* ponteiro;

// essa é a fila em si
// são dois ponteiros do tipo elemento
typedef struct{
    ponteiro inicio;
    ponteiro fim;
} FILA;

//  implementaremos funções para inicializar a estrutura
// retornar a quantidade de elementos válidos
// exibir os elementos
// inserir elementos no fim
// retirar os elementos no começo

// para inicializarmos nossa fila, precisamos acertar o valor do campo inicio (pra indicar que não há elementos válidos)
// e acertar o valor de fim (mesma coisa)
void inicializarfila(FILA* a){
    a->inicio = NULL;
    a->fim = NULL;
}

int qntelementos(FILA* a){
    ponteiro endereco = a->inicio;
    int tamanho = 0, i;

    for(i = 0; endereco != NULL; i++){
        tamanho++;
        endereco = endereco->prox;
    }

    return tamanho;
}

// imprimir elemento
void imprimirelemento(FILA* a){
    printf("FILA: \n");
    ponteiro endereco = a->inicio;
    while(endereco != NULL){
        printf("%d\n", endereco->reg.chave);
        endereco = endereco->prox;
    }
    printf("\"\n");
}

// inserção de um elemento
// sempre ocorre no final
// alocaremos memória para o novo elemento
// vamos colocá-lo após o último elemento da fila
// alterar o valor do campo fim
// note que a fila poderia estar vazia
bool inserirelemento(FILA* a, REGISTRO registroaserinserido){
    ponteiro novoelemento = (ponteiro) malloc(sizeof(ELEMENTO));
    novoelemento->reg = registroaserinserido;
    if(a->inicio == NULL) a->inicio = novoelemento;
    else a->fim->prox = novoelemento;
    a->fim = novoelemento;
    return true;
}

// exclusão de um elemento
// iremos copiar esse elemento pra um lugar indicado pelo usuário
// acertar o valor do campo inicio
// eventualmente acertar o valor do campo fim
bool excluirfila(FILA* a, REGISTRO* registroaserexcluido){
    if(a->inicio == NULL) return false;
    *registroaserexcluido = a->inicio->reg;
    ponteiro apagar = a->inicio;
    a->inicio = a->inicio->prox;
    free(apagar);
    if(a->inicio == NULL) a->fim = NULL;
    return true;
}
