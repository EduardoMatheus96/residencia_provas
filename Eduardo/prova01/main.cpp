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

bool isAnoBissexto(int ano) {
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

    cout << "Data inválida. Insira novamente!" << std::endl;
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
    } while (calcularIdade(roteiro.dataHoraPrevista.data) == -1);

    do
    {
        cout << "Digite a hora da saida prevista ( HH:MM )"
             << ": ";
        cin >> roteiro.dataHoraPrevista.hora;
        cout << endl;
    } while (!extrairHora(roteiro.dataHoraPrevista.hora, hora, minuto));

    cout << "Digite a duracao da viagem prevista: ";
    // cin >> roteiro.duracaoPrevista;
    while(getline(cin, roteiro.duracaoPrevista)){
        if(roteiro.duracaoPrevista != ""){
                break;
            }}
    cout << endl;

    cout << "Digite a origem da viagem: ";
    while(getline(cin, roteiro.origem)){
        if(roteiro.origem != ""){
                break;
            }}
    // cin >> roteiro.origem;
    cout << endl;

    cout << "Digite a destino da viagem: ";
    while(getline(cin, roteiro.destino)){
        if(roteiro.destino != ""){
                break;
            }}
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
    while(getline(cin, passageiro.nome)){
        if(passageiro.nome != ""){
                break;
            }}
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

void preencherPassageirosTeste(vector<Passageiro> &passageiros)
{
    string nomes[] = {"João", "Maria", "Pedro", "Ana", "Carlos", "Lúcia", "Paulo", "Camila", "Rodrigo", "Isabela"};

    for (int i = 0; i < 10; ++i)
    {
        Passageiro passageiro;
        passageiro.nome = nomes[i];

        // Gera um CPF fictício válido para o passageiro
        // Esta é uma implementação fictícia apenas para demonstração
        // Em um cenário real, você precisaria gerar CPFs de forma diferente
        std::string cpfFicticio = "123456789";
        srand(time(0)); // Inicializa a semente aleatória
        for (int j = 0; j < 2; ++j)
            cpfFicticio += to_string(rand() % 10);
        for (int j = 0; j < 6; ++j)
            cpfFicticio += to_string(rand() % 10);

        passageiro.cpf = cpfFicticio;

        // Simula uma data de nascimento válida para o passageiro
        // Se i for par, a data de nascimento será ajustada para garantir que tenha menos de 18 anos
        int anoAtual = 2023; // Ano atual fictício para o exemplo
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
    "Gestão de Passageiros.",
    "Gestão de Roteiros.",
};

void menuOpcoesPassageiros(bool alternar)
{
    vector<Passageiro> passageiros;
    vector<Roteiro> roteiros;
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
    int opcao;
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
            menuOpcoesPassageiros(true);
            break;
        case 2:
            menuOpcoesPassageiros(false);
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
