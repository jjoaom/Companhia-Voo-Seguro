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

# Configuração de runtime específica para MSVC
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Adicione o diretório de código-fonte
add_executable(TP-Voo-Seguro src/main.cpp)

# Configuração específica para GoogleTest
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compilando para macOS/Linux")
    find_package(GTest REQUIRED)
    target_include_directories(TP-Voo-Seguro PUBLIC ${GTEST_INCLUDE_DIRS})
    target_link_libraries(TP-Voo-Seguro GTest::gtest GTest::gtest_main pthread)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Compilando para Windows")
    find_package(GTest REQUIRED)
    target_link_libraries(TP-Voo-Seguro ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
else()
    message(FATAL_ERROR "Sistema operacional não suportado!")
endif()

# Ativar testes
enable_testing()

# Adicionar subdiretório de testes (se existir)
if(EXISTS "${CMAKE_SOURCE_DIR}/test")
    add_subdirectory(test)
endif()
