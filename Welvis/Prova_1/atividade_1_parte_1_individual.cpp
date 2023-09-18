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



int main(void){

    string menuOptions = "(1) Incluir\n(2) Excluir\n(3) Alterar(Apenas por CPF)\n(4) Listar\n(5) Localizar (por CPF)\n(0) Sair";
    cout << menuOptions << endl;
    int selectedOption;

    do {
        cin >> selectedOption;

        if(selectedOption != 0){
            cout << menuOptions << endl;
        }

    }while(selectedOption != 0);




    return 0;
}