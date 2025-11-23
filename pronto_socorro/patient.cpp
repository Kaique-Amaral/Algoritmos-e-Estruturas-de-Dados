// patient.cpp
// objetivo: definir o paciente e o histórico (pilha)

// cada paciente tem um id e nome
// e o histórico, que é uma pilha com no máximo 10 procedimentos (MAX_HISTORY)

// os principais procedimentos são o addprocedure(), pra empilhar um procedimento
// undoprocedure(), pra desempilhar um procedimento
// e showhistory(), pra exibir do mais recente ao mais antigo
#include <iostream>
#include "patient.hpp"

using namespace std;

// cria um novo paciente com id e nome
// retorna um paciente com histórico vazio já inicializado
Patient createpatient(int id, string name) {
    // valida se o nome não está vazio
    if(name.empty()) {
        Patient erro;
        erro.id = -1;  // usa -1 como indicador de erro
        return erro;
    }
    
    Patient p;
    p.id = id;
    p.name = name;
    initializehistory(&p.history);  // começa com histórico vazio
    return p;
}

// mostra as informações básicas do paciente (id e nome)
// não mostra o histórico aqui, só os dados principais
void showpatient(Patient p) {
    if(p.name.empty()){
        cout << "Paciente inválido!" << endl;
        return;
    }
    cout << "Paciente ID: " << p.id << ", Nome: " << p.name << endl;
}

// inicializa o histórico médico (que funciona como uma pilha)
// top = -1 significa que a pilha está vazia
void initializehistory(History *h) {
    if(h == NULL){
        cout << "Historico não encontrado!" << endl;
        return;
    }
    h->top = -1;  // -1 indica pilha vazia
}

// verifica se o histórico está vazio
// se top é -1, não tem nenhum procedimento registrado
bool historyempty(History *h) {
    if(h == NULL){
        cout << "Historico não encontrado!" <<  endl;
        return false;
    }
    return h->top == -1;
}

// verifica se o histórico está cheio
// o limite é MAX_HISTORY (10 procedimentos)
// se top chegou em 9 (índice do último elemento), está cheio
bool historyfull(History *h) {
    if(h == NULL){
        cout << "Historico não encontrado!" << endl;
        return false;
    }
    return h->top == MAX_HISTORY - 1;
}

// adiciona um novo procedimento ao histórico (push na pilha)
// o procedimento é adicionado no topo da pilha
// retorna false se o histórico já estiver cheio
bool addprocedure(History *h, string proc) {
    if(h == NULL){
        cout << "Historico não encontrado!" << endl;
        return false;
    }
    
    // verifica se ainda tem espaço
    if (historyfull(h)) return false;
    
    // valida se o procedimento não está vazio
    if(proc.empty()){
        cout << "Procedimento inválido!" << endl;
        return false;
    }
    
    // incrementa o topo e adiciona o procedimento
    h->top++;
    h->procedures[h->top] = proc;
    
    return true;
}

// remove o último procedimento adicionado (pop da pilha)
// funciona como "desfazer" - sempre remove o mais recente
// retorna o procedimento removido via ponteiro
bool undoProcedure(History *h, string *proc) {
    if(h == NULL || proc == NULL){
        cout << "Historico e/ou procedimentos não encontrados!" << endl;
        return false;
    }
    
    // verifica se tem algo pra remover
    if (historyempty(h)) return false;
    
    // pega o procedimento do topo e decrementa o índice
    *proc = h->procedures[h->top];
    h->top--;
    
    return true;
}

// mostra todo o histórico médico do paciente
// exibe do mais recente (topo) pro mais antigo (base)
void showhistory(History *h) {
    if(h == NULL){
        cout << "Historico não encontrado!" << endl;
        return;
    }
    
    if (historyempty(h)) {
        cout << "Historico vazio." << endl;
        return;
    }
    
    cout << "Historico medico:" << endl;
    // percorre do topo (mais recente) até a base (mais antigo)
    for (int i = h->top; i >= 0; i--) {
        cout << "- " << h->procedures[i] << endl;
    }
}