# Adiciona o GoogleTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Adiciona os arquivos de teste
add_executable(runTests test_main.cpp Passageiro_test.cpp Tripulacao_test.cpp Voo_test.cpp Assento_test.cpp Reserva_test.cpp)

# Linka o GoogleTest e pthread
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Adiciona os testes
add_test(NAME TestePassageiro COMMAND runTests)