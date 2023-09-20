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

    cout << "Insira seu CPF: " << endl;
    while(getline(cin, passageiro.CPF)){
        if(passageiro.CPF != ""){
            break;
        }
    }
    cout << "Insira seu Nome: " << endl;
    while(getline(cin, passageiro.nome)){
        if(passageiro.nome != ""){
            break;
        }
    }
    cout << "Insira sua data de Nascimento 00/00/0000: " << endl;
    while(getline(cin, passageiro.dtNascimento)){
        if(passageiro.dtNascimento != ""){
            break;
        }
    }
    
    if(autorizacao(passageiro)){
        cout << "Insira seu numero de autorizacao: " << endl;        
        cin >> passageiro.numAutorizacao;
    }

    vetPass.push_back(passageiro);   

}


void inserirRoteiro(vector<Roteiro> &vetRot){   
    Roteiro roteiro;

    cout << "Insira seu Codigo: " << endl;
    cin >> roteiro.codigo;
    cout << "Insira data e hora prevista: " << endl;
    while(getline(cin, roteiro.data_Hora_prevista)){
        if(roteiro.data_Hora_prevista != ""){
            break;
        }
    }
    cout << "Insira a duracao prevista: " << endl;
    while(getline(cin, roteiro.duracao_prevista)){
        if(roteiro.duracao_prevista != ""){
            break;
        }
    }  
    cout << "Insira a origem: " << endl;
    while(getline(cin, roteiro.origem)){
        if(roteiro.origem != ""){
            break;
        }
    }  
    cout << "Insira o destino: " << endl;
    while(getline(cin, roteiro.destino)){
        if(roteiro.destino != ""){
            break;
        }
    }  
    
    vetRot.push_back(roteiro);   

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

void Localizar(vector<Passageiro> &vetPass, string CPF){

    for (auto it = vetPass.begin(); it != vetPass.end(); it++) {
        if (it->CPF == CPF) {
            cout << "CPF: " << it->CPF << endl;
            cout << "Nome: " << it->nome << endl;
            cout << "Data de Nascimento: " << it->dtNascimento << endl;
            cout << "Num Utorizacao: " << it->numAutorizacao << endl;
            cout << endl << endl;
        }
    }

}


void alterarPassageiro(vector<Passageiro> &vetPass, string CPF){

    for (auto it = vetPass.begin(); it != vetPass.end(); it++) {
        if (it->CPF == CPF) {
            
            cout << "Nome: " << it->nome << endl;
            cout << "CPF: " << it->CPF << endl;
            cout << "Data de Nascimento: " << it->dtNascimento << endl;
            cout << "Num Utorizacao: " << it->numAutorizacao << endl;
            cout << endl << endl;
            
            cout << "Deseja alterar o  Nome: (Sim) | (Nao)" << endl;
            string res;
            cin >> res;
            if(res == "Sim"){
                while(getline(cin, it->nome)){
                    if(it->nome != ""){
                        break;
                    }
                }         
            }

            cout << "Deseja alterar o CPF: (Sim) | (Nao)" << it->CPF << endl;
            cin >> res;
            if(res == "Sim"){
                cout << "CPF: " << endl;
                while(getline(cin, it->CPF)){
                    if(it->CPF != ""){
                        break;
                    }
                }
            }           
                            
            cout << "Deseja alterar a data de nascimento: (Sim) | (Nao)" << endl;
            cin >> res;
            if(res == "Sim"){
                while(getline(cin, it->dtNascimento)){
                    if(it->dtNascimento != ""){
                        break;
                    }
                }
            }
            
            cout << "Deseja alterar o num autorizacao: (Sim) | (Nao)" << endl;
            cin >> res;
            if(res == "Sim"){
                cin >> it->numAutorizacao;
            }
                
            Localizar(vetPass, it->CPF);
        }
    }

}

void listarPassageiros(vector<Passageiro> &vetPass) {
    for (Passageiro pass: vetPass){
        cout << "CPF: " << pass.CPF << endl;
        cout << "Nome: " << pass.nome << endl;
        cout << "Data de Nascimento: " << pass.dtNascimento << endl;
        cout << "Num Utorizacao: " << pass.numAutorizacao << endl;
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

            if(selectedOption == 3){
                cout << "Digite o CPF do passageiro" << endl;
                string tempCPF;
                cin >> tempCPF;
                alterarPassageiro(passageiros, tempCPF);
            }

            if(selectedOption == 4)
                listarPassageiros(passageiros);

            if(selectedOption == 5){
                cout << "Digite o CPF do passageiro" << endl;
                string tempCPF;
                cin >> tempCPF;
                Localizar(passageiros, tempCPF);
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

