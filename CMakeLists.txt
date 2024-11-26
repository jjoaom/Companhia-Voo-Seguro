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

# Add this line to set the runtime library
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Inicializa e atualiza o submódulo do GoogleTest
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/googletest")
  message(STATUS "GoogleTest submodule not initialized. Initializing...")
  execute_process(COMMAND git submodule update --init --recursive)
endif()

# Adiciona o GoogleTest como subdiretório
add_subdirectory(googletest)

# Adiciona o arquivo de código-fonte principal
add_executable(TP-Voo-Seguro main.cpp)

# Linka o GoogleTest
target_link_libraries(TP-Voo-Seguro gtest gtest_main)

# Configura o link do GoogleTest para todos os sistemas
enable_testing()

# Adiciona o subdiretório de testes
add_subdirectory(test)
