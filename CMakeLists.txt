# Defina a versão mínima do CMake
cmake_minimum_required(VERSION 3.14)

# Nome do projeto
project(TP-Voo-Seguro)

# Defina a versão do C++ que você quer usar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Mensagens de status para saber onde estamos
message(STATUS "Compilando para o sistema: ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMake versão: ${CMAKE_VERSION}")

# Verifique se o GoogleTest foi encontrado corretamente
find_package(GTest REQUIRED)

# Mensagem de sucesso se o GoogleTest for encontrado
message(STATUS "GoogleTest encontrado em: ${GTEST_INCLUDE_DIRS}")

# Adiciona o arquivo de código-fonte
add_executable(TP-Voo-Seguro main.cpp)

# Adiciona o GoogleTest (necessário para rodar os testes)
enable_testing()

# Inclui os diretórios de cabeçalhos do GoogleTest
include_directories(${GTEST_INCLUDE_DIRS})

# Adiciona o subdiretório de testes
add_subdirectory(test)

