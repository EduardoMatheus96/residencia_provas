#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

struct Passageiro
{
    string nome;
    string cpf;
    string dataNascimento;
    int numAutorizacao;
    /*
    bool operator<(const Passageiro &passageiro) const
    {
        return nome < passageiro.nome;
    }

    bool operator==(const Passageiro &passageiro) const
    {
        return cpf == passageiro.cpf;
    }
    */
};

struct Roteiro
{
    string codigo;
    string dataHoraPrevista;
    string duracaoPrevista;
    string origem;
    string destino;

    /*
    bool operator<(const Roteiro &roteiro) const
    {
        return codigo < roteiro.codigo;
    }
    */
};

vector<Passageiro> passageiros;
vector<Roteiro> roteiros;

bool maiorIdade(string dataNascimento)
{
    
    int dia, mes, ano;
    sscanf(dataNascimento.c_str(), "%d/%d/%d", &dia, &mes, &ano);

    
    time_t now = time(0);
    tm *localTime = localtime(&now);
    int anoAtual = localTime->tm_year + 1900; // tm_year retorna o ano desde 1900

    // Calcular a idade
    int idade = anoAtual - ano;

    // Verificar se a pessoa é maior ou menor de idade
    if (idade >= 18)
    {
        return true; // Maior de idade
    }
    else
    {
        cout << "O passageiro e menor de idade sera necessario autorizacao" << endl;
        return false; // Menor de idade
    }
}

void incluirPassageiro()
{
    Passageiro passageiro;
    int dia, mes, ano;
    cout << "Digite o nome do passageiro: ";
    getline(cin, passageiro.nome);
    cout << "Digite o CPF do passageiro: ";
    getline(cin, passageiro.cpf);
    cout << "Digite a data de nascimento do passageiro: ";
    getline(cin, passageiro.dataNascimento);
    maiorIdade(passageiro.dataNascimento);

    cout << "Digite o codigo de autorizacao: ";
    cin >> passageiro.numAutorizacao;
    cin.ignore();
    passageiros.push_back(passageiro);
}

void excluirPassageiro()
{
    string cpf;
    cout << "CPF: ";
    getline(cin, cpf);
    for (float i = 0; i < passageiros.size(); i++)
    {
        if (passageiros[i].cpf == cpf)
        {
            passageiros.erase(passageiros.begin() + i);
            cout << "Passageiro excluido com sucesso!" << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado!" << endl;
}

void alterarPassageiro()
{
    string cpf;
    cout << "CPF: ";
    getline(cin, cpf);
    for (float i = 0; i < passageiros.size(); i++)
    {
        if (passageiros[i].cpf == cpf)
        {
            cout << "Nome: ";
            getline(cin, passageiros[i].nome);
            cout << "CPF: ";
            getline(cin, passageiros[i].cpf);
            cout << "Data de Nascimento: ";
            getline(cin, passageiros[i].dataNascimento);
            cout << "numAutorizacao: ";
            cin >> passageiros[i].numAutorizacao;
            cin.ignore();
            cout << "Passageiro alterado com sucesso!" << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado!" << endl;
}

void listarpassageiros()
{
    cout << "passageiros:" << endl;
    for (int i = 0; i < passageiros.size(); i++)
    {
        cout << "Nome: " << passageiros[i].nome << endl;
        cout << "CPF: " << passageiros[i].cpf << endl;
        cout << "Data de Nascimento: " << passageiros[i].dataNascimento << endl;
        cout << "numAutorizacao: " << passageiros[i].numAutorizacao << endl;
        cout << endl;
    }
}

void localizarPassageiro()
{
    string cpf;
    cout << "CPF: ";
    getline(cin, cpf);
    for (int i = 0; i < passageiros.size(); i++)
    {
        if (passageiros[i].cpf == cpf)
        {
            cout << "Nome: " << passageiros[i].nome << endl;
            cout << "CPF: " << passageiros[i].cpf << endl;
            cout << "Data de Nascimento: " << passageiros[i].dataNascimento << endl;
            cout << "numAutorizacao: " << passageiros[i].numAutorizacao << endl;
            cout << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado!" << endl;
}

void incluirRoteiro()
{
    Roteiro roteiro;
    cout << "Codigo: ";
    getline(cin, roteiro.codigo);
    cout << "Data e Hora Prevista: ";
    getline(cin, roteiro.dataHoraPrevista);
    cout << "Duracao Prevista: ";
    getline(cin, roteiro.duracaoPrevista);
    cout << "Origem: ";
    getline(cin, roteiro.origem);
    cout << "Destino: ";
    getline(cin, roteiro.destino);
    roteiros.push_back(roteiro);
}

void excluirRoteiro()
{
    string codigo;
    cout << "Codigo: ";
    getline(cin, codigo);
    for (int i = 0; i < roteiros.size(); i++)
    {
        if (roteiros[i].codigo == codigo)
        {
            roteiros.erase(roteiros.begin() + i);
            cout << "Roteiro excluido com sucesso!" << endl;
            return;
        }
    }
    cout << "Roteiro nao encontrado!" << endl;
}

void alterarRoteiro()
{
    string codigo;
    cout << "Codigo: ";
    getline(cin, codigo);
    for (int i = 0; i < roteiros.size(); i++)
    {
        if (roteiros[i].codigo == codigo)
        {
            cout << "Codigo: ";
            getline(cin, roteiros[i].codigo);
            cout << "Data e Hora Prevista: ";
            getline(cin, roteiros[i].dataHoraPrevista);
            cout << "Duracao Prevista: ";
            getline(cin, roteiros[i].duracaoPrevista);
            cout << "Origem: ";
            getline(cin, roteiros[i].origem);
            cout << "Destino: ";
            getline(cin, roteiros[i].destino);
            cout << "Roteiro alterado com sucesso!" << endl;
            return;
        }
    }
    cout << "Roteiro nao encontrado!" << endl;
}

void listarroteiros()
{
    cout << "roteiros:" << endl;
    for (int i = 0; i < roteiros.size(); i++)
    {
        cout << "Codigo: " << roteiros[i].codigo << endl;
        cout << "Data e Hora Prevista: " << roteiros[i].dataHoraPrevista << endl;
        cout << "Duracao Prevista: " << roteiros[i].duracaoPrevista << endl;
        cout << "Origem: " << roteiros[i].origem << endl;
        cout << "Destino: " << roteiros[i].destino << endl;
        cout << endl;
    }
}

void localizarRoteiro()
{
    string codigo;
    cout << "Codigo: ";
    getline(cin, codigo);
    for (int i = 0; i < roteiros.size(); i++)
    {
        if (roteiros[i].codigo == codigo)
        {
            cout << "Codigo: " << roteiros[i].codigo << endl;
            cout << "Data e Hora Prevista: " << roteiros[i].dataHoraPrevista << endl;
            cout << "Duracao Prevista: " << roteiros[i].duracaoPrevista << endl;
            cout << "Origem: " << roteiros[i].origem << endl;
            cout << "Destino: " << roteiros[i].destino << endl;
            cout << endl;
            return;
        }
    }
    cout << "Roteiro nao encontrado!" << endl;
}

// Criar menu que interligue os dois menus

int main()
{
    int opcao = -1;
    while (opcao != 0)
    {
        cout << "1. Passageiros" << endl;
        cout << "2. Roteiros" << endl;
        cout << "0. Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();
        cout << endl;
        switch (opcao)
        {
        case 1:
        {
            int opcaoPassageiro = -1;
            while (opcaoPassageiro != 0)
            {
                cout << "1. Incluir" << endl;
                cout << "2. Excluir" << endl;
                cout << "3. Alterar" << endl;
                cout << "4. Listar" << endl;
                cout << "5. Localizar" << endl;
                cout << "0. Sair" << endl;
                cout << "Opcao: ";
                cin >> opcaoPassageiro;
                cin.ignore();
                cout << endl;
                switch (opcaoPassageiro)
                {
                case 1:
                    incluirPassageiro();
                    break;
                case 2:
                    excluirPassageiro();
                    break;
                case 3:
                    alterarPassageiro();
                    break;
                case 4:
                    listarpassageiros();
                    break;
                case 5:
                    localizarPassageiro();
                    break;
                case 0:
                    cout << "Saindo..." << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
                    break;
                }
                cout << endl;
            }
            break;
        }
        case 2:
        {
            int opcaoRoteiro = -1;
            while (opcaoRoteiro != 0)
            {
                cout << "1. Incluir" << endl;
                cout << "2. Excluir" << endl;
                cout << "3. Alterar" << endl;
                cout << "4. Listar" << endl;
                cout << "5. Localizar" << endl;
                cout << "0. Sair" << endl;
                cout << "Opcao: ";
                cin >> opcaoRoteiro;
                cin.ignore();
                cout << endl;
                switch (opcaoRoteiro)
                {
                case 1:
                    incluirRoteiro();
                    break;
                case 2:
                    excluirRoteiro();
                    break;
                case 3:
                    alterarRoteiro();
                    break;
                case 4:
                    listarroteiros();
                    break;
                case 5:
                    localizarRoteiro();
                    break;
                case 0:
                    cout << "Saindo..." << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
                    break;
                }
                cout << endl;
            }
            break;
        }
        case 0:
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
        }
        cout << endl;
    }
    return 0;
}

// Path: Revisão_do_Codigo_01.cpp