# Adiciona o GoogleTest
enable_testing()

# Verifica se o GoogleTest está sendo configurado manualmente no Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Usando GoogleTest manualmente no Windows")
    # Inclui os diretórios de cabeçalhos do GoogleTest
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../googletest-release-1.15.2/googletest/include)
    # Linka a biblioteca do GoogleTest
    set(GTEST_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../googletest-release-1.15.2/googletest/libgtest.a)
    set(GTEST_MAIN_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../googletest-release-1.15.2/googletest/libgtest_main.a)
else()
    # Para outros sistemas, usa o FetchContent para baixar o GoogleTest
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    )
    FetchContent_MakeAvailable(googletest)
    set(GTEST_LIBRARIES gtest)
    set(GTEST_MAIN_LIBRARIES gtest_main)
endif()

# Adiciona os arquivos de teste
add_executable(runTests test_main.cpp)

# Linka o GoogleTest e pthread
target_link_libraries(runTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

# Adiciona os testes
add_test(NAME TestePassageiro COMMAND runTests)
