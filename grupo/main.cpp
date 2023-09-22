#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <ctime>

using namespace std;

struct Passageiro
{
    string cpf;
    string nome;
    string dtNascimento;
    int numAutorizacao = 0;
};
struct dataHora
{
    string data;
    string hora;
};
struct Roteiro
{
    string codigo;
    dataHora dataHoraPrevista;
    string duracaoPrevista;
    string origem;
    string destino;
};
struct Ocorrencia
{
    string descricao = "Nenhuma ocorrencia registrada";
    dataHora data_Hora = {"N/A", "N/A"};
    int numeroApolice = 0;
};
struct Embarque
{
    Passageiro passageiro;
    Roteiro roteiro;
    bool realizada;
    dataHora data_Hora;
    string duracao;
    Ocorrencia ocorrencia;
};

bool encontra;

bool validarCPF(const string &cpf)
{
    // Verifica se o CPF tem 11 dígitos
    if (cpf.length() != 11)
    {
        cout << "Cpf inválido insira novamente." << endl;
        return false;
    }

    // Verifica se todos os caracteres são dígitos
    for (char c : cpf)
    {
        if (!isdigit(c))
        {
            cout << "Cpf inválido insira novamente." << endl;
            return false;
        }
    }

    return true;
}

bool extrairHora(const string &horaStr, int &horas, int &minutos)
{
    char delim;
    istringstream ss(horaStr);

    // Tenta extrair a hora no formato HH:MM
    ss.clear();
    ss.str(horaStr);
    if (ss >> horas >> delim >> minutos)
    {
        // Verifica se as horas e minutos estão no intervalo válido
        if (horas >= 0 && horas < 24 && minutos >= 0 && minutos < 60)
        {
            return true;
        }
    }
    cout << "Hora invalida siga o padrao HH:MM exemplo 22:20" << endl;
    return false;
}

bool isAnoBissexto(int ano)
{
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

bool extrairData(const string &dataStr, int &dia, int &mes, int &ano)
{
    char delim;
    istringstream ss(dataStr);

    if (ss >> dia >> delim >> mes >> delim >> ano)
    {
        // Verifica se o mês é válido
        if (mes >= 1 && mes <= 12)
        {
            // Verifica o número de dias no mês
            int diasNoMes = 31; // Janeiro, março, maio, julho, agosto, outubro, dezembro têm 31 dias

            if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
            {
                diasNoMes = 30; // Abril, junho, setembro, novembro têm 30 dias
            }
            else if (mes == 2)
            {
                // Fevereiro pode ter 28 ou 29 dias, dependendo se é um ano bissexto
                if (isAnoBissexto(ano))
                    diasNoMes = 29;
                else
                    diasNoMes = 28;
            }

            // Verifica se o dia está dentro do intervalo válido para o mês
            if (dia >= 1 && dia <= diasNoMes)
            {
                return true;
            }
        }
    }

    cout << "Data inválida. Insira novamente!" << endl;
    return false;
}

int calcularIdade(const string &dataNascimento)
{
    int dia, mes, ano;
    if (!extrairData(dataNascimento, dia, mes, ano))
    {
        cerr << "Formato de data inválido.\n";
        return -1; // Retorno de erro
    }

    // Obter a data atual
    time_t t = time(nullptr);
    tm *tm_atual = localtime(&t);
    int anoAtual = tm_atual->tm_year + 1900;
    int mesAtual = tm_atual->tm_mon + 1; // Os meses vão de 0 a 11
    int diaAtual = tm_atual->tm_mday;

    // Calcular a idade
    int idade = anoAtual - ano;
    if (mesAtual < mes || (mesAtual == mes && diaAtual < dia))
    {
        idade--;
    }

    return idade;
}

void imprimiRoteiro(Roteiro &roteiro)
{
    cout << "Codigo do roteiro :" << roteiro.codigo << endl;
    cout << "Data e hora prevista da saida: "
         << roteiro.dataHoraPrevista.data << ", "
         << roteiro.dataHoraPrevista.hora
         << endl;
    cout << "Duracao prevista: " << roteiro.duracaoPrevista << endl;
    cout << "Origem da viagem: " << roteiro.origem << endl;
    cout << "Destino da viagem: " << roteiro.destino << endl;
    cout << endl;
}

void incluirRoteiro(vector<Roteiro> &roteiros)
{
    int dia, mes, ano;
    Roteiro roteiro;
    int hora, minuto;
    cout << "Insira o codigo do Roteiro: ";
    cin >> roteiro.codigo;
    cout << endl;
    do
    {
        cout << "Digite a data da saida prevista"
             << ": ";
        cin >> roteiro.dataHoraPrevista.data;
        cout << endl;
    } while (!extrairData(roteiro.dataHoraPrevista.data, dia, mes, ano));

    do
    {
        cout << "Digite a hora da saida prevista ( HH:MM )"
             << ": ";
        cin >> roteiro.dataHoraPrevista.hora;
        cout << endl;
    } while (!extrairHora(roteiro.dataHoraPrevista.hora, hora, minuto));

    cout << "Digite a duracao da viagem prevista: ";
    // cin >> roteiro.duracaoPrevista;
    while (getline(cin, roteiro.duracaoPrevista))
    {
        if (roteiro.duracaoPrevista != "")
        {
            break;
        }
    }
    cout << endl;

    cout << "Digite a origem da viagem: ";
    while (getline(cin, roteiro.origem))
    {
        if (roteiro.origem != "")
        {
            break;
        }
    }
    // cin >> roteiro.origem;
    cout << endl;

    cout << "Digite a destino da viagem: ";
    while (getline(cin, roteiro.destino))
    {
        if (roteiro.destino != "")
        {
            break;
        }
    }
    // cin >> roteiro.destino;
    cout << endl;

    roteiros.push_back(roteiro);
}

void excluirRoteiro(vector<Roteiro> &roteiros)
{
    string codigo;
    cout << "insira o codigo do roteiro a ser excluido: ";
    cin >> codigo;
    cout << endl;
    for (auto it = roteiros.begin(); it != roteiros.end(); ++it)
    {
        if (it->codigo == codigo)
        {
            cout << " foi excluido com sucesso!" << endl;
            it = roteiros.erase(it);
            cout << endl;
            return;
        }
    }
    cout << "O roteiro não existe !!" << endl;
}

void alterarRoteiro(vector<Roteiro> &roteiros)
{
    string codigo;
    cout << "insira o codigo do roteiro a ser alterado: ";
    cin >> codigo;
    cout << endl;
    for (auto it = roteiros.begin(); it != roteiros.end(); ++it)
    {
        if (it->codigo == codigo)
        {
            int escolha;
            string codigo;
            string data;
            string horaPrevista;
            string duracaoPrevista;
            string origem, destino;
            int hora, minuto;
            imprimiRoteiro(*it);
            do
            {
                cout << "Qual o campo do roteiro voce deseja alterar: " << endl;
                cout << "1.Codigo" << endl;
                cout << "2.Data prevista" << endl;
                cout << "3.Hora prevista" << endl;
                cout << "4.Duracao da viagem prevista" << endl;
                cout << "5.Origem da viagem" << endl;
                cout << "6.Destino da viagem" << endl;
                cout << "Insira sua escolha: ";
                cin >> escolha;
                cout << endl;
                switch (escolha)
                {
                case 1:
                    cout << "Insira o novo codigo: ";
                    cin >> codigo;
                    cout << endl;
                    it->codigo = codigo;
                    break;
                case 2:
                    do
                    {
                        cout << "Digite a nova data de saida prevista: ";
                        cin >> data;
                        cout << endl;
                    } while (calcularIdade(it->dataHoraPrevista.data) == -1);
                    do
                    {
                        cout << "Digite a nova hora de saida prevista"
                             << ": ";
                        cin >> horaPrevista;
                        cout << endl;
                    } while (!extrairHora(it->dataHoraPrevista.hora, hora, minuto));
                    it->dataHoraPrevista.data = data;
                    it->dataHoraPrevista.hora = hora;
                    break;
                case 3:
                    cout << "Digite a nova duracao da viagem prevista: ";
                    cin >> duracaoPrevista;
                    cout << endl;
                    it->duracaoPrevista = duracaoPrevista;
                    break;
                case 4:
                    cout << "Digite a nova origem da viagem: ";
                    cin >> origem;
                    cout << endl;
                    it->origem = origem;
                    break;
                case 5:
                    cout << "Digite o novo destino da viagem: ";
                    cin >> destino;
                    cout << endl;
                    it->destino = destino;
                    break;
                case 0:
                    cout << "Saindo !!" << endl;
                    break;
                default:
                    cout << "Escolha inválida. Por favor, tente novamente." << endl;
                    break;
                }

            } while (escolha < 1 || escolha > 6);
            imprimiRoteiro(*it);
            break;
        }
    }
}

void listarRoteiro(vector<Roteiro> &roteiros)
{
    for (Roteiro roteiro : roteiros)
    {
        imprimiRoteiro(roteiro);
    }
}

void localizarRoteiro(vector<Roteiro> &roteiros)
{
    string codigo;
    cout << "insira o codigo do roteiro a ser encontrado: ";
    cin >> codigo;
    cout << endl;

    for (Roteiro roteiro : roteiros)
    {
        if (roteiro.codigo == codigo)
        {
            imprimiRoteiro(roteiro);

            break;
        }
    }
}

void imprimiPassageiro(Passageiro &passageiro)
{
    cout << "Passageiro :" << passageiro.nome << endl;
    cout << "Cpf: " << passageiro.cpf << endl;
    cout << "Data de Nascimento: " << passageiro.dtNascimento << endl;
    if (passageiro.numAutorizacao)
    {
        cout << "Número de autorizacao: " << passageiro.numAutorizacao << endl;
    }
    cout << endl;
}
void incluir(vector<Passageiro> &passageiros)
{
    Passageiro passageiro;
    cout << "Insira o nome do passageiro: ";
    // cin >> passageiro.nome;
    while (getline(cin, passageiro.nome))
    {
        if (passageiro.nome != "")
        {
            break;
        }
    }
    // getline(cin, passageiro.nome);
    cout << endl;
    do
    {
        cout << "Digite o CPF (apenas números) do " << passageiro.nome << ": ";
        cin >> passageiro.cpf;
        cout << endl;
    } while (!validarCPF(passageiro.cpf));

    do
    {
        cout << "Insira a data de nascimento do passageiro (dd/mm/aaaa) " << passageiro.nome << ": ";
        cin >> passageiro.dtNascimento;
        cout << endl;
    } while (calcularIdade(passageiro.dtNascimento) == -1);

    if (calcularIdade(passageiro.dtNascimento) < 18)
    {
        cout << "O passageiro tem menos de 18 anos por isso insira o número de autorizacao do passageiro " << passageiro.nome << ": ";
        cin >> passageiro.numAutorizacao;
        cout << endl;
    }

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
            cout << endl;
            return;
        }
    }
    cout << "O passageiro não existe !!" << endl;
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
    cout << "insira o cpf do passageiro a encontrado: ";
    cin >> cpf;
    cout << endl;

    for (Passageiro passageiro : passageiros)
    {
        if (passageiro.cpf == cpf)
        {
            imprimiPassageiro(passageiro);
            break;
        }
    }
}
void encontraPassageiro(bool value)
{
    encontra = value;
}
void preencherRoteiroTeste(vector<Roteiro> &roteiros)
{
    string destinos[] = {"São Paulo", "Rio de Janeiro", "Belo Horizonte", "Curitiba", "Porto Alegre", "Salvador", "Brasília", "Recife", "Fortaleza", "Manaus"};
    string origens[] = {"Campinas", "Santos", "Campina Grande", "Cuiabá", "Maringá", "Natal", "Florianópolis", "Goiânia", "João Pessoa", "Belém"};

    for (int i = 1; i <= 10; ++i)
    {
        Roteiro roteiro;
        roteiro.codigo = "R" + to_string(i);
        roteiro.dataHoraPrevista.data = "0" + to_string(i) + "/09/2023"; // Data fictícia para teste
        roteiro.dataHoraPrevista.hora = "12:" + to_string(i * 10);       // Hora fictícia para teste
        roteiro.duracaoPrevista = to_string(i) + " horas";               // Duração fictícia para teste
        roteiro.origem = origens[i - 1];                                 // Origem fictícia para teste
        roteiro.destino = destinos[i - 1];                               // Destino fictício para teste

        roteiros.push_back(roteiro);
    }
}
void preencherPassageirosTeste(vector<Passageiro> &passageiros)
{
    srand(time(NULL));
    string nomes[] = {"João", "Maria", "Pedro", "Ana", "Carlos", "Lúcia", "Paulo", "Camila", "Rodrigo", "Isabela"};

    for (int i = 0; i < 10; ++i)
    {
        Passageiro passageiro;
        passageiro.nome = nomes[i];

        // Gera um CPF fictício válido para o passageiro
        // Esta é uma implementação fictícia apenas para demonstração
        // Em um cenário real, você precisaria gerar CPFs de forma diferente
        string cpfFicticio = "123456789";
        // srand(time(0));
        for (int j = 0; j < 2; ++j)
            cpfFicticio += to_string(rand() % 10);
        for (int j = 0; j < 6; ++j)
            cpfFicticio += to_string(rand() % 10);

        passageiro.cpf = cpfFicticio;

        // Simula uma data de nascimento válida para o passageiro
        // Se i for par, a data de nascimento será ajustada para garantir que tenha menos de 18 anos
        int anoAtual = 2023;                         // Ano atual fictício para o exemplo
        int anoNascimento = anoAtual - 18 - (i % 2); // Ajusta a data de nascimento para garantir menos de 18 anos
        passageiro.dtNascimento = "01/01/" + to_string(anoNascimento);

        if (i % 2 == 0) // Simular alguns passageiros menores de 18 anos
            passageiro.numAutorizacao = i + 1;

        passageiros.push_back(passageiro);
    }
}

vector<string> menuNomes = {
    "Incluir.",
    "Excluir.",
    "Alterar ( Apenas CPF ).",
    "Listar.",
    "Localizar ( Pelo CPF ).",
};

vector<string> menuNomesRoteiro = {
    "Incluir.",
    "Excluir.",
    "Alterar ( Apenas Codigo ).",
    "Listar.",
    "Localizar ( Pelo Codigo ).",
};

vector<string> menuGeralNomes = {
    "Gestao de Passageiros.",
    "Gestao de Roteiros.",
    "Gestao de Embarques",
    "Gestao de Ocorrencias",
};
vector<string> menuOpcoesEmbarque = {
    "Incluir Embarque.",
    "Excluir Embarque.",
    "Alterar Embarque",
    "Listar Embarques",
};
vector<string> menuOcorrencias = {
    "Incluir Ocorrencia.",
    "Excluir Ocorrencia",
    "Alterar Ocorrencia",
    "Listar Ocorrencias por passageiros",
    "Listar Ocorrencias por roteiros",
    "Incluir Ocorrencias por roteiros",
};

void incluirEmbarque(vector<Embarque> &embarques, vector<Passageiro> &passageiros, vector<Roteiro> &roteiros)
{
    int dia, mes, ano;
    Embarque embarque;
    Passageiro passageiroAtual;
    Roteiro roteiroAtual;
    dataHora dataRealEmbarque;
    string cpf, codigoRoteiro, duracao;
    char escolha;
    int hora, minuto;

    cout << "Digite o cpf do passageiro: ";
    cin >> cpf;
    cout << endl;

    // Verificar se o CPF existe
    bool cpfExiste = false;
    for (const auto &passageiro : passageiros)
    {
        if (passageiro.cpf == cpf)
        {
            passageiroAtual = passageiro;
            cpfExiste = true;
            break;
        }
    }

    if (!cpfExiste)
    {
        cout << "CPF nao foi encontrado. Embarque nao realizado." << endl;
        return;
    }

    cout << "Digite o codigo do Roteiro: ";
    cin >> codigoRoteiro;
    cout << endl;

    // Verifica se o código do roteiro existe
    bool roteiroExiste = false;
    for (const auto &roteiro : roteiros)
    {
        if (roteiro.codigo == codigoRoteiro)
        {
            roteiroAtual = roteiro;
            roteiroExiste = true;
            break;
        }
    }

    if (!roteiroExiste)
    {
        cout << "Codigo do roteiro nao encontrado. Embarque nao realizado." << endl;
        return;
    }
    do
    {
        cout << "Digite a data real do embarque (dd/mm/aaaa)"
             << ": ";
        cin >> dataRealEmbarque.data;
        cout << endl;
    } while (!extrairData(dataRealEmbarque.data, dia, mes, ano));
    do
    {
        cout << "Digite a hora real do embarque (HH:MM)"
             << ": ";
        cin >> dataRealEmbarque.hora;
        cout << endl;
    } while (!extrairHora(dataRealEmbarque.hora, hora, minuto));

    cout << "O embarque ja aconteceu? (S para Sim, N para Nao): ";
    cin >> escolha;
    cout << endl;

    cout << "Qual foi a duração do embarque: ";
    cin.ignore();
    getline(cin, duracao);

    bool embarqueRealizado = (escolha == 'S' || escolha == 's');
    Embarque novoEmbarque = {passageiroAtual, roteiroAtual, embarqueRealizado, dataRealEmbarque, duracao};
    embarques.push_back(novoEmbarque);
}

void excluirEmbarque(vector<Embarque> &embarques, const vector<Passageiro> &passageiros, const vector<Roteiro> &roteiros)
{
    string codigoRoteiro;
    string cpfPassageiro;
    bool encontrado = false;

    cout << "Digite o codigo do Roteiro: ";
    cin >> codigoRoteiro;
    cout << endl;

    // Encontrar os passageiros embarcados nesse roteiro
    cout << "Passageiros embarcados nesse roteiro:\n";
    for (const auto &embarque : embarques)
    {
        if (embarque.roteiro.codigo == codigoRoteiro)
        {
            cout << "CPF: " << embarque.passageiro.cpf << ", Nome: " << embarque.passageiro.nome << "\n";
        }
    }

    cout << "Digite o CPF do passageiro que nao embarcara: ";
    cin >> cpfPassageiro;
    cout << endl;

    // Procurar o embarque e excluí-lo se encontrado
    for (auto it = embarques.begin(); it != embarques.end(); ++it)
    {
        if (it->roteiro.codigo == codigoRoteiro && it->passageiro.cpf == cpfPassageiro)
        {
            embarques.erase(it);
            encontrado = true;
            cout << "Embarque excluido com sucesso.\n";
            break;
        }
    }

    if (!encontrado)
    {
        cout << "Embarque nao encontrado para o roteiro e CPF fornecidos.\n";
    }
}

void alterarEmbarque(vector<Embarque> &embarques)
{
    string codigoRoteiro;
    string cpfPassageiro;
    string novaDuracaoReal;

    cout << "Digite o codigo do Roteiro: ";
    cin >> codigoRoteiro;

    // Listar os passageiros embarcados nesse roteiro
    cout << "Passageiros embarcados nesse roteiro:\n";
    for (const auto &embarque : embarques)
    {
        if (embarque.roteiro.codigo == codigoRoteiro)
        {
            cout << "CPF: " << embarque.passageiro.cpf << ", Nome: " << embarque.passageiro.nome << "\n";
        }
    }

    cout << "Digite o CPF do passageiro: ";
    cin >> cpfPassageiro;

    // Procurar o embarque e alterar a duração real se encontrado
    bool encontrado = false;
    for (auto &embarque : embarques)
    {
        if (embarque.roteiro.codigo == codigoRoteiro && embarque.passageiro.cpf == cpfPassageiro)
        {
            cout << "Digite a nova duracao real do embarque: ";
            cin.ignore();
            getline(cin, novaDuracaoReal);
            embarque.duracao = novaDuracaoReal;
            encontrado = true;
            cout << "Registro de embarque alterado com sucesso.\n";
            break;
        }
    }

    if (!encontrado)
    {
        cout << "Embarque nao encontrado para o roteiro e CPF fornecidos.\n";
    }
}

void listarEmbarques(const vector<Embarque> &embarques)
{
    cout << "Lista de Embarques:\n";

    for (const auto &embarque : embarques)
    {
        cout << "CPF: " << embarque.passageiro.cpf << ", Nome: " << embarque.passageiro.nome;
        cout << ", Código do Roteiro: " << embarque.roteiro.codigo;
        cout << ", Data Real do Embarque: " << embarque.data_Hora.data << ":" << embarque.data_Hora.hora;
        cout << ", Status: " << (embarque.realizada ? "Realizado" : "Não Realizado") << "\n";
    }
}

void incluirOcorrencia(vector<Embarque> &embarques)
{
    string cpfPassageiro;
    string codigoRoteiro;

    cout << "Digite o CPF do passageiro: ";
    cin >> cpfPassageiro;

    cout << "Digite o codigo do Roteiro: ";
    cin >> codigoRoteiro;

    bool encontrado = false;
    int dia, mes, ano;
    int hora, min;

    // Procurar o embarque correspondente ao CPF e código do roteiro fornecidos
    for (auto &embarque : embarques)
    {
        if (embarque.passageiro.cpf == cpfPassageiro && embarque.roteiro.codigo == codigoRoteiro)
        {
            cout << "Digite a descricao da ocorrencia: ";
            cin.ignore(); // Limpa o buffer para getline
            getline(cin, embarque.ocorrencia.descricao);

            do
            {
                cout << "Digite a data da ocorrencia (formato: dd/mm/aaaa): ";
                cin >> embarque.ocorrencia.data_Hora.data;
                cout << endl;
            } while (!extrairData(embarque.ocorrencia.data_Hora.data, dia, mes, ano));

            cout << embarque.ocorrencia.data_Hora.data << endl;

            do
            {
                cout << "Digite a hora da ocorrencia (formato: hh:mm): ";
                cin >> embarque.ocorrencia.data_Hora.hora;
                cout << endl;
            } while (!extrairHora(embarque.ocorrencia.data_Hora.hora, hora, min));

            cout << embarque.ocorrencia.data_Hora.hora << endl;

            cout << "Digite o numero da apolice: ";
            cin >> embarque.ocorrencia.numeroApolice;

            cout << "Ocorrência registrada com sucesso para o embarque.\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        cout << "Embarque nao encontrado para o CPF e codigo do roteiro fornecidos.\n";
    }
}

void excluirOcorrencia(vector<Embarque> &embarques)
{
    string cpfPassageiro;
    string codigoRoteiro;

    cout << "Digite o CPF do passageiro: ";
    cin >> cpfPassageiro;

    cout << "Digite o codigo do Roteiro: ";
    cin >> codigoRoteiro;

    bool encontrou = false;

    // Procurar o embarque correspondente ao CPF e código do roteiro fornecidos
    for (auto &embarque : embarques)
    {
        if (embarque.passageiro.cpf == cpfPassageiro && embarque.roteiro.codigo == codigoRoteiro)
        {
            // Exclui a ocorrência associada ao embarque
            embarque.ocorrencia = {}; // Atribui uma nova ocorrência vazia
            cout << "Ocorrência excluída com sucesso para o embarque.\n";
            encontrou = true;
            break;
        }
    }

    if (!encontrou)
    {
        cout << "Embarque nao encontrado para o CPF e codigo do roteiro fornecidos.\n";
    }
}

void alterarOcorrencia(vector<Embarque> &embarques)
{
    string cpfPassageiro;
    string codigoRoteiro;

    cout << "Digite o CPF do passageiro: ";
    cin >> cpfPassageiro;

    cout << "Digite o codigo do Roteiro: ";
    cin >> codigoRoteiro;

    bool encontrou = false;

    // Procurar o embarque correspondente ao CPF e código do roteiro fornecidos
    for (auto &embarque : embarques)
    {
        if (embarque.passageiro.cpf == cpfPassageiro && embarque.roteiro.codigo == codigoRoteiro)
        {
            cout << "Descrição da ocorrência: " << embarque.ocorrencia.descricao << "\n";
            cout << "Deseja alterar a descrição da ocorrência? (s/n): ";
            char alterarDescricao;
            cin >> alterarDescricao;

            if (alterarDescricao == 's' || alterarDescricao == 'S')
            {
                cout << "Digite a nova descrição da ocorrência: ";
                cin.ignore(); // Limpa o buffer para getline
                getline(cin, embarque.ocorrencia.descricao);
            }

            cout << "Data da ocorrencia: " << embarque.ocorrencia.data_Hora.data << "\n";
            cout << "Deseja alterar a data da ocorrência? (s/n): ";
            char alterarData;
            cin >> alterarData;

            if (alterarData == 's' || alterarData == 'S')
            {
                cout << "Digite a nova data da ocorrência (formato: dd/mm/aaaa): ";
                cin.ignore(); // Limpa o buffer para getline
                getline(cin, embarque.ocorrencia.data_Hora.data);
            }
            cout << "Hora da ocorrencia: " << embarque.ocorrencia.data_Hora.hora << "\n";
            cout << "Deseja alterar a hora da ocorrencia? (s/n): ";
            char alterarHora;
            cin >> alterarHora;

            if (alterarHora == 's' || alterarHora == 'S')
            {
                cout << "Digite a nova data e hora da ocorrencia (formato: HH:MM): ";
                cin.ignore(); // Limpa o buffer para getline
                getline(cin, embarque.ocorrencia.data_Hora.hora);
            }

            cout << "Número da Apólice: " << embarque.ocorrencia.numeroApolice << "\n";
            cout << "Deseja alterar o número da apólice? (s/n): ";
            char alterarApolice;
            cin >> alterarApolice;

            if (alterarApolice == 's' || alterarApolice == 'S')
            {
                cout << "Digite o novo número da apólice: ";
                cin >> embarque.ocorrencia.numeroApolice;
            }

            cout << "Ocorrência alterada com sucesso para o embarque.\n";
            encontrou = true;
            break;
        }
    }

    if (!encontrou)
    {
        cout << "Embarque nao encontrado para o CPF e codigo do roteiro fornecidos.\n";
    }
}

void registrarOcorrenciaPorRoteiro(vector<Embarque> &embarques)
{
    string codigoRoteiro;

    cout << "Digite o codigo do roteiro: ";
    cin >> codigoRoteiro;

    bool encontrou = false;

    // Procurar os embarques associados ao código do roteiro fornecido
    for (auto &embarque : embarques)
    {
        if (embarque.roteiro.codigo == codigoRoteiro)
        {
            cout << "Para o embarque de " << embarque.roteiro.origem << " para " << embarque.roteiro.destino << ":\n";
            cout << "Digite a descrição da ocorrência: ";
            cin >> embarque.ocorrencia.descricao;

            cout << "Digite a data da ocorrencia (formato: DD/MM/AAAA): ";
            cin >> embarque.ocorrencia.data_Hora.data;

            cout << "Digite a hora da ocorrencia (formato: HH:MM): ";
            cin >> embarque.ocorrencia.data_Hora.hora;

            cout << "Digite o número da apolice: ";
            cin >> embarque.ocorrencia.numeroApolice;

            cout << "Ocorrencia registrada com sucesso para o embarque.\n";
            encontrou = true;
        }
    }

    if (!encontrou)
    {
        cout << "Nenhum embarque encontrado para o codigo do roteiro fornecido.\n";
    }
}

void listarOcorrenciasPorPassageiro(const vector<Embarque> &embarques)
{
    bool encontrou = false;
    string cpfPassageiro;
    cout << "Digite o CPF do passageiro: ";
    cin >> cpfPassageiro;

    cout << "Ocorrencias para o CPF " << cpfPassageiro << ":\n";

    for (const auto &embarque : embarques)
    {
        if (embarque.passageiro.cpf == cpfPassageiro)
        {
            cout << "Descricao: " << embarque.ocorrencia.descricao << "\n";
            cout << "Data: " << embarque.ocorrencia.data_Hora.data << "\n";
            cout << "Hora: " << embarque.ocorrencia.data_Hora.hora << "\n";
            cout << "Numero da Apolice: " << embarque.ocorrencia.numeroApolice << "\n\n";
            encontrou = true;
            break;
        }
    }

    if (!encontrou)
    {
        cout << "Nenhuma ocorrencia encontrada para o CPF " << cpfPassageiro << "\n";
    }
}

void listarOcorrenciasPorRoteiro(const vector<Embarque> &embarques)
{
    bool encontrou = false;
    string codigoRoteiro;
    cout << "Digite o codigo do roteiro: ";
    cin >> codigoRoteiro;

    cout << "Ocorrencias para o Roteiro de Codigo " << codigoRoteiro << ":\n";

    for (const auto &embarque : embarques)
    {
        if (embarque.roteiro.codigo == codigoRoteiro)
        {
            cout << "CPF do Passageiro: " << embarque.passageiro.cpf << "\n";
            cout << "Descricao: " << embarque.ocorrencia.descricao << "\n";
            cout << "Data: " << embarque.ocorrencia.data_Hora.data << "\n";
            cout << "Hora: " << embarque.ocorrencia.data_Hora.hora << "\n";
            cout << "Numero da Apolice: " << embarque.ocorrencia.numeroApolice << "\n\n";
            encontrou = true;
        }
    }

    if (!encontrou)
    {
        cout << "Nenhuma ocorrencia encontrada para o Roteiro de Codigo " << codigoRoteiro << "\n";
    }
}

void menuEmbarque(vector<Passageiro> &passageiros, vector<Roteiro> &roteiros, vector<Embarque> &embarques)
{
    int opcao;
    do
    {
        cout << "Menu opcões: " << endl;
        for (int i = 0; i < menuOpcoesEmbarque.size(); i++)
        {
            cout << i + 1 << ". " << (menuOpcoesEmbarque[i]) << endl;
        }
        cout << "0. Sair" << endl;
        cout << "Insira sua escolha: ";
        cin >> opcao;
        cout << endl;

        switch (opcao)
        {
        case 1:
            incluirEmbarque(embarques, passageiros, roteiros);
            break;
        case 2:
            excluirEmbarque(embarques, passageiros, roteiros);
            break;
        case 3:
            alterarEmbarque(embarques);
            break;
        case 4:
            listarEmbarques(embarques);
            break;
        case 0:
            cout << "Saindo !!" << endl;
            break;

        default:
            cout << "Escolha inválida. Por favor, tente novamente." << endl;
            break;
        }

    } while (opcao);
}

void menuOcorrencia(vector<Passageiro> passageiros, vector<Roteiro> roteiros, vector<Embarque> embarques)
{
    int opcao;
    do
    {
        cout << "Menu opcões: " << endl;
        for (int i = 0; i < menuOcorrencias.size(); i++)
        {
            cout << i + 1 << ". " << (menuOcorrencias[i]) << endl;
        }
        cout << "0. Sair" << endl;
        cout << "Insira sua escolha: ";
        cin >> opcao;
        cout << endl;

        switch (opcao)
        {
        case 1:
            incluirOcorrencia(embarques);
            break;
        case 2:
            excluirOcorrencia(embarques);
            break;
        case 3:
            alterarOcorrencia(embarques);
            break;
        case 4:
            listarOcorrenciasPorPassageiro(embarques);
            break;
        case 5:
            listarOcorrenciasPorRoteiro(embarques);
        case 6:
            registrarOcorrenciaPorRoteiro(embarques);
        case 0:
            cout << "Saindo !!" << endl;
            break;

        default:
            cout << "Escolha inválida. Por favor, tente novamente." << endl;
            break;
        }

    } while (opcao);
}

void menuOpcoesPassageiros(bool alternar, vector<Passageiro>& passageiros, vector<Roteiro>& roteiros)
{
    int opcao;
    do
    {
        cout << "Menu opcões: " << endl;
        for (int i = 0; i < menuNomes.size(); i++)
        {
            cout << i + 1 << ". " << (alternar ? menuNomes[i] : menuNomesRoteiro[i]) << endl;
        }
        cout << "0. Sair" << endl;
        cout << "Insira sua escolha: ";
        cin >> opcao;
        cout << endl;

        switch (opcao)
        {
        case 1:
            alternar
                ? incluir(passageiros)
                : incluirRoteiro(roteiros);
            break;
        case 2:
            alternar
                ? excluir(passageiros)
                : excluirRoteiro(roteiros);
            break;
        case 3:
            alternar
                ? alterar(passageiros)
                : alterarRoteiro(roteiros);
            break;
        case 4:
            alternar
                ? listar(passageiros)
                : listarRoteiro(roteiros);
            break;
        case 5:
            alternar
                ? localizar(passageiros)
                : localizarRoteiro(roteiros);
            break;
        case 0:
            cout << "Saindo !!" << endl;
            break;

        default:
            cout << "Escolha inválida. Por favor, tente novamente." << endl;
            break;
        }

    } while (opcao);
}
void menu()
{
    vector<Roteiro> roteiros;
    vector<Passageiro> passageiros;
    vector<Embarque> embarques;
    int opcao;
    preencherRoteiroTeste(roteiros);
    preencherPassageirosTeste(passageiros);
    do
    {
        cout << "Menu opcões: " << endl;
        for (int i = 0; i < menuGeralNomes.size(); i++)
        {
            cout << i + 1 << ". " << menuGeralNomes[i] << endl;
        }
        cout << "0. Sair" << endl;
        cout << "Insira sua escolha: ";
        cin >> opcao;
        cout << endl;

        switch (opcao)
        {
        case 1:
            menuOpcoesPassageiros(true, passageiros, roteiros);
            break;
        case 2:
            menuOpcoesPassageiros(false, passageiros, roteiros);
            break;
        case 3:
            menuEmbarque(passageiros, roteiros, embarques);
            break;
        case 4:
            menuOcorrencia(passageiros, roteiros, embarques);
            break;
        case 0:
            cout << "Saindo !!" << endl;
            break;

        default:
            cout << "Escolha inválida. Por favor, tente novamente." << endl;
            break;
        }

    } while (opcao);
}

int main()
{
    menu();

    return 0;
}