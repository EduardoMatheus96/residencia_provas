#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Passageiro
{
    string cpf;
    string nome;
    string dtNascimento;
    int numAutorizacao;
};

struct Roteiro
{
    string codigo;
    string dataHoraPrevista;
    string duracaoPrevista;
    string origem;
    string destino;
};

void incluir(vector<Passageiro> &passageiros)
{
    Passageiro passageiro;
    cout << "Insira o nome do passageiro: ";
    cin >> passageiro.nome;
    cout << endl;
    cout << "Insira o cpf do passageiro " << passageiro.nome << ": ";
    cin >> passageiro.cpf;
    cout << endl;
    cout << "Insira a data de nascimento do passageiro " << passageiro.nome << ": ";
    cin >> passageiro.dtNascimento;
    cout << endl;
    cout << "Insira o número de autorizacao do passageiro " << passageiro.nome << ": ";
    cin >> passageiro.numAutorizacao;
    cout << endl;

    passageiros.push_back(passageiro);
}

void excluir(vector<Passageiro> &passageiros, string cpf)
{
    for (auto it = passageiros.begin(); it != passageiros.end(); ++it)
    {
        if (it->cpf == cpf)
        {
            cout << "O passageiro: " << it->nome << " Com o cpf: " << it->cpf << " foi excluido com sucesso!" << endl;
            it = passageiros.erase(it);
            break;
        }
        
    }
}
void alterar(vector<Passageiro> &passageiros)
{
    cout << "ALTERARRR " << endl;
}
void listar(vector<Passageiro> &passageiros)
{
    cout << "LISTARRRR " << endl;
}
void localizar(vector<Passageiro> &passageiros)
{
    cout << "LOCALIZARRR " << endl;
}

vector<string> menuNomes = {
    "Incluir.",
    "Excluir.",
    "Alterar ( Apenas CPF ).",
    "Listar.",
    "Localizar ( Pelo CPF ).",
};

void menuOpcoes()
{
    vector<Passageiro> passageiros;
    int opcao;
    do
    {
        cout << "Menu opcões: " << endl;
        for (int i = 0; i < menuNomes.size(); i++)
        {
            cout << i + 1 << ". " << menuNomes[i] << endl;
        }
        cout << "0. Sair" << endl;
        cout << "Insira sua escolha: ";
        cin >> opcao;
        cout << endl;

        if (opcao == 1)
        {
            incluir(passageiros);
        }
        else if (opcao != 0)
        {
            cout << "Escolha inválida. Por favor, tente novamente." << endl;
        }

    } while (opcao);
}

int main()
{
    menuOpcoes();

    return 0;
}
