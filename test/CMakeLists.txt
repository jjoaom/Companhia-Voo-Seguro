# Adiciona o GoogleTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Adiciona os arquivos de teste
add_executable(runTests test_main.cpp)

# Linka o GoogleTest e pthread
target_link_libraries(runTests GTest::gtest GTest::gtest_main pthread)

# Adiciona os testes
add_test(NAME TestePassageiro COMMAND runTests)