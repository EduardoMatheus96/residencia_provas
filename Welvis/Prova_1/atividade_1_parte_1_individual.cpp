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

Passageiro inserirPassageiro(){

    Passageiro passageiro;

    cout << "Insira se CPF: " << endl;
    cin >> passageiro.CPF;
    cout << "Insira seu Nome: " << endl;
    cin >> passageiro.nome;
    cout << "Insira sua data de Nascimento 00/00/0000: " << endl;
    cin >> passageiro.dtNascimento;
    cout << "Insira seu numero de autorizacao: " << endl;
    cin >> passageiro.numAutorizacao;

    return passageiro;

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
                passageiros.push_back(inserirPassageiro());
            
            
        }

    }while(selectedOption != 0);




    return 0;
}