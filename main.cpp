#include <iostream> //bib padrão
#include <iomanip> //bib imprimir double formatado
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

    static int contadorId;
    public:
    
    Passageiro() : id(contadorId++), fidelidade(false), pontosFidelidade(0) {}

    Passageiro(const string& n, const string& e, const string& t, bool f, int p)
        : nome(n), endereco(e), telefone(t), fidelidade(f), pontosFidelidade(p) {
        id = contadorId++;  }
    
    int getId() const { return id; }
    void setId(int newId) { id = newId; }
    static int getContador() { return contadorId; }
    static void setContador(int newId) { contadorId = newId; }
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
        while (fidelidade != 0 && fidelidade != 1)
        {
            cout << "Entrada inválida. Informe 1 para Sim ou 0 para Não: ";
            cin >> fidelidade;
        }
        cin.ignore(); 
        pontosFidelidade = 0;  
        
    }
    //metodos para salvar e ler nos arq binarios
    void salvar(ofstream& arq) const{
        arq.write(reinterpret_cast<const char*>(&id),sizeof(id));
        size_t nomeSize = nome.size();
        arq.write(reinterpret_cast<const char*>(&nomeSize),sizeof(nomeSize));
        arq.write(nome.c_str(),nomeSize);
        size_t enderecoSize = endereco.size();
        arq.write(reinterpret_cast<const char*>(&enderecoSize),sizeof(enderecoSize));
        arq.write(endereco.c_str(),enderecoSize);
        size_t telefoneSize = telefone.size();
        arq.write(reinterpret_cast<const char*>(&telefoneSize), sizeof(telefoneSize));
        arq.write(telefone.c_str(), telefoneSize);
        arq.write(reinterpret_cast<const char*>(&fidelidade), sizeof(fidelidade));
        arq.write(reinterpret_cast<const char*>(&pontosFidelidade), sizeof(pontosFidelidade));
    }
    void ler(ifstream& arq) {
        arq.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t nomeSize;
        arq.read(reinterpret_cast<char*>(&nomeSize), sizeof(nomeSize));
        nome.resize(nomeSize);
        arq.read(&nome[0], nomeSize);
        size_t enderecoSize;
        arq.read(reinterpret_cast<char*>(&enderecoSize), sizeof(enderecoSize));
        endereco.resize(enderecoSize);
        arq.read(&endereco[0], enderecoSize);
        size_t telefoneSize;
        arq.read(reinterpret_cast<char*>(&telefoneSize), sizeof(telefoneSize));
        telefone.resize(telefoneSize);
        arq.read(&telefone[0], telefoneSize);
        arq.read(reinterpret_cast<char*>(&fidelidade), sizeof(fidelidade));
        arq.read(reinterpret_cast<char*>(&pontosFidelidade), sizeof(pontosFidelidade));
    }
};
int Passageiro::contadorId = 1; // Contador de ID estático

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
    static int contadorId;
    
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

    Tripulacao() : id(contadorId++) {}

    Tripulacao(const string& n, const string& t, Cargo c)
        : nome(n), telefone(t), cargo(c){
        id = contadorId++;  }
    
    static int getContador() { return contadorId; }
    static void setContador(int newId) { contadorId = newId; }

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

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
    //metodos para salvar e ler nos arq binarios
    void salvar(ofstream& arq) const{
        arq.write(reinterpret_cast<const char*>(&id),sizeof(id));
        size_t nomeSize = nome.size();
        arq.write(reinterpret_cast<const char*>(&nomeSize),sizeof(nomeSize));
        arq.write(nome.c_str(),nomeSize);
        size_t telefoneSize = telefone.size();
        arq.write(reinterpret_cast<const char*>(&telefoneSize), sizeof(telefoneSize));
        arq.write(telefone.c_str(), telefoneSize);
        arq.write(reinterpret_cast<const char*>(&cargo), sizeof(cargo));
    }
    void ler(ifstream& arq) {
        arq.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t nomeSize;
        arq.read(reinterpret_cast<char*>(&nomeSize), sizeof(nomeSize));
        nome.resize(nomeSize);
        arq.read(&nome[0], nomeSize);
        size_t telefoneSize;
        arq.read(reinterpret_cast<char*>(&telefoneSize), sizeof(telefoneSize));
        telefone.resize(telefoneSize);
        arq.read(&telefone[0], telefoneSize);
        arq.read(reinterpret_cast<char*>(&cargo), sizeof(cargo));
    }
};
int Tripulacao::contadorId = 1; // Contador de ID estático

/*VOO: código do voo, data, hora, origem, destino, código do avião, código do piloto,
código do copiloto, código do comissário, status (ativo/inativo), tarifa.*/
class Voo{
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
    Voo() : id(contadorId++), status(false) {}

    Voo(const string& d, const string& h, const string& o, const string& dt, 
    int aviao, int piloto, int copiloto, int comissario, bool s, double preco) 
    : id(contadorId++), data(d), hora(h), origem(o), destino(dt),
    idAviao(aviao), idPiloto(piloto), idCopiloto(copiloto),
    idComissario(comissario), status(s), tarifa(preco) {}

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    static int getContador() { return contadorId; }
    static void setContador(int newId) { contadorId = newId; }

    void visualizar() const {
        cout << "ID: " << id << endl;
        cout << "Data: " << data << "-" << "Hora:" << hora << endl;
        cout << "Origem: " << origem << "-" << "Destino: " << destino << endl;
        cout << "Avião nº: " << idAviao << endl;
        cout << "Nº: Piloto" << idPiloto << endl;
        cout << "Nº: Copiloto" << idCopiloto << endl;
        cout << "Nº: Comissario" << idComissario << endl;
        cout << "Ativo: " << (status ? "Ativo" : "Inativo") << endl;
        cout << "Tarifa: R$" << fixed << setprecision(2) << tarifa << endl;
        cout << "---------------------" << endl;
    }
    void cadastrar() {
        cout << "Informe a data(DD/MM/AAAA) do voo: " << endl;
        getline(cin, data);
        cout << "Informe a hora(HH/MM) do voo: " << endl;
        getline(cin, hora);
        cout << "Informe a origem: " << endl;
        getline(cin, origem);
        cout << "Informe o destino: " << endl;
        getline(cin, destino);
        cin.ignore();
        cout << "Insira o id do avião: " << endl;
        cin >> idAviao;
        cout << "Insira o id do piloto: " << endl;
        cin >> idPiloto;
        cout << "Insira o id do copiloto: " << endl;
        cin >> idCopiloto;
        cout << "Insira o id do comissário: " << endl;
        cin >> idComissario;
        cout << "Status do Voo (1 - Ativo, 0 - Inativo): " << endl;
        cin >> status;
        while (status != 0 && status != 1)
        {
            cout << "Entrada inválida. Informe 1 para Ativo ou 0 para Inativo: ";
            cin >> status;
        }
        cout << "Insira a tarifa do voo: " << endl;
        cin >> tarifa;
        while (tarifa <= 0)
        {
            cout << "Entrada inválida. Informe um valor acima de 0: ";
            cin >> tarifa;
        }
        
    }
    //metodos para salvar e ler nos arq binarios
    void salvar(ofstream& arq) const{
        arq.write(reinterpret_cast<const char*>(&id),sizeof(id));

        size_t dataSize = data.size();
        arq.write(reinterpret_cast<const char*>(&dataSize),sizeof(dataSize));
        arq.write(data.c_str(),dataSize);

        size_t horaSize = hora.size();
        arq.write(reinterpret_cast<const char*>(&horaSize),sizeof(horaSize));
        arq.write(hora.c_str(),horaSize);

        size_t origemSize = origem.size();
        arq.write(reinterpret_cast<const char*>(&origemSize),sizeof(origemSize));
        arq.write(origem.c_str(),origemSize);

        size_t destinoSize = destino.size();
        arq.write(reinterpret_cast<const char*>(&destinoSize),sizeof(destinoSize));
        arq.write(destino.c_str(),destinoSize);

        arq.write(reinterpret_cast<const char*>(&idAviao), sizeof(idAviao));
        arq.write(reinterpret_cast<const char*>(&idPiloto), sizeof(idPiloto));
        arq.write(reinterpret_cast<const char*>(&idCopiloto), sizeof(idCopiloto));
        arq.write(reinterpret_cast<const char*>(&idComissario), sizeof(idComissario));
        arq.write(reinterpret_cast<const char*>(&status), sizeof(status));
        arq.write(reinterpret_cast<const char*>(&tarifa), sizeof(tarifa));
    }
    void ler(ifstream& arq) {
        arq.read(reinterpret_cast<char*>(&id), sizeof(id));

        size_t dataSize;
        arq.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        data.resize(dataSize);
        arq.read(&data[0], dataSize);

        size_t horaSize;
        arq.read(reinterpret_cast<char*>(&horaSize), sizeof(horaSize));
        hora.resize(horaSize);
        arq.read(&hora[0], horaSize);

        size_t origemSize;
        arq.read(reinterpret_cast<char*>(&origemSize), sizeof(origemSize));
        origem.resize(origemSize);
        arq.read(&origem[0], origemSize);

        size_t destinoSize;
        arq.read(reinterpret_cast<char*>(&destinoSize), sizeof(destinoSize));
        destino.resize(destinoSize);
        arq.read(&destino[0], destinoSize);

        arq.read(reinterpret_cast<char*>(&idAviao), sizeof(idAviao));
        arq.read(reinterpret_cast<char*>(&idPiloto), sizeof(idPiloto));
        arq.read(reinterpret_cast<char*>(&idCopiloto), sizeof(idCopiloto));
        arq.read(reinterpret_cast<char*>(&idComissario), sizeof(idComissario));
        arq.read(reinterpret_cast<char*>(&status), sizeof(status));
        arq.read(reinterpret_cast<char*>(&tarifa), sizeof(tarifa));
    }
};
int Voo::contadorId = 1; // Contador de ID estático

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
    //metodos para salvar e ler nos arq binarios
    void salvar(ofstream& arq) const{
        arq.write(reinterpret_cast<const char*>(&numAssento),sizeof(numAssento));
        arq.write(reinterpret_cast<const char*>(&idVoo),sizeof(idVoo));
        arq.write(reinterpret_cast<const char*>(&ocupado),sizeof(ocupado));
    }
    void ler(ifstream& arq) {
        arq.read(reinterpret_cast<char*>(&numAssento), sizeof(numAssento));
        arq.read(reinterpret_cast<char*>(&idVoo), sizeof(idVoo));
        arq.read(reinterpret_cast<char*>(&ocupado), sizeof(ocupado));
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

    //metodos para salvar e ler nos arq binarios
    void salvar(ofstream& arq) const{
        arq.write(reinterpret_cast<const char*>(&idVoo),sizeof(idVoo));
        arq.write(reinterpret_cast<const char*>(&numAssento),sizeof(numAssento));
        arq.write(reinterpret_cast<const char*>(&idPassageiro),sizeof(idPassageiro));
    }
    void ler(ifstream& arq) {
        arq.read(reinterpret_cast<char*>(&idVoo), sizeof(idVoo));
        arq.read(reinterpret_cast<char*>(&numAssento), sizeof(numAssento));
        arq.read(reinterpret_cast<char*>(&idPassageiro), sizeof(idPassageiro));
    }
};



/*Templates são uma característica na linguagem que permite escrever um código genérico que pode ser reutilizado para diferentes tipos.*/
//templates para manipulação do contadorId estático nos arquivos binários
template <typename T>
void salvarContadorArqBinario(const string& nomeArquivo){
    ofstream arq(nomeArquivo, ios::binary | ios::out);
    if (!arq)
    {
        cerr << "Erro ao abrir arquivo para escrita." << endl;
        return;
    }

    //metodo para salvar primeiro o contador id
    int contadorId = T::getContador();
    arq.write(reinterpret_cast<const char*>(&contadorId), sizeof(contadorId));

    arq.close();
}
template <typename T>
void lerContadorArqBinario(const string& nomeArquivo){
    ifstream arq(nomeArquivo,ios::binary | ios::in);
    if(!arq){
        cerr << "Erro ao abrir o arquivo para leitura." << endl;
        return;
    }

    //metodo para ler o contadorId do arquivo
    int contadorId;
    arq.read(reinterpret_cast<char*>(&contadorId),sizeof(contadorId));
    T::setContador(contadorId);

    arq.close();
}

//template para manipulação dos arquivos binários
template <typename T>
void salvarArqBinario(const vector<T>& vetor, const string& nomeArquivo){
    ofstream arq(nomeArquivo, ios::binary | ios::out);
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
        item.salvar(arq);
    }
    arq.close();
}
//template para leitura dos arquivos binários
template <typename T>
vector<T> lerArqBinario(const string& nomeArquivo){
    ifstream arq(nomeArquivo,ios::binary | ios::in);
    vector<T> vetor;

    if(!arq){
        cerr << "Erro ao abrir o arquivo para leitura." << endl;
        return vetor;
    }
    size_t tamanho;
    arq.read(reinterpret_cast<char*>(&tamanho),sizeof(tamanho)); //tamanho do vetor

    for (size_t i = 0; i < tamanho; ++i)
    {
        T item;
        item.ler(arq);
        vetor.push_back(item);
    }
    arq.close();
    return vetor;
}

//template para verificar duplicidade de id
template <typename T>
void verificarId(const vector<T>& vetor, T& novoItem){
    bool idDuplicado;
    do
    {
        idDuplicado = false;
        for(const auto& v : vetor){
            if (v.getId() == novoItem.getId())
            {
                idDuplicado = true;
                int novoId = T::getContador();
                novoItem.setId(novoId);
                T::setContador(novoId + 1);
                break;
            }
            
        }
    } while (idDuplicado);
    
}

/*Funcionalidades a Implementar:*/
/*1. Cadastro de Passageiro:
    o Deve garantir que não haja dois passageiros com o mesmo código.
    o Opcionalmente, pode-se gerar o código automaticamente.*/

void cadastrarPassageiro(){
    //leitura do id para passageiros de acordo com o arquivo binario
    lerContadorArqBinario<Passageiro>("idPassageiro.dat");
    //cria um vetor de passageiros lendo do arquivo binario os passageiros salvos previamente
    vector<Passageiro> passageiros = lerArqBinario<Passageiro>("passageiro.bin");

    Passageiro novoPassageiro;
    novoPassageiro.cadastrar();
    
    verificarId(passageiros, novoPassageiro);

    passageiros.push_back(novoPassageiro);

    salvarArqBinario(passageiros,"passageiro.bin");
    salvarContadorArqBinario<Passageiro>("contador_passageiro.dat");

    cout << "Passageiros registrados: " << endl;
    vector<Passageiro> passageirosLoaded = lerArqBinario<Passageiro>("passageiro.bin");
    for(const auto& p : passageirosLoaded){
        p.visualizar();
    }
    cout << "---------------------" << endl;
}


/*2. Cadastro de Tripulação:
    o Cada membro da tripulação deve ter um cargo específico.
    o Deve garantir que não haja dois membros da tripulação com o mesmo código.
    o Opcionalmente, pode-se gerar o código automaticamente.*/
void cadastrarTripulacao(){
    lerContadorArqBinario<Tripulacao>("idTripulacao.dat");
    vector<Tripulacao> tripulantes = lerArqBinario<Tripulacao>("tripulacao.bin");

    Tripulacao novoTripulante;
    novoTripulante.cadastrar();

    verificarId(tripulantes,novoTripulante);

    tripulantes.push_back(novoTripulante);

    salvarArqBinario(tripulantes, "tripulacao.bin");
    salvarContadorArqBinario<Tripulacao>("idTripulacao.dat");

    cout << "Tripulantes registrados: " << endl;
    vector<Tripulacao> tripulantesLoaded = lerArqBinario<Tripulacao>("tripulacao.bin");
    for (const auto& t : tripulantesLoaded)
    {
        t.visualizar();
    }
    cout << "---------------------" << endl;
}


/*3. Cadastro de Voo:
    o Deve ser possível cadastrar informações sobre data, hora, origem, destino, tarifa,
    tripulação e o avião.
    o Deve verificar a presença de ao menos um piloto e um copiloto para que o voo
    seja marcado como ativo.*/

void cadastrarVoo(){
    vector<Voo> voos;
    Voo novoVoo;
    novoVoo.cadastrar();

    verificarId(voos,novoVoo);

    voos.push_back(novoVoo);
    salvarArqBinario(voos,"voo.bin");

    cout << "Voos registrados" << endl;
    vector<Voo> voosLoaded = lerArqBinario<Voo>("voo.bin");
    for(const auto& v : voosLoaded){
        v.visualizar();
    }
    cout << "---------------------" << endl;
}


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
    vector<Assento> assentosLoaded = lerArqBinario<Assento>("assento.bin");
    for(const auto& a : assentosLoaded){
        cout << "Nº de assentos registrados: " << assentosLoaded.size();
    }
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
            cadastrarPassageiro();
            break;
        case 2:
            cadastrarTripulacao();
            break;
        case 3:
            cadastrarVoo();
            break;
        case 4:
            cadastrarAssentos();
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

int main(){
    menu();

    return 0;
}