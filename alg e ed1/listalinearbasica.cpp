// aula 3 e 4 da univesp de estrutura de dados

#include <stdio.h>

#define max 50

typedef int TIPOCHAVE;

// suponha um struct simples de registro
typedef struct{
    TIPOCHAVE chave;
    // insira outros campos, tanto faz
} REGISTRO;

// agora, fazemos a lista
// por ser linear, ela nao aponta pro próximo elemento
// ela vai ser um struct de registros
typedef struct{
    REGISTRO a[max+1];
    int numeroelementos;
} LISTA;

// tornei a lista comentada pois mais abaixo ha uma lista atualizada

// vamos inicializar a lista
// usando um exemplo:
void inicializarlista(LISTA* sla){
    // usaremos sla->numeroelementos = 0, pois sla.numeroelementos criaria uma cópia
    // queremos alterar diretamente no numero elementos de sla
    // por causa disso, precisa ser um ponteiro de lista
    sla->numeroelementos = 0;
}

// vamos fazer uma funçao que retorna o número de elementos
// nesse caso, é trivial pq temos o int numeroelementos na lista
// entao basta retornar o valor numeroelementos da lista
int tamanho(LISTA* sla){
    return sla->numeroelementos;
}

// agora, para printar os elementos
void exibirlista(LISTA* sla){
    int i;
    printf("Lista: \" ");
    for(i = 0; i < sla->numeroelementos; i++){
        printf("%i ", sla->a[i].chave);
        // ou seja, para a lista sla, vai ir em cada registro e printar o valor do registro
    }
    printf("\"\n");
}

// vamos fazer uma funçao de busca por elementos
// a funçao devera receber uma chave do usuario
// e retornar a posiçao do elemento na lista (caso seja encontrado)
// retorna -1 caso nao ache

int buscasequencial(LISTA* sla, TIPOCHAVE elementobuscado){
    // a funçao vai receber de entrada a lista em questao e o elemento buscado
    int i = 0;
    // vamos entrar num loop
    while(i < sla->numeroelementos){
        // compararemos o valor do elemento buscado com a chave do registro a[i], na lista sla
        // se acharmos, a funçao retorna i(a posiçao) e sai da funçao
        if(elementobuscado == sla->a[i].chave) return i;
        // senao, vai pro próximo registro e compara o elemento buscado com a chave do próximo registro
        else i++;
    }
    // se nao achou, a funçao retorna -1
    return -1;
}

// e se quisermos fazer uma busca sequencial com somente uma comparaçao?
// é impossível nao comparar a chave do elemento atual com a do elemento buscado
// e se nao precisassemos comparar com o número maximo de elementos?
// como garantiríamos que nao vamos passar do último elemento?
// simples, garantido que a chave buscada sera encontrada!
// vamos adicionar um elemento extra inserido no final da lista
// o usuario nao vai ver
// isso só serve pro código
// chamamos de elemento sentinela
int buscasentinela(LISTA* sla, TIPOCHAVE elementobuscado){
    int i = 0;
    // colocamos a chave no sla.a(sla.numeroelementos) (ou seja, no espaço 50, ja que numero de elementos = max)
    sla->a[sla->numeroelementos].chave = elementobuscado;
    // garantimos que o while só para quando for encontrado o elemento
    while(sla->a[i].chave != elementobuscado) i++;
    if(i == sla->numeroelementos) return -1;
    else return i;
}
// existe um problema na abordagem: e se a lista nao tiver mais espaço?
// podemos criar uma lista com total de registros = max+1
// por isso agora a lista ali em cima esta assim
// eba
// problema resolvido


// a busca binaria teoricamente é mais eficiente, mas precisaria que os elementos estejam ordenados
// pra isso, precisamos criar uma nova funçao de inserçao de elemento


// agora, uma funçao de inserçao de elemento
// o usuario ira dizer a posiçao que quer inserir o elemento
// se a posiçao for valida e a lista nao estiver cheia
// a gente "empurra" pra frente todos os elementos que estiverem depois da posiçao onde iremos inserir o elemento
// insere o elemento na posiçao especificada
// e daí aumenta o número de elementos da lista

bool inserirnalista(LISTA* sla, REGISTRO registroquequeremosinserir, int posicao){
    int i;
    // checamos se é valido
    // pra ser valido, a lista nao pode estar cheia(sla->numeroelementos == max)
    // e a posiçao nao pode ser menor que 0 e maior que o número de elementos
    if((sla->numeroelementos == max) || (posicao < 0) || (posicao > sla->numeroelementos)){
        return false;
    }
    // agora movemos todos os elementos maiores que posiçao para a direita
    for(i = sla->numeroelementos; i > posicao; i--) {
        sla->a[i] = sla->a[i-1];
    }
    // e simplesmente inserimos o registro na posiçao que queremos
    sla->a[i] = registroquequeremosinserir;
    // e aumentamos o numero total de elementos
    // eba
    sla->numeroelementos++;

    return true;
}

// como eu tinha dito antes, uma busca binaria precisaria que os elementos estivessem ordenados
// como nao estao, vamos alterar a inserçao de elementos para que seja de forma ordenada
bool inserirelementoslistaordenada(LISTA* sla, REGISTRO registroprocurado){
    if(sla->numeroelementos >= max) return false;    // se a lista estiver cheia, nao da pra inserir
    int posicao = sla->numeroelementos;              
    // enquanto a posiçao for maior que zero, vamos comparar pra ver se a chave de a[posiçao-1] é maior que a procurada
    // assim, a gente encontra a posiçao que vamos inserir
    while(posicao > 0 && sla->a[posicao-1].chave > registroprocurado.chave){
        // se for, movemos pra direita
        sla->a[posicao] = sla->a[posicao-1];
        posicao--;
    }
    // como ja movemos todos os elementos maiores que registroprocurado pra direita, podemos simpllesmente:
    sla->a[posicao] = registroprocurado;
    sla->numeroelementos++;
}

// vamos fazer a busca binaria agora
int buscabinaria(LISTA* sla, TIPOCHAVE chaveprocurada){
    int esq, dir, meio;
    esq = 0; // esquerda é o primeiro elemento valido do arranjo
    dir = sla->numeroelementos-1; // o último elemento valido do arranjo
    while(esq <= dir){
        meio = ((esq+dir)/2);
        if(sla->a[meio].chave == chaveprocurada) return meio; // se a chave buscada ta exatamente no meio, ja retorna o meio
        else{                                                 // se nao tiver
            if(sla->a[meio].chave < chaveprocurada) esq = meio+1; // se ela tiver entre o meio e a direita, vamo procurar só da metade direita
            else dir = meio - 1; // senao, procuramos só pela metade esquerda
        }
        // como a chave é o valor dentro do registro, realmente precisa estar ordenada do menor para o maior os registros
        // por isso da inserçao ordenada
    }

    // se nao achar, entao retorna -1
    return -1;
}

// por fim, exclusao de elementos
// o usuario vai passar a chave que ele quer excluir
// se tiver um elemento com essa chave, vai excluid o elemento
// deslocar todos os elementos posteriores pra uma posiçao pra esquerda
// diminui em um o campo de numero de elementos
// e retorna true
// senao, retorna false
bool excluirelemento(LISTA* sla, TIPOCHAVE registroquequeremosexcluir){
    int i, j;
    for(i = 0; i < sla->numeroelementos; i++){
        if(sla->a[i].chave == registroquequeremosexcluir){
            for(j = i; j < sla->numeroelementos-1; j++){
                sla->a[j].chave = sla->a[j+1].chave;
            }
            sla->numeroelementos--;
            return true;
        }
    }
    return false;
}

// podemos usar busca binaria ou sequencial na exclusao, também
//ó:
bool exclusaobinaria(LISTA* sla, TIPOCHAVE chaveprocurada){
    int posicao, j;
    posicao = buscabinaria(sla, chaveprocurada);
    if(posicao == -1) return false;
    for(j=posicao; j < sla->numeroelementos-1; j++) sla->a[j].chave = sla->a[j+1].chave;
    sla->numeroelementos--;
    return true;
}