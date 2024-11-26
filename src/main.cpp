#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif


#include <iostream>   //bib padrão
#include <iomanip>    //bib imprimir double formatado
#include <string>     //bib string
#include <fstream>    //bib file
#include <vector>     //bib vector
#include <limits>     //bib limits para limpeza de buffer
#include <functional> //bib para criar funções que recebem trecho de código
#include <stdexcept>  //bib para tratamento de exceção
#include <cstdlib>    //bib para sistema
#include "templates.hpp" // Arquivo de templates
#include "classes.hpp" // Arquivo de classes

using namespace std;

// Definindo constantes globais para os vetores
vector<Passageiro> passageiros;
vector<Tripulacao> tripulantes;
vector<Voo> voos;
vector<Assento> assentos;
vector<Reserva> reservas;

void recarregarVetoresGlobais()
{
    try
    {
        passageiros = lerArqBinario<Passageiro>("data/passageiro.bin");
        tripulantes = lerArqBinario<Tripulacao>("data/tripulacao.bin");
        voos = lerArqBinario<Voo>("data/voo.bin");
        assentos = lerArqBinario<Assento>("data/assento.bin");
        reservas = lerArqBinario<Reserva>("data/reserva.bin");
    }
    catch (const runtime_error &e)
    {
        cerr << "Erro ao recarregar vetores globais: " << e.what() << endl;
    }
}


//1. Cadastro de Passageiro:
void cadastrarPassageiro()
{
    try{
    cadastrarTemplate<Passageiro>("data/passageiro.bin");
    }catch (const runtime_error &e){
        cerr << "Erro ao cadastrar passageiro: " << e.what() << endl;
    }
}

//2. Cadastro de Tripulação:
void cadastrarTripulacao()
{
    try{
    cadastrarTemplate<Tripulacao>("data/tripulacao.bin");
    }catch (const runtime_error &e){
        cerr << "Erro ao cadastrar tripulação: " << e.what() << endl;
    }
    
}

//3. Cadastro de Voo:
// função para verificar a presença de ao menos um piloto e um copiloto para marcar o voo como ativo
void verificaVooAtivo(Voo &novoVoo)
{
    vector<Tripulacao> tripulacaoLoaded = lerArqBinario<Tripulacao>("data/tripulacao.bin");

    bool pilotoEncontrado = false;
    bool copilotoEncontrado = false;
    // laço range based que percorre o vetor de tripulação em busca do tripulante com o id digitado e cargo piloto
    for (const auto &t : tripulacaoLoaded)
    {
        if (t.getId() == novoVoo.getIdPiloto() && t.getCargo() == Tripulacao::Cargo::Piloto)
        {
            pilotoEncontrado = true;
        }
        if (t.getId() == novoVoo.getIdCopiloto() && t.getCargo() == Tripulacao::Cargo::Copiloto)
        {
            copilotoEncontrado = true;
        }
    }
    if (pilotoEncontrado && copilotoEncontrado)
    {
        novoVoo.setStatus(true); // Marcar o voo como ativo
    }
    else
    {
        novoVoo.setStatus(false); // Marcar o voo como inativo
        cout << "Este voo foi marcado como inativo devido à ausência de piloto e copiloto válidos." << endl;
        cout << "Deseja cadastrar novos pilotos e copilotos? (1 - Sim, 2 - Não): ";
        int opcao;
        cin >> opcao;
        if (opcao == 1)
        {
            int novoIdPiloto, novoIdCopiloto;
            cout << "Digite o ID do novo piloto: ";
            cin >> novoIdPiloto;
            cout << "Digite o ID do novo copiloto: ";
            cin >> novoIdCopiloto;
            novoVoo.setIdPiloto(novoIdPiloto);
            novoVoo.setIdCopiloto(novoIdCopiloto);
            verificaVooAtivo(novoVoo); // Verificar novamente com os novos IDs
        }
    }
}

// Template para verificar se o ID do voo corresponde
template <typename T>
bool verificarIdVoo(T &item)
{
    bool vooEncontrado = false;
    for (const auto &v : voos)
    {
        if (item.getIdVoo() == v.getId())
        {
            vooEncontrado = true;
            break;
        }
    }
    if (!vooEncontrado)
    {
        cerr << "Este id não corresponde a nenhum voo cadastrado." << endl;
    }
    return vooEncontrado;
}

void cadastrarVoo()
{
    try
    {
        recarregarVetoresGlobais();
        vector<Voo> voosLoaded = lerArqBinario<Voo>("data/voo.bin");
        Voo novoVoo;

        // Incrementar o ID e atribuir ao novo voo
        int novoId = Voo::getContador();
        novoVoo.setId(novoId);
        Voo::setContador(novoId + 1);

        novoVoo.cadastrar();

        verificarId(voosLoaded, novoVoo);

        verificaVooAtivo(novoVoo);

        voosLoaded.push_back(novoVoo);

        salvarArqBinario(voosLoaded, "data/voo.bin");
        recarregarVetoresGlobais();

        cout << "| Voos registrados" << endl;
        for (const auto &v : voosLoaded)
        {
            v.visualizar();
        }
    }
    catch (const runtime_error &e)
    {
        cerr << "Erro ao cadastrar voo: " << e.what() << endl;
    }
}

//4. Cadastro de Assento:
void cadastrarAssentos()
{
    try
    {
        recarregarVetoresGlobais();
        int idVoo, numAssentos;
        cout << "Cadastro de Assento" << endl;
        cout << "Insira o ID do Voo: " << endl;
        cin >> idVoo;
        cout << "Insira a quantidade de assentos disponíveis no voo: " << endl;
        cin >> numAssentos;
        while (numAssentos <= 0)
        {
            cout << "Entrada inválida. Informe um número acima de 0: " << endl;
            cin >> numAssentos;
        }
        vector<Assento> assentos = lerArqBinario<Assento>("data/assento.bin");
        for (int i = 1; i <= numAssentos; i++)
        {
            Assento novoAssento;
            novoAssento.setIdVoo(idVoo);
            if (!verificarIdVoo(novoAssento))
            {
                cerr << "Erro ao cadastrar assento: Voo não encontrado." << endl;
                return;
            }
            novoAssento.setAssento(i);
            novoAssento.liberado();
            assentos.push_back(novoAssento);
        }
        salvarArqBinario(assentos, "data/assento.bin");
        recarregarVetoresGlobais();
        cout << "Todos os " << numAssentos << " assentos do Voo nº " << idVoo << " foram cadastrados com sucesso." << endl;
    }
    catch (const runtime_error &e)
    {
        cerr << "Erro ao cadastrar assentos: " << e.what() << endl;
    }
}

//5. Reserva:
bool verificarItemsReserva(Reserva &item)
{
    // Verifica se o voo existe
    bool vooEncontrado = false;
    for (const auto &v : voos)
    {
        if (item.getIdVoo() == v.getId())
        {
            cout << "Voo correspondente encontrado. Prosseguindo..." << endl;
            vooEncontrado = true;
            break;
        }
    }
    if (!vooEncontrado)
    {
        cerr << "Este id não corresponde a nenhum voo cadastrado." << endl;
        return false;
    }

    // Verifica se o passageiro já tem uma reserva no voo
    for (const auto &r : reservas)
    {
        if (r.getIdPassageiro() == item.getIdPassageiro() && r.getIdVoo() == item.getIdVoo())
        {
            cerr << "Esse passageiro já tem uma reserva cadastrada no Voo. Dê baixa na reserva e tente novamente." << endl;
            return false;
        }
    }
    // Verifica se o passageiro existe
    bool passageiroEncontrado = false;
    for (const auto &p : passageiros)
    {
        if (item.getIdPassageiro() == p.getId())
        {
            cout << "Passageiro correspondente encontrado. Prosseguindo..." << endl;
            passageiroEncontrado = true;
            break;
        }
    }
    if (!passageiroEncontrado)
    {
        cerr << "Este id não corresponde a nenhum passageiro cadastrado." << endl;
        return false;
    }

    // Verifica se o assento está disponível
    bool assentoEncontrado = false;
    vector<Assento> assentosLoaded = lerArqBinario<Assento>("data/assento.bin");
    for (auto &a : assentosLoaded)
    {
        if (item.getNumAssento() == a.getAssento() && !a.isOcupado())
        {
            cout << "Assento correspondente encontrado. Prosseguindo..." << endl;
            assentoEncontrado = true;
            a.ocupar();
            break;
        }
    }
    if (!assentoEncontrado)
    {
        cerr << "Este assento não se encontra disponível." << endl;
        return false;
    }
    salvarArqBinario(assentosLoaded, "data/assento.bin");

    return true;
}

void reserva()
{
    try
    {
        recarregarVetoresGlobais();
        int qtdReservas;
        cout << "Cadastrar reserva." << endl;
        cout << "Insira a quantidade de reservas que deseja registrar:" << endl;
        cin >> qtdReservas;
        while (qtdReservas <= 0)
        {
            cout << "Insira um valor maior que zero." << endl;
            cin >> qtdReservas;
        }
        
        for (int i = 0; i < qtdReservas; i++)
        {
            cout << "Reserva nº" << i+1 << ":" << endl;
            Reserva novaReserva;
            novaReserva.cadastrar();

            // Verificar se a reserva foi validada corretamente
            if (!verificarItemsReserva(novaReserva))
            {
                cerr << "Erro ao verificar os itens da reserva. Verifique os dados e tente novamente." << endl;
                return;
            }

            if (novaReserva.getIdVoo() == 0 || novaReserva.getNumAssento() == 0 || novaReserva.getIdPassageiro() == 0)
            {
                cerr << "Erro ao cadastrar a reserva. Verifique os dados e tente novamente." << endl;
                return;
            }

            vector<Reserva> reservasLoaded = lerArqBinario<Reserva>("data/reserva.bin");
            reservasLoaded.push_back(novaReserva);

            salvarArqBinario(reservasLoaded, "data/reserva.bin");
            recarregarVetoresGlobais();
            cout << "|Reserva registrada" << endl;
            novaReserva.visualizar();
        }
    }
    catch (const runtime_error &e)
    {
        cerr << "Erro ao cadastrar reserva: " << e.what() << endl;
    }
}

//6. Baixa em Reserva:
bool baixaEfetuada(Reserva &novaReserva)
{
    // verifica se o voo existe
    bool vooEncontrado = false;
    for (const auto &v : voos)
    {
        if (novaReserva.getIdVoo() == v.getId())
        {
            vooEncontrado = true;
            break;
        }
    }
    if (!vooEncontrado)
    {
        cerr << "O id: "<< novaReserva.getIdVoo() << " não corresponde a nenhum voo cadastrado." << endl;
        return false;
    }

    // verifica se o assento está ocupado
    vector<Assento> assentosLoaded = lerArqBinario<Assento>("data/assento.bin");
    bool assentoEncontrado = false;
    for (auto &a : assentosLoaded)
    {
        if (novaReserva.getNumAssento() == a.getAssento() && a.isOcupado())
        {
            a.liberado();
            assentoEncontrado = true;
            break;
        }
    }
    if (!assentoEncontrado)
    {
        cerr << "Este assento não está ocupado." << endl;
        return false;
    }

    // verifica se o passageiro existe
    bool passageiroEncontrado = false;
    for (const auto &p : passageiros)
    {
        if (novaReserva.getIdPassageiro() == p.getId())
        {
            passageiroEncontrado = true;
            break;
        }
    }
    if (!passageiroEncontrado)
    {
        cerr << "Este id não corresponde a nenhum passageiro cadastrado." << endl;
        return false;
    }

    salvarArqBinario(assentosLoaded, "data/assento.bin");

    for (const auto &v : voos)
    {
        if (novaReserva.getIdVoo() == v.getId())
        {
            cout << "A tarifa total é de R$" << fixed << setprecision(2) << v.getTarifa() << endl;
        }
    }

    return true;
}

void baixarReserva()
{
    try
    {
        recarregarVetoresGlobais();
        cout << "Baixar Reserva." << endl;
        cout << "Insira a reserva que deseja dar baixa." << endl;
        Reserva novaReserva;
        novaReserva.cadastrar();

        if (!baixaEfetuada(novaReserva))
        {
            cerr << "Erro ao dar baixa na reserva. Verifique os dados e tente novamente." << endl;
            return;
        }

        vector<Reserva> reservasLoaded = lerArqBinario<Reserva>("data/reserva.bin");

        auto reservaRemovida = remove_if(reservasLoaded.begin(), reservasLoaded.end(), [&novaReserva](const Reserva &r) {
            return r.getIdPassageiro() == novaReserva.getIdPassageiro() && r.getIdVoo() == novaReserva.getIdVoo() && r.getNumAssento() == novaReserva.getNumAssento();
        });

        if (reservaRemovida == reservasLoaded.end())
        {
            cerr << "Reserva não encontrada." << endl;
            return;
        }

        reservasLoaded.erase(reservaRemovida, reservasLoaded.end());

        salvarArqBinario(reservasLoaded, "data/reserva.bin");

        vector<Passageiro> passageirosLoaded = lerArqBinario<Passageiro>("data/passageiro.bin");
        bool passageiroEncontrado = false;
        for (auto &p : passageirosLoaded)
        {
            if (novaReserva.getIdPassageiro() == p.getId())
            {
                p.increaseFidelidade();
                passageiroEncontrado = true;
                break;
            }
        }
        if (!passageiroEncontrado)
        {
            cerr << "Este id não corresponde a nenhum passageiro cadastrado." << endl;
            return;
        }

        salvarArqBinario(passageirosLoaded, "data/passageiro.bin");
        recarregarVetoresGlobais();
        cout << "Reserva baixada com sucesso." << endl;
    }
    catch (const runtime_error &e)
    {
        cerr << "Erro ao baixar reserva: " << e.what() << endl;
    }
}
//7. Pesquisa:
int menuPesquisa(int &buscaId, string &buscaNome)
{
    int pesquisa;
    do
    {
        cout << "Pesquisa" << endl;
        cout << "1-Pesquisar por ID" << endl;
        cout << "2-Pesquisar por nome" << endl;
        cout << "Escolha uma opção:" << endl;
        cin >> pesquisa;
    } while (pesquisa != 1 && pesquisa != 2);

    if (pesquisa == 1)
    {
        cout << "Insira o ID a ser buscado:" << endl;
        cin >> buscaId;
    }
    else if (pesquisa == 2)
    {
        cout << "Insira o nome a ser buscado:" << endl;
        cin.ignore();
        getline(cin, buscaNome);
    }
    return pesquisa;
}
Passageiro pesquisaPassageiro()
{
    int buscaId;
    string buscaNome;
    int tipoPesquisa = menuPesquisa(buscaId, buscaNome);

    //converte o nome digitado
    string buscaNomeMin = toLowerCase(buscaNome);
    for (const auto &p : passageiros)
    {
        string nomeMin = toLowerCase(p.getNome());
        if (tipoPesquisa == 1 && p.getId() == buscaId)
        {
            return p;
        }
        else if (tipoPesquisa == 2 && nomeMin.find(buscaNomeMin)!= string::npos)
        {
            return p;
        }
    }

    throw runtime_error("Passageiro não encontrado.");
}

Tripulacao pesquisarTripulacao()
{
    int buscaId;
    string buscaNome;
    int tipoPesquisa = menuPesquisa(buscaId, buscaNome);
    //converte o nome digitado
    string buscaNomeMin = toLowerCase(buscaNome);
    for (const auto &t : tripulantes)
    {
        string nomeMin = toLowerCase(t.getNome());
        if (tipoPesquisa == 1 && t.getId() == buscaId)
        {
            return t;
        }
        else if (tipoPesquisa == 2 && nomeMin.find(buscaNomeMin)!= string::npos)
        {
            return t;
        }
    }
    throw runtime_error("Tripulante não encontrado.");
}

void pesquisa()
{
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
            try
            {
                Passageiro passageiroEncontrado = pesquisaPassageiro();
                passageiroEncontrado.visualizar();
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
            }
            break;
        case 2:
            try
            {
                Tripulacao tripulacaoEncontrado = pesquisarTripulacao();
                tripulacaoEncontrado.visualizar();
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
            }
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

//8. Programa de Fidelidade:
void verificarPontosFidelidade()
{
    try
    {
        recarregarVetoresGlobais();
        Passageiro passageiroEncontrado = pesquisaPassageiro();
        if (passageiroEncontrado.ehFiel())
        {
            cout << "O passageiro " << passageiroEncontrado.getNome() << " possui " << passageiroEncontrado.getPontosFidelidade() << " pontos." << endl;
        }else if(!passageiroEncontrado.ehFiel()){
            cout << "O passageiro " << passageiroEncontrado.getNome() << " não está cadastrado no programa Fidelidade." << endl;
        }
    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl;
    }
}

void pesquisaAssento()
{
    int opcao, idBuscado;
    vector<Assento> assentos = lerArqBinario<Assento>("data/assento.bin");
    do
    {
        cout << "Pesquisa de assentos" << endl;
        cout << "1-Assentos disponíveis" << endl;
        cout << "2-Assentos ocupados" << endl;
        cout << "3-Todos os assentos registrados" << endl;
        cout << "0-Sair" << endl;
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            for (auto &a : assentos){
                if (!a.isOcupado()){
                    a.visualizar();
                }
            }

            break;
        case 2:
            for (auto &a : assentos){
                if (a.isOcupado()){
                    a.visualizar();
                }
            }
            break;
        case 3:
            for (auto &a : assentos){
                a.visualizar();
            }

            break;
        case 0:
            cout << "Saindo..." << endl;
            break;

        default:
            break;
        }
    } while (opcao != 0);
}
//Função extra para abrir e verificar todos os arquivos binários
void depurarArquivos()
{
    try
    {
        vector<Passageiro>passageiros = lerArqBinario<Passageiro>("data/passageiro.bin");
        vector<Tripulacao>tripulantes = lerArqBinario<Tripulacao>("data/tripulacao.bin");
        vector<Voo>voos = lerArqBinario<Voo>("data/voo.bin");
        vector<Reserva>reservas = lerArqBinario<Reserva>("data/reserva.bin");
        vector<Assento>assentos = lerArqBinario<Assento>("data/assento.bin");
        int opcao;
        do
        {
            cout << endl;
            cout << "Depuração de arquivos" << endl;
            cout << "Escolha uma opção:" << endl;
            cout << "1-Arquivo Passageiro" << endl;
            cout << "2-Arquivo Tripulacao" << endl;
            cout << "3-Arquivo Voo" << endl;
            cout << "4-Arquivo Assento" << endl;
            cout << "5-Arquivo Reserva" << endl;
            cout << "0-Sair" << endl;
            cin >> opcao;

            switch (opcao)
            {
            case 1:
                if (passageiros.empty())
                {
                    cout << "Nenhum passageiro cadastrado." << endl;
                }
                else
                {
                    for (auto &p : passageiros)
                    {
                        p.visualizar();
                    }
                }
                break;
            case 2:
                if (tripulantes.empty())
                {
                    cout << "Nenhum tripulante cadastrado." << endl;
                }
                else
                {
                    for (auto &t : tripulantes)
                    {
                        t.visualizar();
                    }
                }
                break;
            case 3:
                if (voos.empty())
                {
                    cout << "Nenhum voo cadastrado." << endl;
                }
                else
                {
                    for (auto &v : voos)
                    {
                        v.visualizar();
                    }
                }
                break;
            case 4:
                pesquisaAssento();
                if (assentos.empty())
                {
                    cout << "Nenhum assento cadastrado." << endl;
                }
                else
                {
                    for (auto &a : assentos)
                    {
                        a.visualizar();
                    }
                }
                break;
            case 5:
                if (reservas.empty())
                {
                    cout << "Nenhuma reserva cadastrada." << endl;
                }
                else
                {
                    for (auto &r : reservas)
                    {
                        r.visualizar();
                    }
                }
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Valor incorreto. Tente novamente." << endl;
                break;
            }
        } while (opcao != 0);
    }
    catch (const runtime_error &e)
    {
        cerr << "Erro ao depurar arquivos: " << e.what() << endl;
    }
}
//Menu principal
void menu()
{
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
        cout << "9-Verificar os arquivos binários" << endl;
        cout << "0-Sair" << endl;
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
            reserva();
            break;
        case 6:
            baixarReserva();
            break;
        case 7:
            pesquisa();
            break;
        case 8:
            verificarPontosFidelidade();
            break;
        case 9:
            depurarArquivos();
            break;
        case 0:
            cout << "Saindo..." << endl;
        default:
            break;
        }
    } while (opcao != 0);
}

//Função de verificar dos arquivos
void verificarArquivos()
{
    // Iniciando arquivos dos vetores
    inicializarArq<Passageiro>("data/passageiro.bin");
    inicializarArq<Tripulacao>("data/tripulacao.bin");
    inicializarArq<Assento>("data/assento.bin");
    inicializarArq<Voo>("data/voo.bin");
    inicializarArq<Reserva>("data/reserva.bin");

    // Lendo os dados para atualizar o contador
    vector<Passageiro> passageirosLoaded = lerArqBinario<Passageiro>("data/passageiro.bin");
    atualizarContadorId(passageirosLoaded);

    vector<Tripulacao> tripulantesLoaded = lerArqBinario<Tripulacao>("data/tripulacao.bin");
    atualizarContadorId(tripulantesLoaded);

    vector<Voo> voosLoaded = lerArqBinario<Voo>("data/voo.bin");
    atualizarContadorId(voosLoaded);
}

// Inicializando contadores id
int Passageiro::contadorId = 1;
int Tripulacao::contadorId = 1;
int Voo::contadorId = 1;

#ifndef RUNNING_TESTS
int main()
{
    checkOs();
    verificarArquivos();
    menu();

    return 0;
}
#endif