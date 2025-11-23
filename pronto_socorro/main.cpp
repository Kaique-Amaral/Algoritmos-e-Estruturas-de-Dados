#include <iostream>
#include <string>
#include <cctype> // para isdigit e isalpha
#include "patient.hpp"
#include "queue.hpp"
#include "list.hpp"
#include "io.hpp"

using namespace std;

// valida se o nome contém apenas letras e espaços
// retorna true se o nome é válido, false caso contrário
bool validname(const string &name) {
    // nome vazio não é válido
    if (name.empty()) return false;
    
    // verifica se tem pelo menos uma letra
    bool hasLetter = false;
    
    for (char c : name) {
        // permite letras (incluindo acentuadas), espaços e apóstrofos
        // rejeita números e símbolos estranhos
        if (isdigit(c)) {
            return false; // nome não pode ter números
        }
        if (isalpha(c)) {
            hasLetter = true; // encontrou pelo menos uma letra
        }
        // permite espaços e apóstrofos (para nomes como "D'Angelo")
        // mas outros caracteres especiais devem ser aceitos com cuidado
    }
    
    // precisa ter pelo menos uma letra
    return hasLetter;
}

int main() {
    // estruturas principais do sistema
    List patients;       // lista de todos os pacientes cadastrados
    Queue waitingroom;   // fila de espera pro atendimento
    
    // inicializa as estruturas vazias
    initializelist(&patients);
    initializequeue(&waitingroom);
    
    // tenta carregar dados salvos anteriormente
    // primeiro carrega a lista de pacientes (com todo o histórico)
    load(&patients, "patients.txt");
    // depois carrega a fila de espera (reconstrói a ordem de atendimento)
    loadqueue(&waitingroom, &patients, "queue.txt");
    
    int option;
    do {
        // mostra o menu de opções
        cout << "\n--- MENU ---\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Registrar obito do paciente\n";
        cout << "3. Adicionar procedimento\n";
        cout << "4. Desfazer procedimento\n";
        cout << "5. Chamar paciente\n";
        cout << "6. Mostrar fila\n";
        cout << "7. Mostrar historico\n";
        cout << "8. Sair\n";
        cout << "Escolha: ";
        
        // lê a opção com validação
        // se o usuário digitar algo que não é número, pede pra digitar de novo
        while(!(cin >> option)){
            cout << "Entrada invalida! Digite um numero entre 1 e 8: ";
            cin.clear();              // limpa o estado de erro do cin
            cin.ignore(1000, '\n');   // descarta a entrada inválida
        }
        
        // opção 1: registrar um novo paciente
        if (option == 1) {
            int id;
            string name;
            
            cout << "ID: ";
            // valida se o id é um número inteiro
            while (!(cin >> id)) {
                cout << "Entrada invalida! Digite um numero inteiro: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            cin.ignore(); // limpa o buffer antes de ler a linha
            cout << "Nome: ";
            getline(cin, name);
            
            // valida se o nome é válido (não vazio, sem números, etc)
            while(!validname(name)){
                cout << "Nome invalido! O nome deve conter apenas letras e espacos, sem numeros." << endl;
                cout << "Nome: ";
                getline(cin, name);
            }
            
            // verifica se o id já existe no sistema
            if (findpatient(&patients, id) != NULL) {
                cout << "ERRO: ID ja existe!" << endl;
            } else {
                // cria o paciente, adiciona na lista e na fila
                Patient p = createpatient(id, name);
                insertpatient(&patients, p);
                
                if (!enqueue(&waitingroom, p)) {
                    cout << "Fila cheia!" << endl;
                } else {
                    cout << "Paciente registrado e inserido na fila." << endl;
                }
            }
        }
        
        // opção 2: registrar óbito (remove o paciente do sistema)
        else if (option == 2) {
            int id;
            cout << "ID do paciente que veio a obito: ";
            cin >> id;
            
            // REGRA IMPORTANTE: paciente só pode morrer se NÃO estiver na fila
            // se ainda está esperando atendimento, é proibido registrar óbito
            if (isinqueue(&waitingroom, id)) {
                cout << "ERRO: Paciente ainda esta na fila de espera! So e possivel registrar obito apos o atendimento." << endl;
            } else {
                // paciente não está na fila, pode registrar óbito
                if (!removepatient(&patients, id)) {
                    cout << "Paciente nao encontrado!" << endl;
                } else {
                    cout << "Paciente removido com sucesso." << endl;
                }
            }
        }
        
        // opção 3: adicionar um procedimento ao histórico do paciente
        else if (option == 3) {
            int id;
            string proc;
            
            cout << "ID do paciente: ";
            cin >> id;
            cin.ignore(); // limpa o buffer
            cout << "Procedimento: ";
            getline(cin, proc);
            
            // busca o paciente pelo id
            Patient *p = findpatient(&patients, id);
            if (p == NULL) {
                cout << "Paciente nao encontrado!" << endl;
            } else if (!addprocedure(&p->history, proc)) {
                // o histórico tem limite de 10 procedimentos
                cout << "Historico cheio!" << endl;
            } else {
                cout << "Procedimento adicionado." << endl;
            }
        }
        
        // opção 4: desfazer o último procedimento (funciona como pilha)
        else if (option == 4) {
            int id;
            cout << "ID do paciente: ";
            cin >> id;
            
            Patient *p = findpatient(&patients, id);
            if (p == NULL) {
                cout << "Paciente nao encontrado!" << endl;
            } else {
                string proc;
                // remove o procedimento do topo da pilha
                if (!undoProcedure(&p->history, &proc)) {
                    cout << "Historico vazio!" << endl;
                } else {
                    cout << "Procedimento desfeito: " << proc << endl;
                }
            }
        }
        
        // opção 5: chamar o próximo paciente da fila
        else if (option == 5) {
            Patient p;
            // remove o paciente do início da fila (FIFO)
            if (!dequeue(&waitingroom, &p)) {
                cout << "Fila vazia!" << endl;
            } else {
                cout << "Chamando paciente para atendimento: ";
                showpatient(p);
            }
        }
        
        // opção 6: mostrar toda a fila de espera
        else if (option == 6) {
            showqueue(&waitingroom);
        }
        
        // opção 7: mostrar o histórico médico de um paciente
        else if (option == 7) {
            int id;
            cout << "ID do paciente: ";
            cin >> id;
            
            Patient *p = findpatient(&patients, id);
            if (p == NULL) {
                cout << "Paciente nao encontrado!" << endl;
            } else {
                showhistory(&p->history);
            }
        }
        
        // opção 8: sair do programa
        else if (option == 8) {
            cout << "Salvando e saindo..." << endl;
        }
        
        // opção inválida
        else {
            cout << "Opçao invalida!" << endl;
        }
        
    } while (option != 8);
    
    // salva todos os dados antes de encerrar
    save(&patients, "patients.txt");      // salva a lista de pacientes
    savequeue(&waitingroom, "queue.txt"); // salva a fila de espera
    
    // libera toda a memória alocada
    destroylist(&patients);
    
    return 0;
}