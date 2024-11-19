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
    # Evita conflitos com macros max/min no Windows
    add_definitions(-DNOMINMAX)
    
    # Aqui você pode adicionar configurações específicas para Windows, como linkar bibliotecas específicas, se necessário
    # Por exemplo: target_link_libraries(TP-Voo-Seguro ws2_32) para usar Winsock

elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Compilando para macOS")
    # Configurações específicas para o macOS, se necessário

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compilando para Linux")
    # Configurações específicas para Linux, se necessário
endif()

# Adiciona o arquivo de código-fonte
add_executable(TP-Voo-Seguro main.cpp)

# Adiciona o GoogleTest usando FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Adiciona o GoogleTest
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Adiciona o subdiretório de testes
add_subdirectory(test)