#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

    static int contadorCodigo;
    public:
    
    Passageiro() : id(contadorCodigo++), fidelidade(false), pontosFidelidade(0) {}

    Passageiro(const string& n, const string& e, const string& t, bool f, int p)
        : nome(n), endereco(e), telefone(t), fidelidade(f), pontosFidelidade(p) {
        id = contadorCodigo++;  }
    
    int getId() const { return id; }
    string getNome() const { return nome; }
    bool ehFiel() const { return fidelidade; }

    void visualizar() const {
        std::cout << "Código: " << id << "\n";
        std::cout << "Nome: " << nome << "\n";
        std::cout << "Endereço: " << endereco << "\n";
        std::cout << "Telefone: " << telefone << "\n";
        std::cout << "Fidelidade: " << (fidelidade ? "Sim" : "Não") << "\n";
        std::cout << "Pontos de Fidelidade: " << pontosFidelidade << "\n";
    }
    void cadastrar() {
        std::cout << "Informe o nome: ";
        std::getline(std::cin, nome);
        std::cout << "Informe o endereço: ";
        std::getline(std::cin, endereco);
        std::cout << "Informe o telefone: ";
        std::getline(std::cin, telefone);
        std::cout << "Fidelidade (1 - Sim, 0 - Não): ";
        std::cin >> fidelidade;
        pontosFidelidade = 0;  
        std::cin.ignore(); 
    }
};
/*TRIPULAÇÃO: código, nome, telefone, cargo (piloto, copiloto, comissário).*/
class Tripulacao{
    public:
        enum class Cargo{ //1=piloto, 2==copiloto, 3 == comissario
            Piloto = 1,
            Copiloto = 2,
            Comissario = 3
        };

    private:

    int id;
    static int contadorCodigo;
    
    string nome;
    string telefone;
    Cargo cargo;

    public:

    Tripulacao() : id(contadorCodigo++) {}

    Tripulacao(const string& n, const string& t, Cargo c)
        : nome(n), telefone(t), cargo(c){
        id = contadorCodigo++;  }
    
    int getId() const {return id;}
    Cargo getCargo() const {return cargo;}

};
/*VOO: código do voo, data, hora, origem, destino, código do avião, código do piloto,
código do copiloto, código do comissário, status (ativo/inativo), tarifa.*/
class Voo{
    private:
    int id;
    static int contadorCodigo;

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
    Voo() : id(contadorCodigo++), status(false) {}

    Voo(const string& d, const string& h, const string& o, const string& dt, 
    int aviao, int piloto, int copiloto, int comissario, bool s, double preco) 
    : id(contadorCodigo++), data(d), hora(h), origem(o), destino(dt),
      idAviao(aviao), idPiloto(piloto), idCopiloto(copiloto), 
      idComissario(comissario), status(s), tarifa(preco) {}

};

/*ASSENTO: número do assento, código do voo, status (ocupado/livre).*/
class Assento{
    private:
    int numAssento;
    int idVoo;
    bool status;
    public: 
    Assento() : numAssento(0), idVoo(0) , status(false) {}
    Assento(int assento, int voo, bool s) : numAssento(assento), idVoo(voo), status(s) {}
    int getAssento() const { return numAssento; }
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
    Reserva() : idVoo(0), numAssento(0), idPassageiro(0) {}
    Reserva(int cod, int assento, int passageiro) 
        : idVoo(cod), numAssento(assento), idPassageiro(passageiro) {}
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

void pesquisa(){
    int opcao, pesquisa;
    do
    {
        cout << "Pesquisa" << endl;
        cout << "Escolha uma opção:" << endl;
        cout << "1-Pesquisar Passageiro" << endl;
        cout << "2-Pesquisar Tripulação" << endl;
        cout << "3-Sair" << endl;
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            cout << "Pesquisa Passageiro" << endl;
            cout << "1-Pesquisar por ID" << endl;
            cout << "2-Pesquisar por nome" << endl;
            cout << "Escolha uma opção:" << endl;
            cin >> pesquisa;
            if (pesquisa == 1)
            {
                
            }
            
            break;
        case 2:
            cout << "Pesquisa Passageiro" << endl;
            cout << "1-Pesquisar por ID" << endl;
            cout << "2-Pesquisar por nome" << endl;
            cout << "Escolha uma opção:" << endl;
            cin >> pesquisa;
            break;
        case 3:
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opção inválida!" << endl;
            break;
        }
    } while (opcao != 3);
    
}


void menu(){
    int opcao;
    do
    {
        cout << "MENU - Companhia Voo Seguro" << endl;
        cout << "1-Cadastrar Passageiro" << endl;
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
            pesquisa();
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

int Passageiro::contadorCodigo = 1;
int Tripulacao::contadorCodigo = 1;

int main(){
    menu();

    return 0;
}