#include <iostream>
#include <string>
#include <vector>
#include <regex>
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

bool validarCPF(const string& cpf) {
    // Verifica se o CPF possui 11 caracteres
    if (cpf.length() != 11)
        return false;

    // Verifica se todos os caracteres são dígitos
    for (char c : cpf) {
        if (!isdigit(c))
            return false;
    }

    return true;
}

bool verificarFormatoDataHora(const string& dataHora) {
    // Expressão regular para o formato desejado
    regex formato("([0-9]{2})/([0-9]{2})/([0-9]{4}) ([0-9]{2}):([0-9]{2})");

    // Verificar se a string corresponde ao formato desejado
    if (regex_match(dataHora, formato)) {
        return true;
    } else {
        return false;
    }
}

bool verificarFormatoData(const string& dataHora) {
    // Expressão regular para o formato desejado
    regex formato("([0-9]{2})/([0-9]{2})/([0-9]{4})");

    // Verificar se a string corresponde ao formato desejado
    if (regex_match(dataHora, formato)) {
        return true;
    } else {
        return false;
    }
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

bool autorizacao(Passageiro passageiro){
    return !verificarMaiorIdade(passageiro.dtNascimento);       
}

void inserirPassageiro(vector<Passageiro> &vetPass){

    Passageiro passageiro;    


    cout << "Insira seu CPF (Apenas numeros): " << endl;
    while(getline(cin, passageiro.CPF)){
        if(passageiro.CPF != ""){
            break;
        }
    }

    while(!validarCPF(passageiro.CPF)){
        passageiro.CPF = "";
        cout << "Formato de CPF incorreto!!!\n\n\n";

        cout << "Insira seu cpf: " << endl;    

        while(getline(cin, passageiro.CPF)){
            if(passageiro.CPF != ""){
                break;
            }
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

    while(!verificarFormatoData(passageiro.dtNascimento)){
        passageiro.dtNascimento = "";
        cout << "Formato de data incorretos!!!\n\n\n";

        cout << "Insira sua data de Nascimento 00/00/0000: " << endl;    

        while(getline(cin, passageiro.dtNascimento)){
            if(passageiro.dtNascimento != ""){
                break;
            }
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
    cout << "Insira data e hora prevista (00/00/0000 00:00): " << endl;    

    while(getline(cin, roteiro.data_Hora_prevista)){
        if(roteiro.data_Hora_prevista != ""){
            break;
        }
    }

    while(!verificarFormatoDataHora(roteiro.data_Hora_prevista)){
        roteiro.data_Hora_prevista = "";
        cout << "Formato de data e hora incorretos!!!\n\n\n";

        cout << "Insira data e hora prevista (00/00/0000 00:00): " << endl;    

        while(getline(cin, roteiro.data_Hora_prevista)){
            if(roteiro.data_Hora_prevista != ""){
                break;
            }
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

bool excluirRoteiro(vector<Roteiro> &vetRot, int codigo){


    for (auto it = vetRot.begin(); it != vetRot.end(); it++) {
        if (it->codigo == codigo) {
            it = vetRot.erase(it);
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
            cout << "Num Autorizacao: " << it->numAutorizacao << endl;
            cout << endl << endl;
        }
    }

}

void LocalizarRoteiro(vector<Roteiro> &vetRot, int codigo){

    for (auto it = vetRot.begin(); it != vetRot.end(); it++) {
        if (it->codigo == codigo) {
            cout << "Codigo: " << it->codigo << endl;
            cout << "Data e Hora Prevista: " << it->data_Hora_prevista << endl;
            cout << "Duracao Prevista: " << it->duracao_prevista << endl;
            cout << "Origem: " << it->origem << endl;
            cout << "Destino: " << it->destino << endl;
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

void alterarRoteiro(vector<Roteiro> &vetRot, int codigo){

    for (auto it = vetRot.begin(); it != vetRot.end(); it++) {
        if (it->codigo == codigo) {    
            
            cout << "Codigo: " << it->codigo << endl;
            cout << "Data e Hora Prevista: " << it->data_Hora_prevista << endl;
            cout << "Duracao Prevista: " << it->duracao_prevista << endl;
            cout << "Origem: " << it->origem << endl;
            cout << "Destino: " << it->destino << endl;
            cout << endl << endl;
            
            cout << "Deseja alterar o Codigo: (Sim) | (Nao)" << endl;
            string res;
            cin >> res;
            if(res == "Sim"){
                cout << "Codigo: " << endl;
                cin >> it->codigo;                
            }              

            cout << "Deseja alterar a Data e Hora Prevista: (Sim) | (Nao)" << endl;
            cin >> res;
            if(res == "Sim"){
                cout << "Data e Hora Prevista: " << endl;
                while(getline(cin, it->data_Hora_prevista)){
                    if(it->data_Hora_prevista != ""){
                        break;
                    }
                }
            }           
                            
            cout << "Deseja alterar a Duracao Prevista: (Sim) | (Nao)" << endl;
            cin >> res;
            if(res == "Sim"){
                cout << "Duracao Prevista: " << endl;
                while(getline(cin, it->duracao_prevista)){
                    if(it->duracao_prevista != ""){
                        break;
                    }
                }
            }
            
            cout << "Deseja alterar a Origem: (Sim) | (Nao)" << endl;
            cin >> res;
            if(res == "Sim"){
                cout << "Origem: " << endl;
                while(getline(cin, it->origem)){
                    if(it->origem != ""){
                        break;
                    }
                }
            }

            cout << "Deseja alterar o Destino: (Sim) | (Nao)" << endl;
            cin >> res;
            if(res == "Sim"){
                cout << "Destino: " << endl;
                while(getline(cin, it->destino)){
                    if(it->destino != ""){
                        break;
                    }
                }
            }
                
            LocalizarRoteiro(vetRot, it->codigo);
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


void listarRoteiros(vector<Roteiro> &vetRot) {
      
    for (Roteiro rot: vetRot){
        cout << "Codigo: " << rot.codigo << endl;
        cout << "Data e Hora Prevista: " << rot.data_Hora_prevista << endl;
        cout << "Duracao Prevista: " << rot.duracao_prevista << endl;
        cout << "Origem: " << rot.origem << endl;
        cout << "Destino: " << rot.destino << endl;
        cout << endl << endl;
    }
}



int main(void){

    string opcoesDoMenuPassageiro = "\n\nMenu Passageiro\t\t\t\tMenu Roteiro\n\n(1) Incluir\t\t\t\t(6) Incluir\n(2) Excluir\t\t\t\t(7) Excluir\n(3) Alterar(Apenas por CPF)\t\t(8) Alterar(apenas por Codigo)\n(4) Listar\t\t\t\t(9) Listar\n(5) Localizar (por CPF)\t\t\t(10) Localizar (por Codigo)\n(0) Sair\n\n\n\n";

    vector<Passageiro> passageiros;
    vector<Roteiro> roteiro;

    cout << opcoesDoMenuPassageiro << endl;
    int selectedOption;

    do {
        cin >> selectedOption;

        if(selectedOption != 0){

            if(selectedOption == 1)
                inserirPassageiro(passageiros);   
            if(selectedOption == 2){
                cout << "Digite o CPF do passageiro" << endl;
                string tempCPF;
                while(getline(cin, tempCPF)){
                    if(tempCPF != ""){
                        break;
                    }
                }
                cout << (excluirPassageiro(passageiros, tempCPF) ? "Item Excluido" : "Item Nao encontrado") << endl;
            }

            if(selectedOption == 3){
                cout << "Digite o CPF do passageiro" << endl;
                string tempCPF;
                while(getline(cin, tempCPF)){
                    if(tempCPF != ""){
                        break;
                    }
                }
                alterarPassageiro(passageiros, tempCPF);
            }

            if(selectedOption == 4)
                listarPassageiros(passageiros);

            if(selectedOption == 5){
                cout << "Digite o CPF do passageiro" << endl;
                string tempCPF;
                while(getline(cin, tempCPF)){
                    if(tempCPF != ""){
                        break;
                    }
                }
                Localizar(passageiros, tempCPF);
            }

            if(selectedOption == 6){
                inserirRoteiro(roteiro);
            }

            if(selectedOption == 7){
                cout << "Digite o codigo do roteiro" << endl;
                int temCodigo;
                cin >> temCodigo;
                cout << (excluirRoteiro(roteiro, temCodigo) ? "Item Excluido" : "Item Nao encontrado") << endl;
            }

            if(selectedOption == 8){
                cout << "Digite o codigo do roteiro" << endl;
                int tempCodigo;
                cin >> tempCodigo;
                alterarRoteiro(roteiro, tempCodigo);
            }

            if(selectedOption == 9){
                listarRoteiros(roteiro);
            }

            if(selectedOption == 10){
                cout << "Digite o codigo do roteiro:" << endl;
                int tempRoteiro;
                cin >> tempRoteiro;
                LocalizarRoteiro(roteiro, tempRoteiro);
            }

        }else if (selectedOption == 0){
            break;
        }else {
            cout << "Opcao Invalida!!!" << endl;
        }

        cout << opcoesDoMenuPassageiro << endl;

    }while(selectedOption != 0);

    return 0;
}