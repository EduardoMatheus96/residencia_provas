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
    unsigned int numAutorizacao;
};

struct Roteiro
{
    string codigo;
    string dataHoraPrevista;
    string duracaoPrevista;
    string origem;
    string destino;
};

void verificaData(){
    
}

void imprimiPassageiro(Passageiro &passageiro)
{
    cout << "Passageiro :" << passageiro.nome << endl;
    cout << "Cpf: " << passageiro.cpf << endl;
    cout << "Data de Nascimento: " << passageiro.dtNascimento << endl;
    cout << "Número de autorizacao: " << passageiro.numAutorizacao << endl;
    cout << endl;
}

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

void excluir(vector<Passageiro> &passageiros)
{
    string cpf;
    cout << "insira o cpf do passageiro a ser excluido: ";
    cin >> cpf;
    cout << endl;
    for (auto it = passageiros.begin(); it != passageiros.end(); ++it)
    {
        if (it->cpf == cpf)
        {
            cout << "O passageiro: " << it->nome << " Com o cpf: " << it->cpf << " foi excluido com sucesso!" << endl;
            it = passageiros.erase(it);
            break;
        }
    }
    cout << endl;
}
void alterar(vector<Passageiro> &passageiros)
{
    string cpf;
    cout << "insira o cpf do passageiro a ser alterado: ";
    cin >> cpf;
    cout << endl;
    for (auto it = passageiros.begin(); it != passageiros.end(); ++it)
    {
        if (it->cpf == cpf)
        {
            int escolha;
            imprimiPassageiro(*it);
            do
            {
                cout << "Qual o campo do passageiro voce deseja alterar: " << endl;
                cout << "1.Nome" << endl;
                cout << "2.Cpf" << endl;
                cout << "3.Data de nascimento" << endl;
                cout << "Insira sua escolha: ";
                cin >> escolha;
                cout << endl;
                if (escolha == 1)
                {
                    string nome;
                    cout << "Insira o nome: ";
                    cin >> nome;
                    cout << endl;
                    it->nome = nome;
                }
                else if (escolha == 2)
                {
                    string cpf;
                    cout << "Insira o cpf: ";
                    cin >> cpf;
                    cout << endl;
                    it->cpf = cpf;
                }
                else if (escolha == 3)
                {
                    string dataNascimento;
                    cout << "Insira a data de nascimento: ";
                    cin >> dataNascimento;
                    cout << endl;
                    it->dtNascimento = dataNascimento;
                }

            } while (escolha < 1 || escolha > 3);
            imprimiPassageiro(*it);
            break;
        }
    }

    cout << endl;
}
void listar(vector<Passageiro> &passageiros)
{
    for (Passageiro passageiro : passageiros)
    {
        imprimiPassageiro(passageiro);
    }
    
}
void localizar(vector<Passageiro> &passageiros)
{
    string cpf;
    cout << "insira o cpf do passageiro a ser alterado: ";
    cin >> cpf;
    cout << endl;

    for (Passageiro passageiro : passageiros)
    {
        if(passageiro.cpf == cpf)
        {
            imprimiPassageiro(passageiro);
            break;
        }        
    }
    
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
        else if (opcao == 2)
        {
            excluir(passageiros);
        }
        else if (opcao == 3)
        {
            alterar(passageiros);
        } else if (opcao == 4)
        {
            listar(passageiros);
        } else if (opcao == 5)
        {
            localizar(passageiros);
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
