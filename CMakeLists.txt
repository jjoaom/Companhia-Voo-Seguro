# Defina a versão mínima do CMake
cmake_minimum_required(VERSION 3.14)

# Nome do projeto
project(Companhia-Voo-Seguro)

# Defina a versão do C++ que você quer usar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Mensagens de status para saber onde estamos
message(STATUS "Compilando para o sistema: ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMake versão: ${CMAKE_VERSION}")

# Add this line to set the runtime library
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Defina configurações específicas com base no sistema operacional
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compilando para macOS/Linux")
    # Verifica se o GoogleTest foi encontrado corretamente
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(main ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
else()
    target_link_libraries(main GTest::gtest GTest::gtest_main pthread)
endif()

# Adiciona o arquivo de código-fonte principal
add_executable(main main.cpp)
target_link_libraries(main ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
# Linka o GoogleTest
enable_testing()

# Configura o link do GoogleTest
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(main ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
else()
    target_link_libraries(main GTest::gtest GTest::gtest_main)
endif()

# Adiciona o subdiretório de testes
add_subdirectory(test)
