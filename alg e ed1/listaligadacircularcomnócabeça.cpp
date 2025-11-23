// aula 7 da univesp

// na última aula aprendemos a modelar e gerenciar listas encadeadas dinâmicas
// que permitia que não gastássemos memória que não estamos usando
// e não precisávamos gerenciar uma lista de espaços disponíveis

// hoje, adicionaremos duas características à estrutura:
// o último elemento irá apontar para o primeiro
// e possuirá um nó cabeça

// a ideia é que temos um ponteiro apontado para o nó cabeça
// cabeça -> 5 -> 7 -> 8 -> 9 -> 5...
// pra removermos o 8, por exemplo, a gente faz o 7 apontar pro nove e tiramos o 8
// para adicionar o 1, por exemplo, apontamos o cabeça pro 1, o 1 pro 5 e o 9 pro 1

#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct tempoRegistro{
    REGISTRO reg;
    struct tempoRegistro* prox;
} ELEMENTO;

typedef ELEMENTO* ponteiro;

typedef struct{
    ponteiro cabeca;
} LISTA;

// inicialização
// para inicializarmos nossa lista ligada circular e com nó cabeça, precisamos:
// criar o nó cabeça
// a cabeça aponta para ele
// e o nó cabeça aponta para ele mesmo como próximo

void inicializarlista(LISTA* sla){
    sla->cabeca = (ponteiro) malloc(sizeof(ELEMENTO));
    sla->cabeca->prox = sla->cabeca;
}

// retornar número de elementos
// precisaremos percorrer todos os elementos
int tamanho(LISTA* sla){
    ponteiro endereco = sla->cabeca->prox;
    int tamanho = 0;
    while(endereco != sla->cabeca){
        tamanho++;
        endereco = endereco->prox;
    }
    return tamanho;
}

// exibição/impressão a lógica é a mesma
// vamos passar pelos elementos válidos e imprimir a chave deles
// note que o nó cabeça não é um elemento válido
void exibirlista(LISTA* sla){
    ponteiro endereco = sla->cabeca->prox;
    printf("Lista: \" ");
    while(endereco != sla->cabeca){
        printf("%i ", endereco->reg.chave);
        endereco = endereco->prox;
    }
    printf("\"\n");
}

// buscar por elemento
// a função deverá receber uma chave, retornar o endereço do elemento encontrado, ou retornar NULL se não encontrar
ponteiro buscasentinela(LISTA* sla, TIPOCHAVE chaveprocurada){
    ponteiro atual = sla->cabeca->prox;
    sla->cabeca->reg.chave = chaveprocurada;
    while(atual->reg.chave != chaveprocurada) atual = atual->prox;
    if(atual != sla->cabeca) return atual;
    return NULL;
}

// caso a lista esteja ordenada pelos valores de cada chave:
ponteiro buscasentinelaordenada(LISTA* sla, TIPOCHAVE chaveprocurada){
    ponteiro atual = sla->cabeca->prox;
    sla->cabeca->reg.chave = chaveprocurada;
    while(atual->reg.chave < chaveprocurada) atual = atual->prox;
    if(atual != sla->cabeca && atual->reg.chave == chaveprocurada) return atual;
    return NULL;
}

// inserção de um elemento
// o usuário passa como parâmetro um registro a ser inserido
// vamos fazer uma inserção ordenada pelo valor da chave do registro passado e não vamos permitir elementos repetidos
// precisamos identificar entre quais elementos o elemento será inserido
// vamos fazer uma função auxiliar:
ponteiro buscaseqexc(LISTA* sla, TIPOCHAVE chave, ponteiro* anterior){
    *anterior = sla->cabeca;        // aqui o anterior é o cabeca
    ponteiro atual = sla->cabeca->prox; // e o atual começa como o primeiro sem ser o cabeça
    sla->cabeca->reg.chave = chave;
    while(atual->reg.chave < chave){
        *anterior = atual;
        atual = atual->prox;
    }
    if(atual != sla->cabeca && atual->reg.chave == chave) return atual;
    return NULL;
}

// inserção ordenada - sem dupllicação
bool inserirelementolistaord(LISTA* sla, REGISTRO registroaserinserido){
    ponteiro anterior, i;
    i = buscaseqexc(sla, registroaserinserido.chave, &anterior);
    if(i != NULL) return false;
    i = (ponteiro) malloc(sizeof(ELEMENTO));
    i->reg = registroaserinserido;
    anterior->prox = i;
    return true;
}

// exclusão de um elemento
// faz a mesma coisa, busca e destrói
// precisamos saber o anterior para que ele aponte para o seguinte
// sempre haverá anterior por ser uma lista circular
bool excluirelementolista(LISTA* sla, TIPOCHAVE chaveaserexcluída){
    ponteiro anterior, i;
    i = buscaseqexc(sla, chaveaserexcluída, &anterior);
    if(i == NULL) return false;
    anterior->prox = i->prox;
    free(i);
    return true;
}

// reinicialização da lista
// excluir todos os elementos válidos e atualizar o campo prox do nó cabeça
void reiniciarlista(LISTA* sla){
    ponteiro endereco = sla->cabeca->prox;
    while(endereco != sla->cabeca){
        ponteiro apagar = endereco;
        endereco = endereco->prox;
        free(apagar);
    }
    sla->cabeca->prox = sla->cabeca;
}