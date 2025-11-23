// aula 9 univesp

// pilha com implementação dinâmica
// como a pilha normal, mas vamos alocar memória para não gastarmos memória desnecessária
// ainda segue a mesma lógica de uma pilha normal
// cada elemento indicará quem é seu sucessor (quem está abaixo dele na pilha)

#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* ponteiro;

typedef struct{
    ponteiro topo;
} PILHA;

// inicialização: pra iniciar, precisamos só acertar o valor do topo
void inicializarpilha(PILHA* p){
    p->topo = NULL;
}

// retornar número de elementos
int retornarnumeroelementos(PILHA* p){
    ponteiro endereco = p->topo;
    int tamanho = 0;
    while(endereco != NULL){
        tamanho++;
        endereco = endereco->prox;
    }
    return tamanho;
}

// poderíamos escrever, também
int retornarnumeroelementos2(PILHA p){
    ponteiro endereco = p.topo; // usamos ., já que estamos passando uma cópia, não o endereço;
    // não há grande diferença na função, mas normalmente passar o endereço é melhor
    int tamanho = 0;
    while(endereco != NULL){
        tamanho++;
        endereco = endereco->prox;
    }
    return tamanho;
}

// verificar se a pilha está vazia
// poderiámos usar a função tamanho, e se o tamanho != 0, dá pra verificar se ela está vazia ou não
// mas isso gasta tempo, porque em pilhas que há mts elementos, a função vai demorar pra rodar
// podemos fazer algo mais simples:
bool estavazia(PILHA* p){
    if(p->topo == NULL) return true;    // pois topo = NULL se ela está vazia
    return false;
}

// exibição/impressão
// merma coisa, vamo percorrer os elementos e imprimir suas chaves
void exibirpilha(PILHA* p){
    ponteiro endereco = p->topo;
    printf("Pilha: \" ");
    while(endereco !=NULL){
        printf("i% ", endereco->reg.chave);
        endereco = endereco->prox;
    }
    printf("\"\n");
}

// push
// inserção de um elemento
// o usuário passa um parâmetro como registro a ser inserido
// o novo elemento será o novo topo da fila e apontará para o antigo topo
bool inserirelementopilha(PILHA* p, REGISTRO registroaserinserido){
    ponteiro novo = (ponteiro) malloc(sizeof(ELEMENTO));
    novo->reg = registroaserinserido;
    novo->prox = p->topo;
    p->topo = novo;
    return true;
}

// pop
// exclusão de um elemento
// exclui o elemento do topo da lista, e copia a memória pra certo endereço
// também checa se ela está vazia, pois não dá pra excluir se ela estiver vazia
bool excluirelementpilha(PILHA* p, REGISTRO* registroaserexcluido){
    if(p->topo == NULL) return false;
    *registroaserexcluido = p->topo->reg;
    ponteiro apagar = p->topo;
    p->topo = p->topo->prox;
    free(apagar);
    return true;
}

// reinicializar pilha
// pra reinicializar precisamos excluir todos os elementos e colocar NULL no topo
void reinicializarpilha(PILHA* p){
    ponteiro apagar;
    ponteiro posicao = p->topo;
    while(posicao != NULL){
        apagar = posicao;
        posicao = posicao->prox;
        free(apagar);
    }
    p->topo = NULL;
}