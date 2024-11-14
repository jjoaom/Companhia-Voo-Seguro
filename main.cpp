#include <iostream>
#include <string>

using namespace std;

class Passageiro{
    private:
    int id;
    string nome;
    string endereco;
    string telefone;
    bool fidelidade;
    int pontosFidelidade;
    public:

};
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

};
class Voo{
    private:
    int id;

    
};

class Assento{
    private:
    int id;
    int idVoo;
    bool status;
};

class Reserva{
    private:
    int idVoo;
    int numAssento;
    int idPassageiro;
};

void menu(){

}