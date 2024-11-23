#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include "templates.hpp" // Incluindo o arquivo de templates para usar os templates definidos




void checkOs()
{
#ifdef _WIN32
    try
    {
        SetConsoleOutputCP(CP_UTF8); // Configura o console para UTF-8
        SetConsoleCP(CP_UTF8);
        system("cls");
        cout << "Localidade configurada para Windows com sucesso.\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Falha ao definir a localidade para Windows: " << e.what() << '\n';
    }
#elif __linux__
    try
    {
        locale::global(locale("pt_BR.UTF-8"));
        system("clear");
        cout << "Localidade configurada para Linux com sucesso.\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Falha ao definir a localidade para Linux: " << e.what() << '\n';
    }
#else
    cout << "Sistema operacional não identificado.\n";
#endif
}

#endif // FUNCOES_HPP
