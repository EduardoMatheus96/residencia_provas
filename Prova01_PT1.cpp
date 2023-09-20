#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

struct passageiro
{
    string CPF;
    string Nome;
    string DtNascimento;
    string NumAutorizacao;
};

struct roteiro
{
    string Codigo;
    string Data_Hora;
    string Duracao;
    string Origem;
    string Destino;
};

bool MaiorIdade(const string DtNascimento) {
    // Obter a data atual
    time_t now;
    time(&now);
    tm t = *gmtime(&now);

    // Extrair o ano, mês e dia da data de nascimento
    int anoNascimento = stoi(DtNascimento.substr(6, 4));
    int mesNascimento = stoi(DtNascimento.substr(3, 2));
    int diaNascimento = stoi(DtNascimento.substr(0, 2));

    // Calcular a idade
    int anoAtual = t.tm_year + 1900;
    int mesAtual = t.tm_mon + 1;
    int diaAtual = t.tm_mday;

    int idade = anoAtual - anoNascimento;

    // Verificar se o aniversário já ocorreu este ano
    if (mesAtual < mesNascimento || (mesAtual == mesNascimento && diaAtual < diaNascimento)) {
        idade--;
    }

    // Verificar se a idade é menor ou igual a 18 anos
    return idade <= 18;
}

void IncluirPassageiro(vector<passageiro> &dadosPassageiros){
    passageiro temp;
    cout << "Digite o Nome do Passageiro: " <<endl;
    cin >> temp.Nome;
    cout << "Digite o CPF do Passageiro sem caracteres: " << endl;
    cin >> temp.CPF;
    cout << "Digite a Data de Nascimento (formato: DD/MM/AAAA): " << endl;
    cin >> temp.DtNascimento;    
    if(MaiorIdade(temp.DtNascimento)){
        cout << "Digite o numero de autorizacao: "<< endl;
        cin >> temp.NumAutorizacao;
    }
    dadosPassageiros.push_back(temp);
}

