# Defina a versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(TP-Voo-Seguro)

# Defina a versão do C++ que você quer usar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adiciona o arquivo de código-fonte
add_executable(TP-Voo-Seguro main.cpp)

# Configuração para Windows (caso queira usar algum recurso do Windows, como Windows.h)
if(WIN32)
    # Específico para o Windows, podemos adicionar flags ou configurações especiais se necessário
    message(STATUS "Compilando para Windows")
    # Aqui você pode adicionar configurações específicas do Windows, como suporte a fontes e acentuação
    # Para o Windows, não há nada a mais a configurar especificamente para o seu código
elseif(APPLE)
    message(STATUS "Compilando para macOS")
elseif(UNIX)
    message(STATUS "Compilando para Linux ou outro sistema UNIX")
endif()

# Caso queira adicionar flags de compilação para depuração ou release
# Por exemplo, pode-se adicionar otimizações em modo Release
set(CMAKE_BUILD_TYPE Release)

# Caso tenha dependências externas, você pode encontrar bibliotecas da seguinte forma
# Exemplo: find_package(Boost REQUIRED)
# target_link_libraries(ProjetoSimples Boost::Boost)
