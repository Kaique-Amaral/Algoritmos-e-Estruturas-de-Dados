#ifndef LIST_H
#define LIST_H

#include "patient.hpp"

// estrutura do nó da lista encadeada
// cada nó guarda um paciente e aponta pro próximo nó
typedef struct Node {
    Patient patient;
    Node *next;
} Node;

// estrutura da lista
// só precisa guardar o ponteiro pro primeiro nó
typedef struct {
    Node *start;
} List;

// funções para manipular a lista
void initializelist(List *l);           // inicializa a lista vazia
void insertpatient(List *l, Patient p); // insere paciente no início
bool removepatient(List *l, int id);    // remove paciente por id
Patient* findpatient(List *l, int id);  // busca paciente por id
void showlist(List *l);                 // mostra todos os pacientes
void destroylist(List *l);              // libera toda a memória (IMPORTANTE!)

#endif