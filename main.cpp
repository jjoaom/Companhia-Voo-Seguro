#include <iostream> //bib padrão
#include <iomanip> //bib conversão double
#include <string> //bib string
#include <fstream> //bib file
#include <vector> //bib vector

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
        cout << "ID: " << id << endl;
        cout << "Nome: " << nome << endl;
        cout << "Endereço: " << endereco << endl;
        cout << "Telefone: " << telefone << endl;
        cout << "Fidelidade: " << (fidelidade ? "Sim" : "Não") << endl;
        cout << "Pontos de Fidelidade: " << pontosFidelidade << endl;
        cout << "---------------------" << endl;
    }
    void cadastrar() {
        cout << "Informe o nome: " << endl;
        getline(cin, nome);
        cout << "Informe o endereço: " << endl;
        getline(cin, endereco);
        cout << "Informe o telefone: " << endl;
        getline(cin, telefone);
        cout << "Fidelidade (1 - Sim, 0 - Não): " << endl;
        cin >> fidelidade;
        pontosFidelidade = 0;  
        cin.ignore(); 
    }
};
int Passageiro::contadorCodigo = 1; // Contador de ID estático

/*TRIPULAÇÃO: código, nome, telefone, cargo (piloto, copiloto, comissário).*/
class Tripulacao{
    public:
        enum class Cargo{ //1=piloto, 2=copiloto, 3=comissario
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

    //metodo estático para converter o tipo do cargo para string
    static string cargoParaString(Cargo cargo) {
        switch (cargo) {
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

    Tripulacao() : id(contadorCodigo++) {}

    Tripulacao(const string& n, const string& t, Cargo c)
        : nome(n), telefone(t), cargo(c){
        id = contadorCodigo++;  }
    
    int getId() const { return id; }
    string getNome() const { return nome; }
    Cargo getCargo() const {return cargo;}

    void visualizar() const {
        cout << "ID: " << id << endl;
        cout << "Nome: " << nome << endl;
        cout << "Telefone: " << telefone << endl;
        cout << "Cargo: " << cargoParaString(cargo) << endl;
        cout << "---------------------" << endl;
    }
    void cadastrar() {
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
        cargo = static_cast<Cargo>(cargoEscolhido); //converte o valor digitado para o usuário para o tipo enum
        cin.ignore();
    }

};
int Tripulacao::contadorCodigo = 1; // Contador de ID estático

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
int Voo::contadorCodigo = 1; // Contador de ID estático

/*ASSENTO: número do assento, código do voo, status (ocupado/livre).*/
class Assento{
    private:
    int numAssento;
    int idVoo;
    bool ocupado;
    public: 
    Assento() : numAssento(0), idVoo(0) , ocupado(false) {}
    Assento(int assento, int voo, bool s) : numAssento(assento), idVoo(voo), ocupado(s) {}
    int getAssento() const { return numAssento; }
    void setAssento(int assento) { numAssento = assento;}
    int getIdVoo() const { return idVoo; }
    void setIdVoo(int id) { idVoo = id;}
    bool isOcupado() const { return ocupado;}
    void ocupar() { 
        if (!ocupado)
        {
            ocupado = true;
        }else{
            cout << "O assento " << numAssento << " já está ocupado." << endl; 
        }
        
    }
    void liberar() { 
        if (ocupado)
        {
            ocupado = false;
        }else{
            cout << "O assento " << numAssento << " já está livre." << endl; 
        }
        
    }
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
    void setIdVoo(int id) { idVoo = id;}
    int getNumAssento() const { return numAssento; }
    void setAssento(int assento) { numAssento = assento;}
    int getIdPassageiro() const { return idPassageiro; }
    void setIdPassageiro(int id ) { idPassageiro = id;}
};


/*O que são templates? Templates são uma característica na linguagem que permite escrever um código genérico que pode ser reutilizado para diferentes tipos.*/
//template para manipulação dos arquivos binários
template <typename T>
void salvarArqBinario(const vector<T>& vetor, const string& nomeArquivo){
    ofstream arq(nomeArquivo, ios::binary);
    if (!arq)
    {
        cerr << "Erro ao abrir arquivo para escrita." << endl;
        return;
    }
    //size_t é um tipo que serve para representar tamanhos e contagens
    size_t tamanho = vetor.size();
    //reinterpret_cast serve para realizar conversões diretas
    arq.write(reinterpret_cast<const char*>(&tamanho),sizeof(tamanho)); //tamanho do vetor
    //Gravação de dados do vetor
    //loop para percorrer o vetor, o tipo auto serve para deduzir automaticamente o tipo do vetor
    for (const auto& item : vetor)
    {
        arq.write(reinterpret_cast<const char*>(&item),sizeof(item));
    }
    arq.close();
}
//template para leitura dos arquivos binários
template <typename T>
vector<T> lerArqBinario(const string& nomeArquivo){
    ifstream arq(nomeArquivo,ios::binary);
    vector<T> vetor;

    if(!arq){
        cerr << "Erro ao abrir o arquivo para leitura." << endl;
        return;
    }

    size_t tamanho;
    arq.read(reinterpret_cast<char*>(&tamanho),sizeof(tamanho)); //tamanho do vetor
    for (size_t i = 0; i < tamanho; ++i)
    {
        T item;
        arq.read(reinterpret_cast<char*>(&item),sizeof(item));
        vetor.push_back(item);
    }
    return vetor;
}



/*Funcionalidades a Implementar:*/
/*1. Cadastro de Passageiro:
    o Deve garantir que não haja dois passageiros com o mesmo código.
    o Opcionalmente, pode-se gerar o código automaticamente.*/


/*2. Cadastro de Tripulação:
    o Cada membro da tripulação deve ter um cargo específico.
    o Deve garantir que não haja dois membros da tripulação com o mesmo código.
    o Opcionalmente, pode-se gerar o código automaticamente.*/


/*3. Cadastro de Voo:
    o Deve ser possível cadastrar informações sobre data, hora, origem, destino, tarifa,
    tripulação e o avião.
    o Deve verificar a presença de ao menos um piloto e um copiloto para que o voo
    seja marcado como ativo.*/


/*4. Cadastro de Assento:
    o Deve ser possível cadastrar os assentos de cada voo.*/
void cadastrarAssentos(){
    int idVoo, numAssentos;
    cout << "Cadastro de Assento" << endl;
    cout << "Insira o ID do Voo: " << endl;
    cin >> idVoo;
    cout << "Insira a quantidade de assentos disponíveis no voo: " << endl;
    cin >> numAssentos;
    vector<Assento> Assentos;
    for (int i = 1; i <= numAssentos; i++)
    {
        Assento novoAssento;
        novoAssento.setIdVoo(idVoo);
        novoAssento.setAssento(i);
        novoAssento.liberar(); //certifica que todos os assentos cadastrados já estejam liberados
        Assentos.push_back(novoAssento);
    }
    salvarArqBinario(Assentos, "assentos.bin");
}

/*5. Reserva:
    o Deve garantir que o assento esteja disponível antes de reservar.
    o Reservas duplicadas para o mesmo assento no mesmo voo devem ser evitadas.*/


/*6. Baixa em Reserva:
    o Deve liberar o assento e atualizar o status para livre.
    o Calcular o valor total a ser pago, se necessário, de acordo com a tarifa do voo.*/

/*7. Pesquisa:
    o Deve ser possível buscar passageiros e membros da tripulação pelo nome ou
    código.
    o Deve ser possível listar todos os voos de um determinado passageiro.*/

int menuPesquisa(int& buscaId, string& buscaNome){
    int pesquisa;
    do
    {
        cout << "Pesquisa Passageiro" << endl;
        cout << "1-Pesquisar por ID" << endl;
        cout << "2-Pesquisar por nome" << endl;
        cout << "Escolha uma opção:" << endl;
        cin >> pesquisa;
    } while (pesquisa != 1 && pesquisa != 2);

    if (pesquisa == 1){
        cout << "Insira o ID a ser buscado:" << endl;
        cin >> buscaId;
    }else if(pesquisa == 2){
        cout << "Insira o nome a ser buscado:" << endl;
        cin.ignore();
        getline(cin,buscaNome);
    }
    return pesquisa;
}

void pesquisaPassageiro()
{
    int buscaId;
    string buscaNome;
    int tipoPesquisa = menuPesquisa(buscaId, buscaNome);
    vector<Passageiro> passageirosLidos = lerArqBinario<Passageiro>("passageiros.bin");
    for (const auto &p : passageirosLidos)
    {
        if (tipoPesquisa == 1){
            if (p.getId() == buscaId)
            {
                p.visualizar();
            }
            
        }
        else if (tipoPesquisa == 2){
            if (p.getNome() == buscaNome)
            {
                p.visualizar();
            }
            
        }
    }
}

void pesquisarTripulacao(){
    int buscaId;
    string buscaNome;
    int tipoPesquisa = menuPesquisa(buscaId, buscaNome);
    vector<Tripulacao> tripulacaoLidos = lerArqBinario<Tripulacao>("tripulacao.bin");
    for (const auto &t : tripulacaoLidos)
    {
        if (tipoPesquisa == 1){
            if (t.getId() == buscaId)
            {
                t.visualizar();
            }
            
        }
        else if (tipoPesquisa == 2){
            if (t.getNome() == buscaNome)
            {
                t.visualizar();
            }
            
        }
    }
}

void pesquisa(){
    int opcao;
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
            pesquisaPassageiro();
            break;
        case 2:
            pesquisarTripulacao();
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

/*8. Programa de Fidelidade:
    o Cada voo concede 10 pontos de fidelidade ao passageiro.
    o Um passageiro pode acumular pontos ao longo de múltiplos voos.*/



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
    //Vectors das classes a serem manipuladas por arquivo
    vector<Passageiro> passageiros;
    vector<Tripulacao> tripulantes;
    vector<Voo> voos;
    vector<Assento> assentos;
    vector<Reserva> reservas;

    return 0;
}