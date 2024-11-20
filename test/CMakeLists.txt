# Adiciona o GoogleTest
enable_testing()

# Verifica se o GoogleTest foi encontrado corretamente
if(NOT TARGET GTest::gtest)
    # Se não encontrado, configura o GoogleTest para uso
    find_package(GTest REQUIRED)
endif()

# Inclui o diretório de cabeçalhos do GoogleTest
include_directories(${GTEST_INCLUDE_DIRS})

# Adiciona os arquivos de teste
add_executable(runTests test_main.cpp)

# Linka o GoogleTest e pthread (necessário no Linux)
target_link_libraries(runTests GTest::gtest GTest::gtest_main pthread)

# Adiciona os testes
add_test(NAME TestePassageiro COMMAND runTests)
