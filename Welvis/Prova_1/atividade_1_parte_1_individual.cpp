#include <iostream>
#include <string>
#include <vector>
using namespace  std;


struct Passageiro{
    string CPF;
    string nome;
    string dtNascimento;
    string numAutorizacao;
};

struct Roteiro{
    int codigo;
    string data_Hora_prevista;
    string duracao_prevista;
    string origem;
    string destino;
};

bool autorizacao(Passageiro passageiro){
    return verificarMaiorIdade(passageiro.dtNascimento);       
}

bool verificarMaiorIdade(string dataNascimento) {
    // Extrai o dia, mês e ano da string de data de nascimento
    int dia = stoi(dataNascimento.substr(0, 2));
    int mes = stoi(dataNascimento.substr(3, 2));
    int ano = stoi(dataNascimento.substr(6, 4));

    // Obtém a data atual
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int anoAtual = now->tm_year + 1900;
    int mesAtual = now->tm_mon + 1;
    int diaAtual = now->tm_mday;

    // Calcula a idade da pessoa
    int idade = anoAtual - ano;
    if (mes < mesAtual || (mes == mesAtual && dia < diaAtual)) {
        idade--; // ainda não fez aniversário este ano
    }

    // Verifica se a pessoa é maior de idade (18 anos ou mais)
    if (idade >= 18) {
        return true;
    } else {
        return false;
    }
}

void inserirPassageiro(vector<Passageiro> &vetPass){

    Passageiro passageiro;

    cout << "Insira se CPF: " << endl;
    cin >> passageiro.CPF;
    cout << "Insira seu Nome: " << endl;
    cin >> passageiro.nome;
    cout << "Insira sua data de Nascimento 00/00/0000: " << endl;
    cin >> passageiro.dtNascimento;
    
    vetPass.push_back(passageiro);   

}

int main(void){

    string opcoesDoMenu = "(1) Incluir\n(2) Excluir\n(3) Alterar(Apenas por CPF)\n(4) Listar\n(5) Localizar (por CPF)\n(0) Sair";
    cout << opcoesDoMenu << endl;
    int selectedOption;

    vector<Passageiro> passageiros;
    vector<Roteiro> roteiro;

    do {
        cin >> selectedOption;

        if(selectedOption != 0){
            cout << opcoesDoMenu << endl;

            if(selectedOption == 1)
                inserirPassageiro(passageiros);



            cout << passageiros[0].nome;
            
            
        }else if (selectedOption == 0){
            break;
        }else {
            cout << "Opcao Invalida!!!" << endl;
        }

    }while(selectedOption != 0);




    return 0;
}

