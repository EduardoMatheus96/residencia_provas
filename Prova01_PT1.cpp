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

void ListarPassageiro(vector<passageiro> dadosPassageiros) {
    for (size_t i = 0; i < dadosPassageiros.size(); i++)
    {
        cout << "CPF: " << dadosPassageiros[i].CPF << endl;
        cout << "Nome: " << dadosPassageiros[i].Nome << endl;
        cout << "Data de Nascimento: " << dadosPassageiros[i].DtNascimento << endl;
        cout << "Numero de  Autorizacao: " << dadosPassageiros[i].NumAutorizacao << endl;
        cout << endl << endl;
    }

}

void LocalizarPassageiro(vector<passageiro> dadosPassageiros){
    string CPFbuscar;
    cout << "Digite o CPF do Passageiro cujo nome será alterado: ";
    cin.ignore();
    getline(cin, CPFbuscar);

    for (size_t i = 0; i < dadosPassageiros.size(); ++i) {
        if (dadosPassageiros[i].CPF == CPFbuscar) {
            int index = i; // Índice do passageiro encontrado

            cout << "Dados do Passageiro " << dadosPassageiros[index].Nome << ": "
            << dadosPassageiros[index].DtNascimento << " : " << dadosPassageiros[index].NumAutorizacao
            << " : " << dadosPassageiros[index].CPF << endl;
        }
    }
}

void IncluirRoteiro(vector<roteiro> &dadosRoteiros) {
    roteiro temp;
    cout << "Digite o Codigo do Roteiro: " << endl;
    cin >> temp.Codigo;
    cout << "Digite a Data e Hora (formato: DD/MM/AAAA HH:MM): " << endl;
    cin.ignore();
    getline(cin, temp.Data_Hora);
    cout << "Digite a Duracao: " << endl;
    getline(cin, temp.Duracao);
    cout << "Digite a Origem: " << endl;
    getline(cin, temp.Origem);
    cout << "Digite o Destino: " << endl;
    getline(cin, temp.Destino);
    dadosRoteiros.push_back(temp);
}

void ExcluirRoteiro(vector<roteiro> &dadosRoteiros) {
    char excluirRoteiro = 's';
    while (excluirRoteiro == 's') {
        cout << "Deseja excluir algum Roteiro (s/n)? ";
        cin >> excluirRoteiro;

        if (excluirRoteiro == 's') {
            string CodigoParaExcluir;
            cout << "Digite o Codigo do Roteiro a ser excluído: ";
            cin.ignore();
            getline(cin, CodigoParaExcluir);

            for (size_t i = 0; i < dadosRoteiros.size(); ++i) {
                if (dadosRoteiros[i].Codigo == CodigoParaExcluir) {
                    dadosRoteiros.erase(dadosRoteiros.begin() + i);
                    cout << "Roteiro excluído com sucesso." << endl;
                    break; 
                }
            }
        }
    }
}

void AlterarRoteiro(vector<roteiro> &dadosRoteiros) {
    char alterarRoteiro;
    do {
        cout << "Deseja fazer alteracao (s/n)? ";
        cin >> alterarRoteiro;

        if (alterarRoteiro == 's') {
            string CodigoBuscar;
            cout << "Digite o Codigo do Roteiro cujo nome será alterado: ";
            cin.ignore();
            getline(cin, CodigoBuscar);

            // Iterar pelos roteiros e procurar pelo Codigo
            for (size_t i = 0; i < dadosRoteiros.size(); ++i) {
                if (dadosRoteiros[i].Codigo == CodigoBuscar) {
                    int index = i; // Índice do roteiro encontrado

                    cout << "Dados atuais do Roteiro " << dadosRoteiros[index].Codigo << ": "
                         << dadosRoteiros[index].Data_Hora << " : " << dadosRoteiros[index].Duracao
                         << " : " << dadosRoteiros[index].Origem << " : " << dadosRoteiros[index].Destino << endl;

                    char opcao;
                    do {
                        cout << "Alterar o Codigo (1), Data e Hora (2), Duracao (3), Origem (4), Destino (5)? ou Nenhuma alteracao(0): ";
                        cin >> opcao;

                        cin.ignore(); // Limpa o buffer após a leitura de opcao

                        if (opcao == '1') {
                            cout << "Digite o Codigo correto: ";
                            getline(cin, dadosRoteiros[index].Codigo);
                        } else if (opcao == '2') {
                            cout << "Digite a Data e Hora Corretos (formato: DD/MM/AAAA HH:MM): ";
                            getline(cin, dadosRoteiros[index].Data_Hora);
                        } else if (opcao == '3') {
                            cout << "Digite a Duracao Correta: ";
                            getline(cin, dadosRoteiros[index].Duracao);
                        } else if (opcao == '4') {
                            cout << "Digite a Origem Correta: ";
                            getline(cin, dadosRoteiros[index].Origem);
                        } else if (opcao == '5') {
                            cout << "Digite o Destino Correto: ";
                            getline(cin, dadosRoteiros[index].Destino);
                        } else if (opcao != '0') {
                            cout << "Opção inválida. Use '1', '2', '3', '4', '5' ou '0'." << endl;
                        }
                    } while (opcao != '0');

                    cout << "Dados atualizados do roteiro " << dadosRoteiros[index].Codigo << ": "
                         << dadosRoteiros[index].Data_Hora << " : " << dadosRoteiros[index].Duracao << " : "
                         << dadosRoteiros[index].Origem << " : " << dadosRoteiros[index].Destino << endl;
                    break;
                }
            }
        }
    } while (alterarRoteiro == 's');
}

void ListarRoteiro(vector<roteiro> dadosRoteiros) {
    for (size_t i = 0; i < dadosRoteiros.size(); i++) {
        cout << "Codigo: " << dadosRoteiros[i].Codigo << endl;
        cout << "Data e Hora: " << dadosRoteiros[i].Data_Hora << endl;
        cout << "Duracao: " << dadosRoteiros[i].Duracao << endl;
        cout << "Origem: " << dadosRoteiros[i].Origem << endl;
        cout << "Destino: " << dadosRoteiros[i].Destino << endl;
        cout << endl << endl;
    }
}

void LocalizarRoteiro(vector<roteiro> dadosRoteiros) {
    string CodigoBuscar;
    cout << "Digite o Codigo do Roteiro cujo nome será alterado: ";
    cin.ignore(); // Limpa o buffer
    getline(cin, CodigoBuscar);

    for (size_t i = 0; i < dadosRoteiros.size(); ++i) {
        if (dadosRoteiros[i].Codigo == CodigoBuscar) {
            int index = i; // Índice do roteiro encontrado

            cout << "Dados do Roteiro " << dadosRoteiros[index].Codigo << ": "
                 << dadosRoteiros[index].Data_Hora << " : " << dadosRoteiros[index].Duracao
                 << " : " << dadosRoteiros[index].Origem << " : " << dadosRoteiros[index].Destino << endl;
        }
    }
}