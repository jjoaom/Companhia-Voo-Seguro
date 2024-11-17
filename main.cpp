#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*PASSAGEIRO: código, nome, endereço, telefone, fidelidade (sim/não), pontos
fidelidade.*/
class Passageiro{
    private:
    int id;
    string nome;
    string endereco;
    string telefone;
    bool fidelidade;
    int pontosFidelidade;
    public:
    
    Passageiro(int cod, string nm, string ender, string tel, bool fid = false, int pontos = 0) : id(cod),nome(nm),endereco(end),telefone(tel),fidelidade(fid), pontosFidelidade(pontos) {}

    int getId() const { return id; }
    string getNome() const { return nome; }
    bool ehFiel() const { return fidelidade; }

};
/*TRIPULAÇÃO: código, nome, telefone, cargo (piloto, copiloto, comissário).*/
class Tripulacao{
    public:
        enum class Cargo{
            Piloto,
            Copiloto,
            Comissario
        };
    private:
    int id;
    string nome;
    string telefone;
    Cargo cargo;
    public:
    Tripulacao(int cod, string nm, string tel, Cargo cg) : id(cod), nome(nm), telefone(tel), cargo(cg) {} 
    int getId() const {return id;}
    Cargo getCargo() const {return cargo;}

};
/*VOO: código do voo, data, hora, origem, destino, código do avião, código do piloto,
código do copiloto, código do comissário, status (ativo/inativo), tarifa.*/
class Voo{
    private:
    int id;
    string data;
    string hora;
    string origem;
    string destino;
    int idAviao;
    int idPiloto;
    int idCopiloto;
    int idComissario;
    bool status;
    double tarifa;
    
    public:
};

/*ASSENTO: número do assento, código do voo, status (ocupado/livre).*/
class Assento{
    private:
    int id;
    int idVoo;
    bool status;
    public: 
    Assento(int cod, int voo, bool stats = false) : id(cod), idVoo(voo), status(stats) {}
    int getId() const { return id; }
    int getIdVoo() const { return idVoo; }
    bool isOcupado() const { return status;}
    void reservar() { status = true; }
    void liberar() { status = false; }
};
/*RESERVA: código do voo, número do assento, código do passageiro.*/
class Reserva{
    private:
    int idVoo;
    int numAssento;
    int idPassageiro;
    public:
    Reserva(int cod, int assento, int passageiro) : idVoo(cod), numAssento(assento), idPassageiro(passageiro) {}
    int getIdVoo() const { return idVoo; }
    int getNumAssento() const { return numAssento; }
    int getIdPassageiro() const { return idPassageiro; }
};

/*Funcionalidades a Implementar:
1. Cadastro de Passageiro:
    o Deve garantir que não haja dois passageiros com o mesmo código.
    o Opcionalmente, pode-se gerar o código automaticamente.
2. Cadastro de Tripulação:
    o Cada membro da tripulação deve ter um cargo específico.
    o Deve garantir que não haja dois membros da tripulação com o mesmo código.
    o Opcionalmente, pode-se gerar o código automaticamente.
3. Cadastro de Voo:
    o Deve ser possível cadastrar informações sobre data, hora, origem, destino, tarifa,
    tripulação e o avião.
    o Deve verificar a presença de ao menos um piloto e um copiloto para que o voo
    seja marcado como ativo.
4. Cadastro de Assento:
    o Deve ser possível cadastrar os assentos de cada voo.
5. Reserva:
    o Deve garantir que o assento esteja disponível antes de reservar.
    o Reservas duplicadas para o mesmo assento no mesmo voo devem ser evitadas.
6. Baixa em Reserva:
    o Deve liberar o assento e atualizar o status para livre.
    o Calcular o valor total a ser pago, se necessário, de acordo com a tarifa do voo.
7. Pesquisa:
    o Deve ser possível buscar passageiros e membros da tripulação pelo nome ou
    código.
    o Deve ser possível listar todos os voos de um determinado passageiro.
8. Programa de Fidelidade:
    o Cada voo concede 10 pontos de fidelidade ao passageiro.
    o Um passageiro pode acumular pontos ao longo de múltiplos voos.    
    */
void menu(){
    int opcao;
    do
    {
        cout << "MENU - Companhia Voo Seguro" << endl;
        cout << "1-Cadastrar Passaeiro" << endl;
        cout << "2-Cadastrar Tripulação" << endl;
        cout << "3-Cadastrar Voo" << endl;
        cout << "4-Cadastrar Assento" << endl;
        cout << "5-Reserva" << endl;
        cout << "6-Baixar Reserva" << endl;
        cout << "7-Pesquisa" << endl;
        cout << "8-Programa Fidelidade" << endl;
        cout << "9-Sair" << endl;
        cout << "Escolha uma opção: " << endl;
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            /* 1 */
            break;
        case 2:
            /* 2 */
            break;
        case 3:
            /* 3 */
            break;
        case 4:
            /* 4 */
            break;
        case 5:
            /* 5 */
            break;
        case 6:
            /* 6 */
            break;
        case 7:
            /* 7 */
            break;
        case 8:
            /* 8 */
            break;
        case 9:
            cout << "Saindo..." << endl;
            break;
        
        default:
            cout << "Opção inválida!" << endl;
            break;
        }
    } while (opcao != 9);
}

int main(){
    menu();

    return 0;
}