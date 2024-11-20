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
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Compilando para Windows")
    # No Windows, o GoogleTest será configurado pelo workflow
    include_directories("googletest-release-1.15.2/googletest/include" "googletest-release-1.15.2/googlemock/include")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Compilando para macOS")
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compilando para Linux")
endif()

# Adiciona o arquivo de código-fonte
add_executable(TP-Voo-Seguro main.cpp)

# Adiciona o GoogleTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Adiciona o subdiretório de testes
add_subdirectory(test)
