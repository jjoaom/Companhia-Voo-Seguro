#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <limits>
#include <algorithm> 
#include <cctype> 

using namespace std;


// Template para manipulação dos arquivos binários
template <typename T>
void salvarArqBinario(const vector<T> &vetor, const string &nomeArquivo)
{
    ofstream arq(nomeArquivo, ios::binary | ios::out);
    if (!arq)
    {
        cerr << "Erro ao abrir arquivo para escrita." << endl;
        return;
    }
    size_t tamanho = vetor.size();
    arq.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho)); // tamanho do vetor
    for (const auto &item : vetor)
    {
        item.salvar(arq);
    }
    arq.close();
}

// Template para leitura dos arquivos binários
template <typename T>
vector<T> lerArqBinario(const string &nomeArquivo)
{
    ifstream arq(nomeArquivo, ios::binary | ios::in);
    vector<T> vetor;
    if (!arq)
    {
        cerr << "Erro ao abrir o arquivo para leitura." << endl;
        return vetor;
    }
    size_t tamanho;
    arq.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho)); // tamanho do vetor
    for (size_t i = 0; i < tamanho; ++i)
    {
        T item;
        item.ler(arq);
        vetor.push_back(item);
    }
    arq.close();
    return vetor;
}

// Template para atualizar o id do contador
template <typename T>
void atualizarContadorId(vector<T> &vetor)
{
    int maiorId = 0;
    for (const auto &item : vetor)
    {
        if (item.getId() > maiorId)
        {
            maiorId = item.getId();
        }
    }
    T::setContador(maiorId + 1);
}

// Template para verificar duplicidade de id
template <typename T>
void verificarId(const vector<T> &vetor, T &novoItem)
{
    bool idDuplicado;
    do
    {
        idDuplicado = false;
        for (const auto &v : vetor)
        {
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

// Template para inicializar os arquivos das classes
template <typename T>
void inicializarArq(const string &nomeArquivo)
{
    ifstream arq(nomeArquivo, ios::binary);
    if (!arq)
    {
        vector<T> vetor;
        ofstream newVetor(nomeArquivo, ios::binary | ios::out);
        if (newVetor)
        {
            size_t tamanho = vetor.size();
            newVetor.write(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
            newVetor.close();
        }
        else
        {
            cerr << "Erro ao criar o arquivo " << nomeArquivo << endl;
        }
    }
    arq.close();
}



// Template para funções de cadastro
template <typename T>
void cadastrarTemplate(const string &arqBinario)
{
    vector<T> items = lerArqBinario<T>(arqBinario);
    T novoItem;
    novoItem.cadastrar();
    verificarId(items, novoItem);
    items.push_back(novoItem);
    salvarArqBinario(items, arqBinario);
    cout << "._____________________________" << endl;
    cout << "| Items registrados: " << endl;
    vector<T> itemsLoaded = lerArqBinario<T>(arqBinario);
    for (const auto &item : itemsLoaded)
    {
        item.visualizar();
    }
}

// Teste com novo tipo de função que pode receber trecho de código como parâmetro para MODIFICAÇÃO - sem const
template <typename T, typename Func>
void  percorrerVetor(vector<T> &vetor, Func func)
{
    for (auto &item : vetor)
    {
        func(item);
    }
}


//converter nome para minusculo para realizar busca

string toLowerCase(const string& str) {
    string minusculo = str;
    std::transform(minusculo.begin(), minusculo.end(), minusculo.begin(), [](unsigned char c) { 
        return tolower(c); 
    });
    return minusculo;
}
#endif // TEMPLATES_HPP
