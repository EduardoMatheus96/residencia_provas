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

void ExcluirPassageiro(vector<passageiro> &dadosPassageiros) {
    char excluirPassageiro = 's';
    while (excluirPassageiro == 's') {
        cout << "Deseja excluir algum Passageiro (s/n)? ";
        cin >> excluirPassageiro;

        if (excluirPassageiro == 's') {
            string CPFParaExcluir;
            cout << "Digite o CPF do Passageiro a ser excluído: ";
            cin.ignore();
            getline(cin, CPFParaExcluir);

            for (size_t i = 0; i < dadosPassageiros.size(); ++i) {
                if (dadosPassageiros[i].CPF == CPFParaExcluir) {
                    dadosPassageiros.erase(dadosPassageiros.begin() + i);
                    cout << "Passageiro excluído com sucesso." << endl;
                    break;
                }
            }
        }
    }
}

void AlterarPassageiro(vector<passageiro> &dadosPassageiros) {
    char alterarNome;
    do {
        cout << "Deseja fazer alteracao (s/n)? ";
        cin >> alterarNome;

        if (alterarNome == 's') {
            string CPFbuscar;
            cout << "Digite o CPF do Passageiro cujo nome será alterado: ";
            cin.ignore(); 
            getline(cin, CPFbuscar);

            // Iterar pelos passageiros e procurar pelo CPF
            for (size_t i = 0; i < dadosPassageiros.size(); ++i) {
                if (dadosPassageiros[i].CPF == CPFbuscar) {
                    int index = i; // Índice do passageiro encontrado

                    cout << "Dados atuais do Passageiro " << dadosPassageiros[index].Nome << ": "
                         << dadosPassageiros[index].DtNascimento << " : " << dadosPassageiros[index].NumAutorizacao
                         << " : " << dadosPassageiros[index].CPF << endl;

                    char opcao;
                    do {
                        cout << "Alterar o nome (1), Data de Nascimento (2), CPF (3), Numero de Autorizacao (4)? ou Nenhuma alteracao(0): ";
                        cin >> opcao;

                        cin.ignore();

                        if (opcao == '1') {
                            cout << "Digite o nome correto: ";
                            getline(cin, dadosPassageiros[index].Nome);
                        } else if (opcao == '2') {
                            cout << "Digite a Data de Nascimento Correta: ";
                            getline(cin, dadosPassageiros[index].DtNascimento);
                        } else if (opcao == '3') {
                            cout << "Digite o CPF Correto: ";
                            getline(cin, dadosPassageiros[index].CPF);
                        } else if (opcao == '4') {
                            cout << "Digite o numero de autorizacao Correto: ";
                            getline(cin, dadosPassageiros[index].NumAutorizacao);
                        } else if (opcao != '0') {
                            cout << "Opção inválida. Use '1', '2', '3', '4' ou '0'." << endl;
                        }
                    } while (opcao != '0');

                    cout << "Dados atualizados do passageiro " << dadosPassageiros[index].Nome << ": "
                         << dadosPassageiros[index].CPF << " : " << dadosPassageiros[index].DtNascimento << " : "
                         << dadosPassageiros[index].NumAutorizacao << endl;
                    break;
                }
            }
        }
    } while (alterarNome == 's');
}