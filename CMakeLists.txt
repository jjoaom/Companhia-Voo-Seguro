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

# Adiciona o diretório de código-fonte
add_executable(TP-Voo-Seguro src/main.cpp)

# Configuração específica para GoogleTest
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compilando para macOS/Linux")
    find_package(GTest REQUIRED)
    target_include_directories(TP-Voo-Seguro PUBLIC ${GTEST_INCLUDE_DIRS})
    target_link_libraries(TP-Voo-Seguro GTest::gtest GTest::gtest_main pthread)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Compilando para Windows")
    # Instala o GoogleTest via vcpkg
    execute_process(
        COMMAND powershell -Command "Set-ExecutionPolicy RemoteSigned -Scope CurrentUser"
    )
    execute_process(
        COMMAND powershell -Command "Invoke-WebRequest -Uri https://github.com/microsoft/vcpkg/releases/download/2024.06/vcpkg-x64-windows.zip -OutFile vcpkg.zip"
    )
    execute_process(
        COMMAND powershell -Command "Expand-Archive -Path vcpkg.zip -DestinationPath vcpkg"
    )
    execute_process(
        COMMAND powershell -Command "cd vcpkg && .\\vcpkg install gtest"
    )
    find_package(GTest REQUIRED)
    target_link_libraries(TP-Voo-Seguro GTest::gtest GTest::gtest_main)
else()
    message(FATAL_ERROR "Sistema operacional não suportado!")
endif()

# Ativar testes
enable_testing()

# Adicionar subdiretório de testes (se existir)
if(EXISTS "${CMAKE_SOURCE_DIR}/test")
    add_subdirectory(test)
endif()
