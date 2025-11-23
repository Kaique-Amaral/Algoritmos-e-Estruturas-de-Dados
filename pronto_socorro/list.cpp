// lista encadeada de pacientes (banco principal)

// é uma lista encadeada simples
// é epra guardar todos os pacientes existentes (vivos ou não atendidos)

// as operações são:
// insertpatient() pra inserir o paciente no início
// removepatient() pra buscar o paciente e remover por ID
// findpatient() pra buscar e retornar o ponteiro do paciente
// destroylist() pra liberar memória
// showlist() pra imprimir todos os pacientes
#include <iostream>
#include <cassert>
#include <cstdlib>
#include "list.hpp"

using namespace std;

// inicializa a lista deixando ela vazia
// basicamente só faz o ponteiro de início apontar pra nulo
void initializelist(List *l) {
    if(l == NULL){
        cout << "Lista inválida!" << endl;
        return;
    }
    l->start = NULL;
}

// insere um novo paciente no início da lista
// sempre insere no começo porque é mais rápido - complexidade O(1)
void insertpatient(List *l, Patient p) {
    if(l == NULL){
        cout << "Lista inválida!" << endl;
        return;
    }
    
    // aloca memória para o novo nó usando new (operador do c++)
    Node *newNode = new Node();
    assert(newNode != NULL); // garante que a alocação funcionou
    
    // copia os dados do paciente pro novo nó
    newNode->patient = p;
    
    // faz o novo nó apontar pro antigo início da lista
    newNode->next = l->start;
    
    // atualiza o início da lista pra ser o novo nó
    l->start = newNode;
}

// remove um paciente da lista procurando pelo id
// percorre a lista até achar o id ou chegar no final
bool removepatient(List *l, int id) {
    if(l == NULL){
        cout << "Lista inválida!" << endl;
        return false;
    }
    
    Node *curr = l->start;  // ponteiro que vai percorrer a lista
    Node *prev = NULL;      // guarda o nó anterior pra poder fazer a "ponte"
    
    // procura o paciente com o id desejado
    while (curr != NULL && curr->patient.id != id) {
        prev = curr;
        curr = curr->next;
    }
    
    // se chegou no final sem achar, retorna false
    if (curr == NULL) return false;
    
    // agora vamos remover o nó encontrado
    // se o nó a remover é o primeiro da lista
    if (prev == NULL) {
        l->start = curr->next;
    } 
    // se está no meio ou final da lista
    else {
        prev->next = curr->next; // faz a "ponte" pulando o nó atual
    }
    
    // CORREÇÃO: estava usando free(), pq antes eu tava usando malloc
    // mas como alocamos com new agora, então a gente usa delete
    delete curr;
    
    return true;
}

// procura um paciente pelo id e retorna um ponteiro pra ele
// útil quando você quer acessar/modificar o paciente sem remover
Patient* findpatient(List *l, int id) {
    if(l == NULL){
        cout << "Lista inválida!" << endl;
        return NULL;
    }
    
    Node *curr = l->start;
    
    // percorre a lista procurando o id
    while (curr != NULL) {
        if (curr->patient.id == id) {
            // achou! retorna o endereço do paciente
            return &(curr->patient);
        }
        curr = curr->next;
    }
    
    // não encontrou
    return NULL;
}

// mostra todos os pacientes cadastrados na lista
void showlist(List *l) {
    if(l == NULL){
        cout << "Lista inválida!" << endl;
        return;
    }
    
    Node *curr = l->start;
    
    // verifica se a lista está vazia
    if (curr == NULL) {
        cout << "Nenhum paciente registrado." << endl;
        return;
    }
    
    cout << "Lista de pacientes:" << endl;
    
    // percorre toda a lista mostrando cada paciente
    while (curr != NULL) {
        showpatient(curr->patient);
        curr = curr->next;
    }
}

// essencial chamar isso antes de encerrar o programa
// se não chamar, vai vazar memória!
void destroylist(List *l) {
    if(l == NULL) return;
    
    Node *curr = l->start;
    
    // percorre a lista liberando cada nó
    while (curr != NULL) {
        Node *temp = curr;      // guarda o nó atual
        curr = curr->next;      // avança pro próximo
        delete temp;            // libera o nó guardado
    }
    
    // marca a lista como vazia
    l->start = NULL;
}