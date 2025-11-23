#ifndef QUEUE_H
#define QUEUE_H

#include "patient.hpp"

#define MAX_QUEUE 50

typedef struct {
    Patient patients[MAX_QUEUE];
    int start, end, amount;
} Queue;

void initializequeue(Queue *f);        // inicializar fila
bool emptyqueue(Queue *f);             // fila vazia
bool fullqueue(Queue *f);              // fila cheia
bool enqueue(Queue *f, Patient p);     // enfileirar
bool dequeue(Queue *f, Patient *p);    // desenfileirar
void showqueue(Queue *f);              // mostrar fila
bool isinqueue(Queue *f, int id);      // verifica se paciente está na fila
bool removefromqueue(Queue *f, int id); // remove paciente específico da fila

#endif