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

# Verifica se o GoogleTest foi encontrado corretamente
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Compilando para Windows")
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2")
        message(FATAL_ERROR "GoogleTest not found. Please ensure it is installed or manually download it.")
    endif()
    set(GTEST_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2/googletest/include")
    set(GTEST_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.15.2/googletest/libgtest.a")
    include_directories(${GTEST_INCLUDE_DIRS})
endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Se estiver no macOS
    message(STATUS "Compilando para macOS")
    find_package(GTest REQUIRED)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Se estiver no Ubuntu
    message(STATUS "Compilando para Ubuntu")
    find_package(GTest REQUIRED)
else()
    message(WARNING "Sistema operacional não suportado para a instalação do GoogleTest.")
endif()

# Verificação de se o GoogleTest foi encontrado
if(NOT GTest_FOUND)
    message(FATAL_ERROR "GoogleTest não encontrado. Verifique se o GTest está instalado corretamente.")
else()
    message(STATUS "GoogleTest encontrado em: ${GTEST_INCLUDE_DIRS}")
endif()

# Adiciona o arquivo de código-fonte
add_executable(TP-Voo-Seguro main.cpp)

# Adiciona o GoogleTest para os testes
enable_testing()

# Inclui os diretórios de cabeçalhos do GoogleTest
include_directories(${GTEST_INCLUDE_DIRS})

# Adiciona o subdiretório de testes
add_subdirectory(test)
