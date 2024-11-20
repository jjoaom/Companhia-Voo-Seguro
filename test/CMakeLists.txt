# Habilita a execução de testes
enable_testing()

# Verifica se o GoogleTest está sendo configurado manualmente no Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Usando GoogleTest manualmente no Windows")
    # Adiciona o diretório de cabeçalhos do GoogleTest
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../googletest-release-1.15.2/googletest/include)
    # Adiciona o diretório de bibliotecas do GoogleTest
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../googletest-release-1.15.2/googletest)
    # Defina a variável para a biblioteca
    set(GTEST_LIBRARIES gtest gtest_main)
else()
    # Para outros sistemas, usa o find_package normalmente
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    set(GTEST_LIBRARIES ${GTEST_LIBRARY})
endif()

# Adiciona os arquivos de teste
add_executable(runTests test_main.cpp)

# Linka o GoogleTest e pthread
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Adiciona os testes
add_test(NAME TestePassageiro COMMAND runTests)
