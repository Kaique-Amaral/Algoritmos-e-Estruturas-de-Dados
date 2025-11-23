// aula 8 univesp
// uma pilha é uma estrutura linear onde:
// as inserções ocorrem no topo da pilha
// as exclusões ocorrem no topo da pilha
// segue a mesma lógica de uma pilha de papéis

// utilizaremoss um arranjo de elementos de tamanho predefinido
// controlaremos a posição do elemento que está no topo da pilha

#include <stdio.h>

#define MAX 50

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct{
    REGISTRO a[MAX];
    int topo;
} PILHA;

// impletemntaremos funções para inicializar, retornar quantidade de elementos válidos, exibir os elementos, inserir elementos(push) excluir elementos(pop), reinicializar a esturtura

// inicialização
// precisamos acertar o valor do campo topo
// como o topo indica como está o elemento do topo, uma pilha com 1 elemento teria topo 0
// como tem 0 elementos, é -1
void inicializarpilha(PILHA* p){
    p->topo = -1;
}

//retornar número de elementos
// o número de elementos será topo+1
int retornarelementos(PILHA* p){
    return p->topo+1;
}

// exibição/impressão
// vamos iterar pelos elementos válidos e imprimir suas chaves, do topo para baixo
void exibirpilha(PILHA* p){
    printf("Pilha: \" ");
    int i;
    for(i = p->topo; i >= 0; i--){
        printf("%i ", p->a[i].chave);
    }
    printf("\"\n");
}

// push
// inserção do elemento no topo da pilha
// se a pilha não estiver cheia, o elemento será inserido acima de onde estava o topo, e daí o topo é atualizado
bool  inserirelementopilha(PILHA* p, REGISTRO registroaserinserido){
    if(p->topo >= MAX-1) return false;
    p->topo = p->topo+1;
    p->a[p->topo] = registroaserinserido;
    return true;
}

// pop
// exclusão
// se estiver vazia, retorna falso, senão copiaremos o topo da pilha para um lugar indicado pelo usuário,
// excluiremos o topo da pilha e atualizamos o topo(topo = topo-1)
bool excluirelementopilha(PILHA* p, REGISTRO* registroaserexcluido){
    if(p->topo == -1) return false;
    *registroaserexcluido = p->a[p->topo];
    p->topo = p->topo-1;
    return true;
}

// reinicialização da pilha
// basta colocarmos topo = -1, já que é estática

void reinicializarpilha(PILHA* p){
    p->topo = -1;
}