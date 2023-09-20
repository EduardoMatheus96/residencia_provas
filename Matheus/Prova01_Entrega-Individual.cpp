#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Passageiro {
    string CPF;
    string nome;
    string dtNascimento;
    int numAutorizacao;
};

struct Roteiro {
    int codigo;
    string data_Hora_prevista;
    string duracao_prevista;
    string origem;
    string destino;
};

vector<Passageiro> passageiros;
vector<Roteiro> roteiros;

bool verificarMaiorIdade(const string& dataNascimento) {
    // Função para verificar a maioridade
    int dia, mes, ano;
    sscanf(dataNascimento.c_str(), "%d/%d/%d", &dia, &mes, &ano);

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int anoAtual = now->tm_year + 1900;
    int mesAtual = now->tm_mon + 1;
    int diaAtual = now->tm_mday;

    return (anoAtual - ano > 18) || ((anoAtual - ano == 18) && (mes < mesAtual || (mes == mesAtual && dia <= diaAtual)));
}

void imprimirPassageiro(const Passageiro& passageiro) {
    cout << "Passageiro: " << passageiro.nome << endl;
    cout << "CPF: " << passageiro.CPF << endl;
    cout << "Data de Nascimento: " << passageiro.dtNascimento << endl;
    cout << "Número de Autorizacao: " << passageiro.numAutorizacao << endl;
    cout << endl;
}

void incluirPassageiro() {
    Passageiro passageiro;
    cout << "Insira o nome do passageiro: ";
    cin.ignore();
    getline(cin, passageiro.nome);
    cout << "Insira o CPF do passageiro " << passageiro.nome << ": ";
    cin >> passageiro.CPF;
    cout << "Insira a data de nascimento do passageiro " << passageiro.nome << " (dd/mm/aaaa): ";
    cin >> passageiro.dtNascimento;

    if (verificarMaiorIdade(passageiro.dtNascimento)) {
        cout << "Passageiro maior de idade." << endl;
        passageiro.numAutorizacao = -1;
    } else {
        cout << "Passageiro menor de idade." << endl;
        cout << "Insira o número de autorizacao do passageiro " << passageiro.nome << ": ";
        cin >> passageiro.numAutorizacao;
    }

    passageiros.push_back(passageiro);
}
void excluirPassageiro(const string& cpf) {
    for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
        if (it->CPF == cpf) {
            cout << "O passageiro: " << it->nome << " com o CPF: " << it->CPF << " foi excluído com sucesso!" << endl;
            passageiros.erase(it);
            return;
        }
    }
    cout << "Passageiro não encontrado." << endl;
}

void alterarPassageiro(const string& cpf) {
    for (auto& passageiro : passageiros) {
        if (passageiro.CPF == cpf) {
            int escolha;
            imprimirPassageiro(passageiro);
            do {
                cout << "Qual o campo do passageiro você deseja alterar: " << endl;
                cout << "1. Nome" << endl;
                cout << "2. CPF" << endl;
                cout << "3. Data de nascimento" << endl;
                cout << "Insira sua escolha: ";
                cin >> escolha;
                cin.ignore();

                switch (escolha) {
                    case 1:
                        cout << "Insira o novo nome: ";
                        getline(cin, passageiro.nome);
                        break;
                    case 2:
                        cout << "Insira o novo CPF: ";
                        cin >> passageiro.CPF;
                        break;
                    case 3:
                        cout << "Insira a nova data de nascimento (dd/mm/aaaa): ";
                        cin >> passageiro.dtNascimento;
                        break;
                    default:
                        cout << "Opção inválida." << endl;
                }
            } while (escolha < 1 || escolha > 3);
            imprimirPassageiro(passageiro);
            return;
        }
    }
    cout << "Passageiro não encontrado." << endl;
}

void localizarPassageiro(const string& cpf) {
    for (const Passageiro& passageiro : passageiros) {
        if (passageiro.CPF == cpf) {
            imprimirPassageiro(passageiro);
            return;
        }
    }
    cout << "Passageiro não encontrado." << endl;
}

void listarPassageiros() {
    for (const Passageiro& passageiro : passageiros) {
        imprimirPassageiro(passageiro);
    }
}
void imprimirRoteiro(const Roteiro& roteiro) {
    cout << "Código do Roteiro: " << roteiro.codigo << endl;
    cout << "Data e Hora Prevista: " << roteiro.data_Hora_prevista << endl;
    cout << "Duração Prevista: " << roteiro.duracao_prevista << endl;
    cout << "Origem: " << roteiro.origem << endl;
    cout << "Destino: " << roteiro.destino << endl;
    cout << endl;
}

void incluirRoteiro() {
    Roteiro roteiro;
    cout << "Insira o código do roteiro: ";
    cin >> roteiro.codigo;
    cout << "Insira a data e hora prevista (dd/mm/aaaa hh:mm): ";
    cin.ignore();
    getline(cin, roteiro.data_Hora_prevista);
    cout << "Insira a duração prevista: ";
    getline(cin, roteiro.duracao_prevista);
    cout << "Insira a origem: ";
    getline(cin, roteiro.origem);
    cout << "Insira o destino: ";
    getline(cin, roteiro.destino);

    roteiros.push_back(roteiro);
}
void excluirRoteiro(int codigo) {
    for (auto it = roteiros.begin(); it != roteiros.end(); ++it) {
        if (it->codigo == codigo) {
            cout << "O roteiro com código: " << it->codigo << " foi excluído com sucesso!" << endl;
            roteiros.erase(it);
            return;
        }
    }
    cout << "Roteiro não encontrado." << endl;
}

void alterarRoteiro(int codigo) {
    for (auto& roteiro : roteiros) {
        if (roteiro.codigo == codigo) {
            int escolha;
            imprimirRoteiro(roteiro);
            do {
                cout << "Qual o campo do roteiro você deseja alterar: " << endl;
                cout << "1. Código" << endl;
                cout << "2. Data e Hora Prevista" << endl;
                cout << "3. Duração Prevista" << endl;
                cout << "4. Origem" << endl;
                cout << "5. Destino" << endl;
                cout << "Insira sua escolha: ";
                cin >> escolha;
                cin.ignore();

                switch (escolha) {
                    case 1:
                        cout << "Insira o novo código: ";
                        cin >> roteiro.codigo;
                        break;
                    case 2:
                        cout << "Insira a nova data e hora prevista (dd/mm/aaaa hh:mm): ";
                        getline(cin, roteiro.data_Hora_prevista);
                        break;
                    case 3:
                        cout << "Insira a nova duração prevista: ";
                        getline(cin, roteiro.duracao_prevista);
                        break;
                    case 4:
                        cout << "Insira a nova origem: ";
                        getline(cin, roteiro.origem);
                        break;
                    case 5:
                        cout << "Insira o novo destino: ";
                        getline(cin, roteiro.destino);
                        break;
                    default:
                        cout << "Opção inválida." << endl;
                }
            } while (escolha < 1 || escolha > 5);
            imprimirRoteiro(roteiro);
            return;
        }
    }
    cout << "Roteiro não encontrado." << endl;
}
