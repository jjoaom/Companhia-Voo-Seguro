# Habilita a execução de testes
enable_testing()

# Verifica se o GoogleTest está sendo configurado manualmente no Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Usando GoogleTest manualmente no Windows")
    # Inclui os diretórios de cabeçalhos do GoogleTest
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../googletest-release-1.15.2/googletest/include)
    # Linka a biblioteca do GoogleTest
    set(GTEST_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../googletest-release-1.15.2/googletest/libgtest.a)
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
