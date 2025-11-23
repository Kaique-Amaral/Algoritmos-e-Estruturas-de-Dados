// objetivo: entrada e saída de arquivos

// save() pra salvar os pacientes, load() pra carregar
// savequeue() e loadqueue() pra salvar e carregar a fila
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <cstdlib>
#include "io.hpp"

using namespace std;

// salva todos os pacientes da lista em um arquivo de texto
// formato: id;nome;proc1|proc2|proc3...
// cada linha representa um paciente
bool save(List *l, const char *filename) {
    if (l == NULL) {
        cout << "lista vazia" << endl;
        return false;
    }
    
    // abre o arquivo pra escrita (cria se não existir, sobrescreve se existir)
    ofstream file(filename);
    if (!file.is_open()) return false;
    
    // percorre toda a lista de pacientes
    Node *curr = l->start;
    while (curr != NULL) {
        // grava id e nome separados por ponto-e-vírgula
        file << curr->patient.id << ";" << curr->patient.name << ";";
        
        // grava o histórico médico
        // os procedimentos são separados por pipe (|)
        for (int i = 0; i <= curr->patient.history.top; i++) {
            file << curr->patient.history.procedures[i];
            // adiciona o separador se não for o último procedimento
            if (i < curr->patient.history.top) file << "|";
        }
        file << "\n"; // pula pra próxima linha (próximo paciente)
        
        curr = curr->next;
    }
    
    file.close();
    return true;
}

// carrega pacientes de um arquivo e reconstrói a lista
// espera o mesmo formato que a função save usa
bool load(List *l, const char *filename) {
    if (l == NULL) {
        cout << "lista vazia" << endl;
        return false;
    }
    
    // tenta abrir o arquivo pra leitura
    ifstream file(filename);
    // se não conseguir abrir (arquivo não existe), retorna false
    // mas isso não é erro grave - o programa pode começar do zero
    if (!file.is_open()) return false;
    
    string line;
    // lê o arquivo linha por linha (cada linha é um paciente)
    while (getline(file, line)) {
        if (line.empty()) continue; // pula linhas vazias
        
        // usa stringstream pra separar os campos
        stringstream ss(line);
        string idStr, name, historyStr;
        
        // separa os 3 campos principais: id, nome e histórico
        getline(ss, idStr, ';');      // lê até o primeiro ;
        getline(ss, name, ';');       // lê até o segundo ;
        getline(ss, historyStr);      // lê o resto da linha
        
        // converte o id de string pra int
        int id = atoi(idStr.c_str());
        
        // cria o paciente com id e nome
        Patient p = createpatient(id, name);
        
        // se houver histórico, processa os procedimentos
        if (!historyStr.empty()) {
            stringstream hs(historyStr);
            string proc;
            // separa os procedimentos pelo caractere pipe (|)
            while (getline(hs, proc, '|')) {
                addprocedure(&p.history, proc);
            }
        }
        
        // adiciona o paciente na lista
        insertpatient(l, p);
    }
    
    file.close();
    return true;
}

// salva a fila de espera em um arquivo
// formato simples: cada linha contém apenas o ID de um paciente
// a ordem das linhas representa a ordem da fila
bool savequeue(Queue *q, const char *filename) {
    if (q == NULL) {
        cout << "fila invalida" << endl;
        return false;
    }
    
    ofstream file(filename);
    if (!file.is_open()) return false;
    
    // percorre a fila do início ao fim
    // salva apenas os IDs porque os dados completos já estão em patients.txt
    for (int i = 0; i < q->amount; i++) {
        int idx = (q->start + i) % MAX_QUEUE;
        file << q->patients[idx].id << "\n";
    }
    
    file.close();
    return true;
}

// carrega a fila de espera de um arquivo
// reconstrói a fila pegando os pacientes completos da lista
// isso garante que a fila tem as versões mais atualizadas dos pacientes
bool loadqueue(Queue *q, List *l, const char *filename) {
    if (q == NULL || l == NULL) {
        cout << "fila ou lista invalida" << endl;
        return false;
    }
    
    ifstream file(filename);
    // se o arquivo não existir, não é erro - apenas começa com fila vazia
    if (!file.is_open()) return false;
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // converte o ID de string pra int
        int id = atoi(line.c_str());
        
        // procura o paciente na lista principal
        Patient *p = findpatient(l, id);
        
        // se o paciente ainda existe na lista, adiciona na fila
        // se não existir (foi removido), simplesmente ignora
        if (p != NULL) {
            if (!enqueue(q, *p)) {
                cout << "Erro ao enfileirar paciente " << id << endl;
            }
        }
    }
    
    file.close();
    return true;
}