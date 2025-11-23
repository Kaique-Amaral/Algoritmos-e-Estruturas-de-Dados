// aula 10 univesp
// agora vamos falar sobre deques
// o deque é uma estrutura onde podemos excluir ou inserir de qualquer uma das suas pontas (do início ou do fim)
// utilizaremos uma implementação duplamente encadeada, na qual cada elemento possui o endereço de seu antecessor e do seu sucessor
// utilizaremos também um nó cabeça pra facilitar o gerenciamento da estrutura

// teremos um ponteiro para o nó cabeça
// cada elemento indica seu antecessor e seu sucessor
// o último tem o nó cabeça como sucessor e o nó cabeça tem o último como antecessor
// cabeça -> 0 <-> 5 <-> 9 <-> 8 <-> 7 <-> 0...
// se queremos excluir um elemento do início, precisamos tomar como base o nó cabeça
// ficaria, assim cabeça -> 0 <-> 9 <-> 8 <-> 7 <-> 0...
// se queremos adicionar o elemento 1 no fim, ficaria
// cabeça -> 0 <-> 9 <-> 8 <-> 7 <-> 1 <-> 0...

#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct auxelem{
    REGISTRO reg;
    struct auxelem* anterior;
    struct auxelem* proximo;
} ELEMENTO;

typedef ELEMENTO* ponteiro;

typedef struct{
    ponteiro cabeca;
} DEQUE;

// as funções que iremos implementar serão as mesmas, com exceção de que
// a inserção e a exclusão serão duas funções
// pois podemos inserir/excluir tanto no início quanto no final

// inicialização
// pra inicializarmos o deque, precisamos criar o nó cabeça
// a variável cabeca precisa apontar pra ele
// o próximo do nó cabeça e o anterior do nó cabeça precisa ser ele mesmo
void inicializardeque(DEQUE* d){
    d->cabeca = (ponteiro) malloc(sizeof(ELEMENTO));
    d->cabeca->proximo = d->cabeca;
    d->cabeca->anterior = d->cabeca;
}

// retornar numero de elementos
// precisaremos percorrer todos os elementos
// como é circular, percorreremos até encontrar o nó cabeça, não até achar um elemento NULL
int tamanho(DEQUE* d){
    ponteiro endereco = d->cabeca->proximo;
    int tamanho = 0;
    while(endereco != d->cabeca){
        tamanho++;
        endereco = endereco->proximo;
    }
    return tamanho;
}

// poderíamos, também:
int tamanho2(DEQUE* d){
    ponteiro endereco = d-> cabeca->anterior; // agora com anterior ao invés de proximo
    int tamanho = 0;
    while(endereco != d->cabeca){
        tamanho++;
        endereco = endereco->anterior;
    }
    return true;
}

// exibição/impressão
// vamos percorrer os elementos válidos e imprimiremos suas chaves
// lembrando que o nó cabeça não é um dos elementos válidos
// podemos ir do fim ao início ou do início ao fim
// nesse caso eu fiz do fim ao início
void exibirdequefim(DEQUE* d){
    ponteiro endereco = d->cabeca->anterior;
    printf("Deque partindo do fim: \" ");
    while(endereco != d->cabeca){
        printf("%i ", endereco->reg.chave);
        endereco = endereco->anterior;
    }
    printf("\"\n");
}

// inserção do elemento
// o usuário escolhe a função que insere no início ou no fim e passa como parâmetro o registro a ser inserido
// a função aloca a memória para o novo elemento
// acertar os ponteiros desse elemento
bool inserirdequefim(DEQUE* d, REGISTRO registroaserinserido){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = registroaserinserido;               // o novo registro recebe o registro inserido pelo usuário
    novo->proximo = d->cabeca;                      // o próximo do novo registro aponta pro nó cabeça
    novo->anterior = d->cabeca->anterior;           // o anterior do novo registro aponta pro que vem antes do nó cabeça
    d->cabeca->anterior = novo;                     // o anterior do nó cabeça aponta pra ele 
    novo->anterior->proximo = novo;                 // e o próximo do antigo topo aponta pro novo também
    return true;
}

// exclusão do elemento
// o usuário passa a chave do elemento que ele quer excluir
// se houver um elemento com a chave, exclui, acerta os ponteiros e retorna true
// caso contrário, retorna false
// precisamos saber quem é o predecessor
bool excluirelemdequeinicio(DEQUE* d, REGISTRO* registroaserexcluido){
    if(d->cabeca->proximo == d->cabeca) return false;   // se o cabeça aponta para si mesmo, então o deque tá vazio
    ponteiro apagar = d->cabeca->proximo;               
    *registroaserexcluido = apagar->reg;                // copia o registro que vai ser apagado
    d->cabeca->proximo = apagar->proximo;               // o cabeça vai receber o seguinte ao elemento que vai ser apagado
    apagar->proximo->anterior = d->cabeca;              // o próximo elemento que vai ser excluído agora temq apontar pra cabeça
    free(apagar);
    return true;
}

// reinicialização de deque
// precisa excluir todos os elementos válidos, menos o nó cabeça
// deixamos ele apontando para si mesmo
void reinicializardeque(DEQUE* d){
    ponteiro endereco = d->cabeca->proximo;
    while(endereco != d->cabeca){
        ponteiro apagar = endereco;
        endereco = endereco->proximo;
        free(apagar);
    }
    d->cabeca->proximo = d->cabeca;
    d->cabeca->anterior = d->cabeca;
}