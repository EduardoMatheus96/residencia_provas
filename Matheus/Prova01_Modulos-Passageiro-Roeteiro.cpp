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