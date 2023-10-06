#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct funcionario {
    string nome;
    string sobrenome;
    int ano_nasc;
    string RG;
    int ano_admissao;
    float salario;
    float salario_reajustado;
};

void Reajusta_dez_porcento (funcionario funcionarios[], int numFuncionarios){
    int i;
    for (i = 0; i<numFuncionarios; i++){
        funcionarios[i].salario_reajustado = funcionarios[i].salario + (funcionarios[i].salario*0.1);
    }
}

int main (){
    funcionario funcionarios[50];
	int numFuncionarios, i;

	cout << "Insira a quantidade de funcionarios que deseja cadastrar (maximo de 50)?";
	cin >> numFuncionarios;

    for (i = 0; i < numFuncionarios; i++){
        cout << "Nome: ";
        cin >> funcionarios[i].nome;
        cout << "Sobrenome: ";
        cin >> funcionarios[i].sobrenome;
        cout << "Ano de Nascimento: ";
        cin >> funcionarios[i].ano_nasc;
        cout << "RG: ";
        cin >> funcionarios[i].RG;
        cout << "Ano de admissao: ";
        cin >> funcionarios[i].ano_admissao;
        cout << "Salário: ";
        cin >> funcionarios[i].salario;
    }
    Reajusta_dez_porcento(funcionarios, numFuncionarios);

    cout << "------Funcionários com salario reajustado------" << endl;

    for (i=0; i< numFuncionarios; i++){
        cout << "Nome: " << funcionarios[i].nome << " " << funcionarios[i].sobrenome << endl;
        cout << "Salario anterior: " << funcionarios[i].salario << endl;
        cout << "Salario reajustado: " << funcionarios[i].salario_reajustado << endl;
    }    

    return 0;

}