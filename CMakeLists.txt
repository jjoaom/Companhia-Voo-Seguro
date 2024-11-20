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

# Defina configurações específicas com base no sistema operacional
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Compilando para macOS")
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compilando para Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Compilando para Windows")

    # Se o diretório googletest não existir, vamos fazer o download
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2")
        message(STATUS "GoogleTest não encontrado, baixando...")
        
        # Baixa o GoogleTest do GitHub
        file(DOWNLOAD "https://github.com/google/googletest/archive/refs/tags/release-1.15.2.tar.gz"
             "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2.tar.gz")
        
        # Descompacta o arquivo tar.gz
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2.tar.gz"
                        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

        # Remove o arquivo .tar.gz após descompactar
        file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2.tar.gz")
    endif()

    # Defina os diretórios de inclusão e a biblioteca do GoogleTest
    set(GTEST_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2/googletest/include")
    set(GTEST_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2/googletest/libgtest.a")

    # Inclui o diretório de cabeçalhos do GoogleTest
    include_directories(${GTEST_INCLUDE_DIRS})

endif()

# Adiciona o arquivo de código-fonte
add_executable(TP-Voo-Seguro main.cpp)

# Adiciona o GoogleTest
enable_testing()

# Não é necessário o find_package(GTest REQUIRED) no Windows
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

# Adiciona o subdiretório de testes
add_subdirectory(test)
