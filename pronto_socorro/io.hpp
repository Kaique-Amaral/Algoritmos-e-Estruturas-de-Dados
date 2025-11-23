#ifndef IO_H
#define IO_H

#include "list.hpp"
#include "queue.hpp"

// salva todos os pacientes da lista em disco
bool save(List *l, const char *filename);

// carrega pacientes do disco para a lista
bool load(List *l, const char *filename);

// salva a fila de espera em disco
bool savequeue(Queue *q, const char *filename);

// carrega a fila de espera do disco
bool loadqueue(Queue *q, List *l, const char *filename);

#endif