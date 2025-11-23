// aula 6 da Univesp

#include <stdio.h>
#include <malloc.h>

// já fizemos uma ligação estática
// agora faremos uma dinâmica, alocando elementos, para não gastar memória desnecessária

// de ideia geral, uma lista ligada/encadeada é quando temos um ponteiro para o primeiro elemento
// e cada elemento tem uma parte que aponta para seu sucessor
// sendo o último elemento apontando para NULL

// suponha uma lista ligada: inicio -> 5 -> 7 -> 8 -> 9 -> NULL
// como excluiríamos o 8?
// fazemos o 7 apontar pro 9, e liberamos o espaço e memória do 8: início -> 5 -> 7 -> 9 -> NULL
// como inserimos o 1?
// fazemos o 1 apontar para o cinco, e o ponteiro que aponta para o primeiro elemento apontar para o 1
// início -> 1 -> 5 -> 7 -> 9 -> NULL

// estruturalmente, temos:
typedef int TIPOCHAVE;

// o registro; uma struct onde existem as informações
typedef struct {
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

// antes, tínhamos um índice do arranjo para o próximo elemento
// agora, temos um elemento que aponta para o próximo
typedef struct aux{
    REGISTRO reg;
    struct aux* proximo;
} ELEMENTO;

// vamos colocar isso aqui pra ficar mais claro
// um ponteiro para o tipo elemento vai se chamar ponteiro
typedef ELEMENTO* ponteiro;

// e a lista propriamente dita é apenas um ponteiro que aponta para o início
typedef struct{
    ponteiro inicio;
} LISTA;

// agora, inicialização
// para inicializarmos nossa lista ligada, precisamos colocar o valor NULL na variável início
// para demonstrar que ainda não há elemento válido na estrutura
void inicializarlista(LISTA *sla){
    sla->inicio = NULL;
}

// já que optamos por não criar um campo com o número de elementos, vamos percorrer todos os elementos pra contar
int tamanho(LISTA* sla){
    // o ponteiro que aponta para os elementos vai apontar para o início da lista
    ponteiro endereco = sla->inicio;
    int tamanho = 0;

    while(endereco != NULL){ // enquanto o endereço não for NULL (ou seja, não apontar para um espaço fora da fila)
        tamanho++; // aumenta em um o tamanho
        endereco = endereco->proximo; // e aponta para o próximo endereço
    }
}

// exibição
void exibirlista(LISTA* sla){
    // mesma lógica acima do laço
    // com a diferença que vamos printar o registro contido em cada endereço
    ponteiro endereço = sla->inicio;
    printf("Lista: \" ");
    while(endereço != NULL){
        printf("%i ", endereço->reg.chave);
        endereço = endereço->proximo;
    }
    printf("\"\n");
}

// buscar por elemento
// a função deverá receber uma chave, retornar o endereço em que o elemento se encontra, e retornar NULL caso não acha
ponteiro buscasequencial(LISTA* sla, TIPOCHAVE chavebuscada){
    ponteiro posicao = sla->inicio;
    while(posicao != NULL){
        if(posicao->reg.chave == chavebuscada) return posicao;
        posicao = posicao->proximo;
    }
    return NULL;
}

// caso a lista seja ordenada, podemos fazer assim:
ponteiro buscasequencialordenada(LISTA* sla, TIPOCHAVE chavebuscada){
    ponteiro posicao = sla->inicio;
    // começa do primeiro elemento (início) e vai passando pro próximo elemento enquanto os elementos forem menores que a chave buscada
    // quando deixar de ser menor, ele para e vai comparar
    while(posicao != NULL && posicao->reg.chave < chavebuscada) posicao = posicao->proximo;
    // aqui abaixo a comparação
    // se a posicão não for nula e a chave buscada for igual, a gente retorna a posição
    if(posicao != NULL && posicao->reg.chave == chavebuscada) return posicao;
    // senão, retornamos NULL
    return NULL;
}

// inserção de um elemento
// o usuário passa como parâmetro um registro a ser inserido
// vamos inserir ordenadamente pelo valor da chave
// não aceitaremos elementos repetidos
// na inserção precisamos identificar entre quais elementos será inserido
// alocaremos memória para o elemento inserido e faremos o predecessor apontar pra ele
// desenvolveremos uma função auxiliar para nos informar o endereço do elemento se existir
// e o endereço do predecessor desse elemento (independente dele existir ou não)
// como a função vai nos passar dois endereços diferentes?
// vamos ver como uma função pode passar dois resultados:
// veja por exemplo a função quadrado e cubo:
/*


int funcaoquadradocubo(int x, int* y){
    *y = x*x*x;
    return x*x;
}
    
ela retorna um valor
mas ela recebe, além do valor, um ponteiro de inteiro
podemos, depois, printar o valor do ponteiro passado
assim, seria como se houvéssemos recebido o valor de x e de y
veja por exemplo:

int main(){
    int a = 30;
    int cubo;
    int quadrado = funcaoquadradocubo(a, &cubo);
    printf("a: %s, a*a: %i, a*a*a: %i\n", a, quadrado, cubo);
    
    return 0;
    }

consegue ver?
*/

// agora, vamos pra função busca auxiliar
ponteiro buscasequencialexc(LISTA* sla, TIPOCHAVE chavebuscada, ponteiro* anterior){
    *anterior = NULL;
    ponteiro atual = sla->inicio;
    while((atual != NULL) && (atual->reg.chave < chavebuscada)){
        *anterior = atual;
        atual = atual->proximo;       
    }
    if((atual != NULL) && (atual->reg.chave == chavebuscada)) return atual;
    return NULL;
}

// finalmente, a inserção ordenada
bool inserirelementollistaordenada(LISTA* sla, REGISTRO reg){
    TIPOCHAVE chave = reg.chave;
    ponteiro anterior, i;
    i = buscasequencialexc(sla, chave, &anterior);
    if(i != NULL) return false;
    i = (ponteiro) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    if(anterior == NULL){ // se ele for o início da lista
        i->proximo = sla->inicio; // o próximo dele se torna o antigo início
        sla->inicio = i; // e ele vira o início
    } else {
        i->proximo = anterior->proximo; // ele fica no lugar do anterior e, portanto, aponta para onde o anterior apontava
        anterior->proximo = i;          // e agora o anterior aponta para ele
    }
    return true;
}

// exclusão de um elemento
// o usuário passa a chave do elemento que quer excluir
// se houver um elemento com essa chave na lista, exclui o elemento, acerta os ponteiros e retorna true
// caso contrário retorna false
// para essa função também precisamos saber o predecessor do elemento a ser excluido
bool excluirelementolista(LISTA* sla, TIPOCHAVE chaveaserexcluída){
    ponteiro anterior, i;
    i = buscasequencialexc(sla, chaveaserexcluída, &anterior);
    if(i == NULL) return false; // se não achou, então retorna falso
    if(anterior == NULL) sla->inicio = i->proximo; // se o anterior é nulo, então ele era o 1° elemento. assim, o início passa a ser o próximo
    else anterior->proximo = i->proximo;           // caso contrário, a gente faz com que o próximo do anterior aponte para o elemento que vem depois do elemento excluído
    free(i); // liberamos a memória do elemento excluído para poder ser inserida dnv
    return true;
}

// por fim, reinicialização da lista
// devemos excluir todos os seus elementos e atualizar o campo início para NULL
void reinicializarlista(LISTA* sla){
    ponteiro endereco = sla->inicio;
    while (endereco != NULL){
        ponteiro apagar = endereco;
        endereco = endereco->proximo;
        free(apagar);
    }
    sla->inicio = NULL;
}