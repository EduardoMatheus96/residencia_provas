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
