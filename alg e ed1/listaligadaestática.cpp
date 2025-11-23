// aula 5 da univesp de estrutura de dados

// continuaremos utilizando um vetor fixo (MAX posições)
// cada posição do vetor é um nó que contém a chave (dado armazenado) e um índice que aponta para o próximo vetor
// guardaremos o índice do primeiro elemento da lista e o índice do primeiro espaço livre (lista de "nós livres")

#include <stdio.h>

#define max 50
#define NIL -1 // usaremos -1 pra indicar "nulo" (não existe ou então a lista acabou)

// tipo de chave
typedef int TIPOCHAVE;

// nó da lista estática
typedef struct{
    TIPOCHAVE chave;
    int prox; // índice do próximo elemento
} REGISTRO;

// a lista em si
typedef struct{
    REGISTRO a[max];
    int inicio; // índice do primeiro elemento válido
    int dispo; // índice do primeiro espaço livre
} LISTA;

// vamos criar uma função que inicializa a lista
// podemos chamar ela de construtor
void inicializarlista(LISTA* sla){
    int i;
    for(i = 0; i < max-1; i++){
        sla->a[i].prox = i+1; // o próximo aponta pro espaço i+1 para todo i até o penúltimo espaço da lista
    }
    sla->a[max-1].prox = NIL; // no último espaço, o próximo aponta para NIL (-1)

    sla->inicio = NIL; // como a lista começa vazia, não há elementos válidos para apontar
    sla->dispo = 0;    // o espaço livre começa no índice 0
}

// vamos criar uma função auxiliar para obter o nó duma lista de livres
int obterno(LISTA* sla){
    int resultado = sla->dispo; // vamo pegar o próximo espaço livre e guardar em resultado
    if(sla->dispo != NIL){      // se não for nulo
        sla->dispo = sla->a[sla->dispo].prox; // atualizamos para que o próximo espaço disponível seja onde o espaço disponível anterior apontava
    }
    return resultado;
}

// e uma função auxiliar pra devolver o nó para a lista de livres
void devolverno(LISTA* sla, int nodevolvido){
    sla->a[nodevolvido].prox = sla->dispo;  // fazemos com que o nó que estamos devolvendo aponte para o início da lista de disponíveis
    sla->dispo = nodevolvido;               // atualizamos o início da lista para nódevolvido. ou seja, o início da lista de livres agr passa a ser esse nó devolvido
}

// inserção ordenada
bool inserirelemento(LISTA* sla, TIPOCHAVE chavequeinseriremos){
    int i, anterior, novo;
    i = sla->inicio; // pra percorrer a lista
    anterior = NIL; // guarda o nó anterior

    // vamos procurar a posição correta
    while(i != NIL && sla->a[i].chave < chavequeinseriremos){ // seguindo a mesma lógica que anteriormente,
        // se i não é um lugar inválido e a chave na posição é menor que a que inserimos
        anterior = i; // o anterior vira o i
        i = sla->a[i].prox; // i passa pro o próximo nó
    }

    //depois do while, temos dois cenários possíveis
    // 1 - chegamos ao fim da lista(assim, a chavequeinseriremos deve ir pro final)
    // 2 - encontramos a posição onde ele deve ser inserido

    // se já existir chave igual, não insere
    // acho meio desnecessário, mas como essa aula eu tô aprendendo pelo GPT, vou seguir oq ele falar
    if(i != NIL && sla->a[i].chave == chavequeinseriremos) return false;

    // vamos obter espaço livre
    novo = obterno(sla);
    if(novo == NIL) return false; // lista cheia

    // inserimos
    sla->a[novo].chave = chavequeinseriremos;

    // agora encadearemos
    if(anterior == NIL){ // pra inserir no começo se anterior == NIL
        sla->a[novo].prox = sla->inicio; // aponta pro antigo início
        sla->inicio = novo; // novo se torna o novo início
    }
    else{
        sla->a[novo].prox = sla->a[anterior].prox; // o próximo do nó que inserimos aponta para o próximo do anterior
        sla->a[anterior].prox = novo;              // e o anterior aponta para o novo

        // o que isso significa?
        // significa que o nó inserido toma o lugar entre o anterior e pra onde o anterior apontava
        // agora, o anterior aponta pro nó inserido(novo) e o nó inserido aponta pra onde o anterior apontava
    }

    return true;
}

// agora, para remoção
bool excluirelemento(LISTA* sla, TIPOCHAVE chaveaserexcluida){
    int i = sla->inicio, anterior = NIL;

    // mesma coisa de inserção, vamos procurar onde está o cara
    while(i != NIL && sla->a[i].chave < chaveaserexcluida){
        anterior = i;
        i = sla->a[i].prox;
    }

    if(i == NIL || sla->a[i].chave != chaveaserexcluida) return false; // não achou

    if(anterior == NIL){ // se o nó está no início
        sla->inicio = sla->a[i].prox;     // atualizamos o início para o próximo nó
    }
    else {
        sla->a[anterior].prox = sla->a[i].prox; // basicamente, pegamos o anterior e colocamos ele pra apontar pro nó depois do nó removido
    }
    // ou seja, a gente só finge que o nó não existe, e colamos o próximo do anterior pra apontar pro próximo do nó removido
    // ignorando o nó removido

    // pra terminar, agora a gente chama a função de devolvernó pra devolver o i pro espaço de livres
    // assim outro nó pode ser reinserido aqui
    devolverno(sla, i);

    return true;
}

// e uma função simples que só exibe a lista msm
void exibirLista(LISTA* sla){
    int i = sla->inicio;
    printf("Lista: \" ");
    while(i != NIL){
        printf("%d ", sla->a[i].chave);
        i = sla->a[i].prox;
    }
    printf("\"\n");
}
