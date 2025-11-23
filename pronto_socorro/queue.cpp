// fila circular de atendimento (ordem first in, first out)

// fila circular de tamanho máximo 50 (MAX_QUEUE)
// temos os campos start, end e amount, pra controlar a posição e quantidade
// temos as operações:
// enqueue() pra inserir no final se tiver espaço
// dequeue() pra remover no início (pq é FIFO)
// isinqueue() pra verificar se o paciente está esperando
// removefromqueue() pra remover um paciente específico
// showqueue() imprime fila
#include <iostream>
#include <cassert>
#include "queue.hpp"

using namespace std;

// inicializa a fila circular vazia
// start aponta pro primeiro elemento (quando tiver)
// end aponta pro último elemento (quando tiver)
// amount guarda quantos elementos tem na fila
void initializequeue(Queue *f) {
    if(f == NULL) return;
    
    f->start = 0;      // começa no índice 0
    f->end = -1;       // -1 indica que não tem nenhum elemento ainda
    f->amount = 0;     // quantidade de elementos é zero
    
    // garante que a fila está vazia após a inicialização
    if(!emptyqueue(f)) return;
}

// verifica se a fila está vazia
// se amount é 0, não tem ninguém esperando
bool emptyqueue(Queue *f) {
    if(f == NULL) return false;
    return f->amount == 0;
}

// verifica se a fila está cheia
// o limite é MAX_QUEUE (50 pessoas)
bool fullqueue(Queue *f) {
    if(f == NULL) return false;
    return f->amount == MAX_QUEUE;
}

// adiciona um paciente no final da fila (enfileirar)
// usa estrutura circular: quando chega no final do array, volta pro início
// isso evita ter que deslocar elementos e é mais eficiente
bool enqueue(Queue *f, Patient p) {
    if(f == NULL) return false;
    
    // verifica se ainda tem espaço
    if(fullqueue(f)) return false;
    
    // avança o índice do final de forma circular
    // o operador % faz com que, quando chegar em MAX_QUEUE, volte pra 0
    f->end = (f->end + 1) % MAX_QUEUE;
    
    // coloca o paciente nessa nova posição
    f->patients[f->end] = p;
    
    // incrementa a quantidade de pessoas na fila
    f->amount++;
    
    return true;
}

// remove o primeiro paciente da fila (desenfileirar)
// segue o princípio FIFO (first in, first out)
// quem entrou primeiro é atendido primeiro
bool dequeue(Queue *f, Patient *p) {
    // valida ponteiros e verifica se tem alguém na fila
    if(f == NULL || p == NULL || emptyqueue(f)) return false;
    
    // pega o paciente que está no início da fila
    *p = f->patients[f->start];
    
    // avança o índice de início de forma circular
    f->start = (f->start + 1) % MAX_QUEUE;
    
    // decrementa a quantidade de pessoas na fila
    f->amount--;
    
    return true;
}

// verifica se um paciente com determinado ID está na fila
// usado para impedir óbito de pacientes que ainda não foram atendidos
bool isinqueue(Queue *f, int id) {
    if(f == NULL || emptyqueue(f)) return false;
    
    // percorre toda a fila procurando o ID
    for (int i = 0; i < f->amount; i++) {
        int idx = (f->start + i) % MAX_QUEUE;
        if (f->patients[idx].id == id) {
            return true; // encontrou! está na fila
        }
    }
    
    return false; // não está na fila
}

// remove um paciente específico da fila pelo ID
// isso é necessário quando um paciente vem a óbito
// mais complicado que dequeue porque pode estar em qualquer posição
bool removefromqueue(Queue *f, int id) {
    if(f == NULL || emptyqueue(f)) return false;
    
    // procura o paciente na fila
    int found = -1;
    for (int i = 0; i < f->amount; i++) {
        int idx = (f->start + i) % MAX_QUEUE;
        if (f->patients[idx].id == id) {
            found = i; // guarda a posição relativa onde achou
            break;
        }
    }
    
    // se não encontrou, retorna false
    if (found == -1) return false;
    
    // agora precisa deslocar todos os elementos após o removido
    // para manter a ordem da fila
    for (int i = found; i < f->amount - 1; i++) {
        int currentIdx = (f->start + i) % MAX_QUEUE;
        int nextIdx = (f->start + i + 1) % MAX_QUEUE;
        f->patients[currentIdx] = f->patients[nextIdx];
    }
    
    // ajusta o end (retrocede uma posição de forma circular)
    f->end = (f->end - 1 + MAX_QUEUE) % MAX_QUEUE;
    
    // decrementa a quantidade
    f->amount--;
    
    return true;
}

// mostra toda a fila de espera em ordem
// começa do primeiro (start) até o último (end)
void showqueue(Queue *f) {
    if(f == NULL) return;
    
    if (emptyqueue(f)) {
        cout << "Fila vazia." << endl;
        return;
    }
    
    cout << "Fila de espera:" << endl;
    
    // percorre a fila do início ao fim
    // usa aritmética modular pra lidar com a estrutura circular
    for (int i = 0; i < f->amount; i++) {
        // calcula o índice real no array circular
        int idx = (f->start + i) % MAX_QUEUE;
        showpatient(f->patients[idx]);
    }
}