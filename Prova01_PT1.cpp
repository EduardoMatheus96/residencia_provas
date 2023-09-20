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

