#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

#define MAX_HISTORY 10
#define MAX_TEXT 100

typedef struct {
    string procedures[MAX_HISTORY]; 
    int top; // índice do topo da pilha
} History;

typedef struct {
    int id; 
    string name;
    History history;
} Patient;

// funções relacionadas ao paciente 
Patient createpatient(int id, string name);
void showpatient(Patient p);

// funções relacionadas ao histórico médico (pilha dentro do paciente)
void initializehistory(History *h);
bool historyempty(History *h);
bool historyfull(History *h);
bool addprocedure(History *h, string proc);
bool undoProcedure(History *h, string *proc);
void showhistory(History *h);

#endif
