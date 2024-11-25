#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <iostream>   //bib padrão
#include <iomanip>    //bib imprimir double formatado
#include <string>     //bib string
#include <fstream>    //bib file
#include <vector>     //bib vector
#include <limits>     //bib limits para limpeza de buffer
#include <functional> //bib para criar funções que recebem trecho de código
#include <stdexcept>  //bib para tratamento de exceção
#include <cstdlib>    //bib para sistema
#include "templates.hpp" // Incluindo o arquivo de templates para usar os templates definidos

using namespace std;

/*PASSAGEIRO: código, nome, endereço, telefone, fidelidade (sim/não), pontos
fidelidade.*/
class Passageiro
{
private:
    int id;
    string nome;
    string endereco;
    string telefone;
    bool fidelidade;
    int pontosFidelidade;

    static int contadorId;

public:
    Passageiro() : id(contadorId), fidelidade(false), pontosFidelidade(0) {}

    Passageiro(const string &n, const string &e, const string &t, bool f, int p)
        : nome(n), endereco(e), telefone(t), fidelidade(f), pontosFidelidade(p)
    {
        id = contadorId;
    }

    int getId() const { return id; }
    void setId(int newId) { id = newId; }
    static int getContador() { return contadorId; }
    static void setContador(int newId) { contadorId = newId; }
    string getNome() const { return nome; }
    bool ehFiel() const { return fidelidade; }
    int getPontosFidelidade() const { return pontosFidelidade; }
    void setPontosFidelidade(int newPonto) { pontosFidelidade = newPonto; }
    void increaseFidelidade() { pontosFidelidade += 10; }

    void visualizar() const
    {
        cout << "|" << endl;
        cout << "|ID: " << id << endl;
        cout << "|Nome: " << nome << endl;
        cout << "|Endereço: " << endereco << endl;
        cout << "|Telefone: " << telefone << endl;
        cout << "|Fidelidade: " << (fidelidade ? "Sim" : "Não") << endl;
        if (fidelidade)
        {
            cout << "|Pontos de Fidelidade: " << pontosFidelidade << endl;
        }

        cout << "|_____________________________|" << endl;
    }
    void cadastrar()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Informe o nome: " << endl;
        getline(cin, nome);
        cout << "Informe o endereço: " << endl;
        getline(cin, endereco);
        cout << "Informe o telefone: " << endl;
        getline(cin, telefone);
        cout << "Fidelidade (1 - Sim, 0 - Não): " << endl;
        cin >> fidelidade;
        while (fidelidade != 0 && fidelidade != 1)
        {
            cout << "Entrada inválida. Informe 1 para Sim ou 0 para Não: ";
            cin >> fidelidade;
        }
        cin.ignore();
        pontosFidelidade = 0;
    }
    // metodos para salvar e ler nos arq binarios
    void salvar(ofstream &arq) const
    {
        arq.write(reinterpret_cast<const char *>(&id), sizeof(id));
        size_t nomeSize = nome.size();
        arq.write(reinterpret_cast<const char *>(&nomeSize), sizeof(nomeSize));
        arq.write(nome.c_str(), nomeSize);
        size_t enderecoSize = endereco.size();
        arq.write(reinterpret_cast<const char *>(&enderecoSize), sizeof(enderecoSize));
        arq.write(endereco.c_str(), enderecoSize);
        size_t telefoneSize = telefone.size();
        arq.write(reinterpret_cast<const char *>(&telefoneSize), sizeof(telefoneSize));
        arq.write(telefone.c_str(), telefoneSize);
        arq.write(reinterpret_cast<const char *>(&fidelidade), sizeof(fidelidade));
        arq.write(reinterpret_cast<const char *>(&pontosFidelidade), sizeof(pontosFidelidade));
    }
    void ler(ifstream &arq)
    {
        arq.read(reinterpret_cast<char *>(&id), sizeof(id));
        size_t nomeSize;
        arq.read(reinterpret_cast<char *>(&nomeSize), sizeof(nomeSize));
        nome.resize(nomeSize);
        arq.read(&nome[0], nomeSize);
        size_t enderecoSize;
        arq.read(reinterpret_cast<char *>(&enderecoSize), sizeof(enderecoSize));
        endereco.resize(enderecoSize);
        arq.read(&endereco[0], enderecoSize);
        size_t telefoneSize;
        arq.read(reinterpret_cast<char *>(&telefoneSize), sizeof(telefoneSize));
        telefone.resize(telefoneSize);
        arq.read(&telefone[0], telefoneSize);
        arq.read(reinterpret_cast<char *>(&fidelidade), sizeof(fidelidade));
        arq.read(reinterpret_cast<char *>(&pontosFidelidade), sizeof(pontosFidelidade));
    }
};

/*TRIPULAÇÃO: código, nome, telefone, cargo (piloto, copiloto, comissário).*/
class Tripulacao
{
public:
    enum class Cargo
    { // 1=piloto, 2=copiloto, 3=comissario
        Piloto = 1,
        Copiloto = 2,
        Comissario = 3
    };

private:
    int id;
    static int contadorId;

    string nome;
    string telefone;
    Cargo cargo;

    // metodo estático para converter o tipo do cargo para string
    static string cargoParaString(Cargo cargo)
    {
        switch (cargo)
        {
        case Cargo::Piloto:
            return "Piloto";
        case Cargo::Copiloto:
            return "Copiloto";
        case Cargo::Comissario:
            return "Comissário";
        default:
            return "Desconhecido";
        }
    }

public:
    Tripulacao() : id(contadorId) {}

    Tripulacao(const string &n, const string &t, Cargo c)
        : nome(n), telefone(t), cargo(c)
    {
        id = contadorId;
    }

    static int getContador() { return contadorId; }
    static void setContador(int newId) { contadorId = newId; }

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    string getNome() const { return nome; }
    Cargo getCargo() const { return cargo; }
    int verificaCargo(int cargo) const
    {
        if (cargo == 1)
        {
            return 1;
        }
        else if (cargo == 2)
        {
            return 2;
        }
        else if (cargo == 3)
        {
            return 3;
        }
        return -1;
    }

    void visualizar() const
    {
        cout << "|" << endl;
        cout << "ID: " << id << endl;
        cout << "Nome: " << nome << endl;
        cout << "Telefone: " << telefone << endl;
        cout << "Cargo: " << cargoParaString(cargo) << endl;
        cout << "|_____________________________|" << endl;
    }
    void cadastrar()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Informe o nome: " << endl;
        getline(cin, nome);
        cout << "Informe o telefone: " << endl;
        getline(cin, telefone);
        int cargoEscolhido;
        do
        {
            cout << "Cargo: (1-Piloto, 2-Copiloto, 3-Comissário) " << endl;
            cin >> cargoEscolhido;
        } while (cargoEscolhido < 1 || cargoEscolhido > 3);
        cargo = static_cast<Cargo>(cargoEscolhido); // converte o valor digitado para o usuário para o tipo enum
        cin.ignore();
    }
    // metodos para salvar e ler nos arq binarios
    void salvar(ofstream &arq) const
    {
        arq.write(reinterpret_cast<const char *>(&id), sizeof(id));
        size_t nomeSize = nome.size();
        arq.write(reinterpret_cast<const char *>(&nomeSize), sizeof(nomeSize));
        arq.write(nome.c_str(), nomeSize);
        size_t telefoneSize = telefone.size();
        arq.write(reinterpret_cast<const char *>(&telefoneSize), sizeof(telefoneSize));
        arq.write(telefone.c_str(), telefoneSize);
        arq.write(reinterpret_cast<const char *>(&cargo), sizeof(cargo));
    }
    void ler(ifstream &arq)
    {
        arq.read(reinterpret_cast<char *>(&id), sizeof(id));
        size_t nomeSize;
        arq.read(reinterpret_cast<char *>(&nomeSize), sizeof(nomeSize));
        nome.resize(nomeSize);
        arq.read(&nome[0], nomeSize);
        size_t telefoneSize;
        arq.read(reinterpret_cast<char *>(&telefoneSize), sizeof(telefoneSize));
        telefone.resize(telefoneSize);
        arq.read(&telefone[0], telefoneSize);
        arq.read(reinterpret_cast<char *>(&cargo), sizeof(cargo));
    }
};

/*VOO: código do voo, data, hora, origem, destino, código do avião, código do piloto,
código do copiloto, código do comissário, status (ativo/inativo), tarifa.*/
class Voo
{
private:
    int id;
    static int contadorId;

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
    Voo() : id(contadorId), status(false) {}

    Voo(const string &d, const string &h, const string &o, const string &dt,
        int aviao, int piloto, int copiloto, int comissario, bool s, double preco)
        : id(contadorId), data(d), hora(h), origem(o), destino(dt),
          idAviao(aviao), idPiloto(piloto), idCopiloto(copiloto),
          idComissario(comissario), status(s), tarifa(preco) {}

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    static int getContador() { return contadorId; }
    static void setContador(int newId) { contadorId = newId; }
    int getIdPiloto() const { return idPiloto; }
    void setIdPiloto(int id) { idPiloto = id; }
    int getIdCopiloto() const { return idCopiloto; }
    void setIdCopiloto(int id) { idCopiloto = id; }
    int getIdComissario() const { return idComissario; }
    void setIdComissario(int id) { idComissario = id; }
    bool getStatus() const { return status; }
    void setStatus(bool s) { status = s; }
    double getTarifa() const { return tarifa; }
    void setTarifa(double novaTarifa) { tarifa = novaTarifa; }

    void visualizar() const
    {
        cout << "|" << endl;
        cout << "| ID: " << id << endl;
        cout << "| Data: " << data << " | " << "Hora:" << hora << endl;
        cout << "| Origem: " << origem << endl;
        cout << "| Destino: " << destino << endl;
        cout << "| Avião nº: " << idAviao << endl;
        cout << "| Nº Piloto: " << idPiloto << endl;
        cout << "| Nº Copiloto: " << idCopiloto << endl;
        cout << "| Nº Comissario: " << idComissario << endl;
        cout << "| Status do Voo: " << (status ? "Ativo" : "Inativo") << endl;
        cout << "| Tarifa: R$" << fixed << setprecision(2) << tarifa << endl;
        cout << "|_____________________________|" << endl;
    }
    void cadastrar()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Informe a data(DD/MM/AAAA) do voo: " << endl;
        getline(cin, data);

        cout << "Informe a hora(HH/MM) do voo: " << endl;
        getline(cin, hora);

        cout << "Informe a origem: " << endl;
        getline(cin, origem);

        cout << "Informe o destino: " << endl;
        getline(cin, destino);

        cout << "Insira o id do avião: " << endl;
        cin >> idAviao;
        cin.ignore();
        cout << "Insira o id do piloto: " << endl;
        cin >> idPiloto;
        cin.ignore();
        cout << "Insira o id do copiloto: " << endl;
        cin >> idCopiloto;
        cin.ignore();
        cout << "Insira o id do comissário: " << endl;
        cin >> idComissario;
        cin.ignore();
        cout << "Insira a tarifa do voo: " << endl;
        cin >> tarifa;
        while (tarifa <= 0)
        {
            cout << "Entrada inválida. Informe um valor acima de 0: " << endl;
            cin >> tarifa;
        }
        cin.ignore();
    }
    // metodos para salvar e ler nos arq binarios
    void salvar(ofstream &arq) const
    {
        arq.write(reinterpret_cast<const char *>(&id), sizeof(id));

        size_t dataSize = data.size();
        arq.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));
        arq.write(data.c_str(), dataSize);

        size_t horaSize = hora.size();
        arq.write(reinterpret_cast<const char *>(&horaSize), sizeof(horaSize));
        arq.write(hora.c_str(), horaSize);

        size_t origemSize = origem.size();
        arq.write(reinterpret_cast<const char *>(&origemSize), sizeof(origemSize));
        arq.write(origem.c_str(), origemSize);

        size_t destinoSize = destino.size();
        arq.write(reinterpret_cast<const char *>(&destinoSize), sizeof(destinoSize));
        arq.write(destino.c_str(), destinoSize);

        arq.write(reinterpret_cast<const char *>(&idAviao), sizeof(idAviao));
        arq.write(reinterpret_cast<const char *>(&idPiloto), sizeof(idPiloto));
        arq.write(reinterpret_cast<const char *>(&idCopiloto), sizeof(idCopiloto));
        arq.write(reinterpret_cast<const char *>(&idComissario), sizeof(idComissario));
        arq.write(reinterpret_cast<const char *>(&status), sizeof(status));
        arq.write(reinterpret_cast<const char *>(&tarifa), sizeof(tarifa));
    }
    void ler(ifstream &arq)
    {
        arq.read(reinterpret_cast<char *>(&id), sizeof(id));

        size_t dataSize;
        arq.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
        data.resize(dataSize);
        arq.read(&data[0], dataSize);

        size_t horaSize;
        arq.read(reinterpret_cast<char *>(&horaSize), sizeof(horaSize));
        hora.resize(horaSize);
        arq.read(&hora[0], horaSize);

        size_t origemSize;
        arq.read(reinterpret_cast<char *>(&origemSize), sizeof(origemSize));
        origem.resize(origemSize);
        arq.read(&origem[0], origemSize);

        size_t destinoSize;
        arq.read(reinterpret_cast<char *>(&destinoSize), sizeof(destinoSize));
        destino.resize(destinoSize);
        arq.read(&destino[0], destinoSize);

        arq.read(reinterpret_cast<char *>(&idAviao), sizeof(idAviao));
        arq.read(reinterpret_cast<char *>(&idPiloto), sizeof(idPiloto));
        arq.read(reinterpret_cast<char *>(&idCopiloto), sizeof(idCopiloto));
        arq.read(reinterpret_cast<char *>(&idComissario), sizeof(idComissario));
        arq.read(reinterpret_cast<char *>(&status), sizeof(status));
        arq.read(reinterpret_cast<char *>(&tarifa), sizeof(tarifa));
    }
};

/*ASSENTO: número do assento, código do voo, status (ocupado/livre).*/
class Assento
{
private:
    int numAssento;
    int idVoo;
    bool ocupado;

public:
    Assento() : numAssento(0), idVoo(0), ocupado(false) {}
    Assento(int assento, int voo, bool s) : numAssento(assento), idVoo(voo), ocupado(s) {}
    int getAssento() const { return numAssento; }
    void setAssento(int assento) { numAssento = assento; }
    int getIdVoo() const { return idVoo; }
    void setIdVoo(int id) { idVoo = id; }
    bool isOcupado() const { return ocupado; }
    void liberado(){
        ocupado = false;
    }
    void ocupar()
    {
        ocupado = true;
    }
    void visualizar()
    {
        cout << left; // Alinha à esquerda
        cout << setw(10) << "Nº Voo: " << setw(10) << idVoo
             << setw(15) << "Nº Assento: " << setw(10) << numAssento
             << setw(20) << "Disponibilidade: " << (ocupado ? "[x]" : "[ ]");
        cout << "|" << endl;
    }

    // metodos para salvar e ler nos arq binarios
    void salvar(ofstream &arq) const
    {
        arq.write(reinterpret_cast<const char *>(&numAssento), sizeof(numAssento));
        arq.write(reinterpret_cast<const char *>(&idVoo), sizeof(idVoo));
        arq.write(reinterpret_cast<const char *>(&ocupado), sizeof(ocupado));
    }
    void ler(ifstream &arq)
    {
        arq.read(reinterpret_cast<char *>(&numAssento), sizeof(numAssento));
        arq.read(reinterpret_cast<char *>(&idVoo), sizeof(idVoo));
        arq.read(reinterpret_cast<char *>(&ocupado), sizeof(ocupado));
    }
};

/*RESERVA: código do voo, número do assento, código do passageiro.*/
class Reserva
{
private:
    int idVoo;
    int numAssento;
    int idPassageiro;

public:
    Reserva() : idVoo(0), numAssento(0), idPassageiro(0) {}
    Reserva(int cod, int assento, int passageiro)
        : idVoo(cod), numAssento(assento), idPassageiro(passageiro) {}
    int getIdVoo() const { return idVoo; }
    void setIdVoo(int id) { idVoo = id; }
    int getNumAssento() const { return numAssento; }
    void setAssento(int assento) { numAssento = assento; }
    int getIdPassageiro() const { return idPassageiro; }
    void setIdPassageiro(int id) { idPassageiro = id; }

    void cadastrar()
    {
        cout << "Insira o número do Voo: " << endl;
        cin >> idVoo;
        cout << "Insira o número do assento escolhido: " << endl;
        cin >> numAssento;
        cout << "Insira o número do passageiro: " << endl;
        cin >> idPassageiro;
    }

    void visualizar()
    {
        cout << "|" << endl;
        cout << "Nº do Voo: " << idVoo << endl;
        cout << "Nº do assento: " << numAssento << endl;
        cout << "Nº do passageiro: " << idPassageiro << endl;
        cout << "|_____________________________|" << endl;
    }

    // metodos para salvar e ler nos arq binarios
    void salvar(ofstream &arq) const
    {
        arq.write(reinterpret_cast<const char *>(&idVoo), sizeof(idVoo));
        arq.write(reinterpret_cast<const char *>(&numAssento), sizeof(numAssento));
        arq.write(reinterpret_cast<const char *>(&idPassageiro), sizeof(idPassageiro));
    }
    void ler(ifstream &arq)
    {
        arq.read(reinterpret_cast<char *>(&idVoo), sizeof(idVoo));
        arq.read(reinterpret_cast<char *>(&numAssento), sizeof(numAssento));
        arq.read(reinterpret_cast<char *>(&idPassageiro), sizeof(idPassageiro));
    }
};



#endif // CLASSES_HPP
