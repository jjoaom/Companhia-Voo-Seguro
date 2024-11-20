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
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compilando para macOS/Linux")
    # Verifica se o GoogleTest foi encontrado corretamente
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Usando GoogleTest manualmente no Windows")
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )
    FetchContent_MakeAvailable(googletest)
    set(GTEST_LIBRARIES gtest)
    set(GTEST_MAIN_LIBRARIES gtest_main)
endif()

# Adiciona o arquivo de código-fonte principal
add_executable(TP-Voo-Seguro main.cpp)

# Linka o GoogleTest
enable_testing()

# Configura o link do GoogleTest
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(TP-Voo-Seguro ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
else()
    target_link_libraries(TP-Voo-Seguro GTest::gtest GTest::gtest_main)
endif()

# Adiciona o subdiretório de testes
add_subdirectory(test)