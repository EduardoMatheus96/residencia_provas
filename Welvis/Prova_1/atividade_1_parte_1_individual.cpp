#include <iostream>
#include <string>
#include <vector>
using namespace  std;


struct Passageiro{
    string CPF;
    string nome;
    string dtNascimento;
    int numAutorizacao = -1;
};

struct Roteiro{
    int codigo;
    string data_Hora_prevista;
    string duracao_prevista;
    string origem;
    string destino;
};


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

bool autorizacao(Passageiro passageiro){
    return !verificarMaiorIdade(passageiro.dtNascimento);       
}

void inserirPassageiro(vector<Passageiro> &vetPass){

    Passageiro passageiro;

    cout << "Insira se CPF: " << endl;
    cin >> passageiro.CPF;
    cout << "Insira seu Nome: " << endl;
    cin >> passageiro.nome;
    cout << "Insira sua data de Nascimento 00/00/0000: " << endl;
    cin >> passageiro.dtNascimento;
    
    if(autorizacao(passageiro)){
        cout << "Insira seu numero de autorizacao: " << endl;
        cin >> passageiro.numAutorizacao;
    }

    vetPass.push_back(passageiro);   

}


bool excluirPassageiro(vector<Passageiro> &vetPass, string CPF){


    for (auto it = vetPass.begin(); it != vetPass.end(); it++) {
        if (it->CPF == CPF) {
            it = vetPass.erase(it);
            return true;
        }
    }

    return false;

}

void listarPassageiros(vector<Passageiro> &vetPass) {
    for (Passageiro pass: vetPass){
        cout << pass.CPF << endl;
        cout << pass.nome << endl;
        cout << pass.dtNascimento << endl;
        cout << pass.numAutorizacao << endl;
        cout << endl << endl;
    }
}

int main(void){

    string opcoesDoMenu = "(1) Incluir\n(2) Excluir\n(3) Alterar(Apenas por CPF)\n(4) Listar\n(5) Localizar (por CPF)\n(0) Sair";

    vector<Passageiro> passageiros;
    vector<Roteiro> roteiro;

    cout << opcoesDoMenu << endl;
    int selectedOption;

    do {
        cin >> selectedOption;

        if(selectedOption != 0){

            if(selectedOption == 1)
                inserirPassageiro(passageiros);   
            if(selectedOption == 2){
                cout << "Digite o CPF do passageiro" << endl;
                string tempCPF;
                cin >> tempCPF;
                cout << (excluirPassageiro(passageiros, tempCPF) ? "Item Excluido" : "Item Não encontrado") << endl;
            }
            
        }else if (selectedOption == 0){
            break;
        }else {
            cout << "Opcao Invalida!!!" << endl;
        }

        cout << opcoesDoMenu << endl;

    }while(selectedOption != 0);




    return 0;
}

