#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include <map>
#include <cstdlib> 
#include <ctime>   

using namespace std;

struct Passagem
{
    int numeroAssento;
    int hora;
    int idade;
    double preco;
    string data;
    string cpf;
    string nome;

    Passagem(int _numeroAssento, string _data, int _hora, string _cpf, string _nome, int _idade, double _preco)
    {
        numeroAssento = _numeroAssento;
        data = _data;
        hora = _hora;
        cpf = _cpf;
        nome = _nome;
        idade = _idade;
        preco = _preco;
    }
};

struct Viagem
{
    int numeroViagem;
    string cidadeOrigem;
    string cidadeDestino;
    int horario;
    vector<Passagem> passagens;

    Viagem(int _numeroViagem, string _cidadeOrigem, string _cidadeDestino, int _horario)
    {
        numeroViagem = _numeroViagem;
        cidadeOrigem = _cidadeOrigem;
        cidadeDestino = _cidadeDestino;
        horario = _horario;
    }
};

double calcularTotalArrecadadoViagem(const Viagem &viagem)
{
    double totalArrecadado = 0.0;
    for (const Passagem &passagem : viagem.passagens)
    {
        totalArrecadado += passagem.preco;
    }
    return totalArrecadado;
}

double calcularTotalArrecadadoMes(const vector<Viagem> &viagens, int mes)
{
    double totalArrecadado = 0.0;
    for (const Viagem &viagem : viagens)
    {
        for (const Passagem &passagem : viagem.passagens)
        {
            int viagemMes = stoi(passagem.data.substr(3, 2));
            if (viagemMes == mes)
            {
                totalArrecadado += passagem.preco;
            }
        }
    }
    return totalArrecadado;
}

int encontrarHorarioMaisRentavel(const vector<Viagem> &viagens)
{
    map<int, double> horarioArrecadado;
    for (const Viagem &viagem : viagens)
    {
        horarioArrecadado[viagem.horario] += calcularTotalArrecadadoViagem(viagem);
    }

    int horarioMaisRentavel = -1;
    double maxArrecadado = -1.0;

    for (const auto &pair : horarioArrecadado)
    {
        if (pair.second > maxArrecadado)
        {
            maxArrecadado = pair.second;
            horarioMaisRentavel = pair.first;
        }
    }

    return horarioMaisRentavel;
}

double calcularMediaIdadePassageiros(const Viagem &viagem)
{
    if (viagem.passagens.empty())
    {
        return 0.0;
    }

    int somaIdades = 0;
    for (const Passagem &passagem : viagem.passagens)
    {
        somaIdades += passagem.idade;
    }

    return static_cast<double>(somaIdades) / viagem.passagens.size();
}

string obterNomePassageiro(const vector<Viagem> &viagens)
{
    int numeroViagem, numeroAssento;
    string dataViagem;

    cout << "Digite a data da viagem: ";
    cin >> dataViagem;

    bool encontrou = false;

    for (const Viagem &viagem : viagens)
    {
        for (const Passagem &passagem : viagem.passagens)
        {
            if (passagem.data == dataViagem)
            {
                encontrou = true;
            }
        }
    }

    if (encontrou)
    {
        cout << "Encontrada viagem nessa data" << endl;
    }
    else
    {
        return "Nao encontrado viagens na data especificada";
    }

    cout << "Digite o numero da viagem: ";
    cin >> numeroViagem;

    if (numeroViagem < 1 || numeroViagem > 10)
    {
        return "Numero de viagem inválido.";
    }

    cout << "Digite o numero da poltrona: ";
    cin >> numeroAssento;

    for (const Viagem &viagem : viagens)
    {
        if (viagem.numeroViagem == numeroViagem)
        {
            for (const Passagem &passagem : viagem.passagens)
            {
                if (passagem.numeroAssento == numeroAssento)
                {
                    return "Passageiro encontrado: " + passagem.nome;
                }
            }
        }
    }
    return "Poltrona vazia";
}

int main()
{
    vector<Viagem> viagens;
    srand(time(0)); 

    for (int i = 1; i <= 5; ++i)
    {
        viagens.push_back(Viagem(i, "Rio de Janeiro", "Bahia", rand() % 5 + 1));
        viagens.push_back(Viagem(i + 5, "Sergipe", "Roraima", rand() % 5 + 1));
    }

    // Simulate ticket sales
    viagens[0].passagens.push_back(Passagem(1, "09/11/2023", 2, "09871234567", "Joao", 30, 80.0));
    viagens[0].passagens.push_back(Passagem(2, "14/08/2023", 2, "98765432109", "Pedro", 25, 80.0));
    viagens[0].passagens.push_back(Passagem(3, "15/09/2023", 2, "12345678901", "Cleisque", 35, 80.0));

    int escolha;
    do
    {
        cout << "Escolha uma opcao:" << endl;
        cout << "1. Calcular o total arrecadado para uma viagem" << endl;
        cout << "2. Calcular o total arrecadado em um determinado mes" << endl;
        cout << "3. Encontrar o horario de viagem mais rentavel" << endl;
        cout << "4. Calcular a media de idade dos passageiros" << endl;
        cout << "5. Encontrar o nome do passageiro de uma determinada poltrona" << endl;
        cout << "0. Sair do programa" << endl;

        cin >> escolha;

        switch (escolha)
        {
        case 1:
        {
            int numeroViagem;
            cout << "Digite o numero da viagem: ";
            cin >> numeroViagem;

            if (numeroViagem >= 1 && numeroViagem <= 10)
            {
                cout << "Total arrecadado para a viagem " << numeroViagem << ": " << calcularTotalArrecadadoViagem(viagens[numeroViagem - 1]) << " reais" << endl;
            }
            else
            {
                cout << "Numero de viagem invalido." << endl;
            }
            break;
        }
        case 2:
        {
            int mes;
            cout << "Digite o numero do mes (1 a 12): ";
            cin >> mes;

            if (mes >= 1 && mes <= 12)
            {
                cout << "Total arrecadado em " << mes << ": " << calcularTotalArrecadadoMes(viagens, mes) << " reais" << endl;
            }
            else
            {
                cout << "Mes invalido." << endl;
            }
            break;
        }
        case 3:
        {
            int horarioMaisRentavel = encontrarHorarioMaisRentavel(viagens);
            cout << "Horario mais rentavel: " << horarioMaisRentavel << endl;
            break;
        }
        case 4:
        {
            int numeroViagem;
            cout << "Digite o numero da viagem: ";
            cin >> numeroViagem;

            if (numeroViagem >= 1 && numeroViagem <= 10)
            {
                cout << "Media de idade dos passageiros na viagem " << numeroViagem << ": " << fixed << setprecision(2) << calcularMediaIdadePassageiros(viagens[numeroViagem - 1]) << " anos" << endl;
            }
            else
            {
                cout << "Numero de viagem invalido." << endl;
            }
            break;
        }
        case 5:
            cout << obterNomePassageiro(viagens) << endl;
            break;
        case 0:
            cout << "Encerrando o programa." << endl;
            break;
        default:
            cout << "Opcao invalida. Tente novamente." << endl;
        }
    } while (escolha != 0);

    return 0;
}
