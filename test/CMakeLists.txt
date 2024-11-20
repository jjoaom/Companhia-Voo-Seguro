# Adiciona o GoogleTest
enable_testing()

# Verifica se o GoogleTest está sendo configurado manualmente no Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Usando GoogleTest manualmente no Windows")
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )
    FetchContent_MakeAvailable(googletest)
    set(GTEST_LIBRARIES gtest)
    set(GTEST_MAIN_LIBRARIES gtest_main)
else()
    # Para outros sistemas, usa o FetchContent para baixar o GoogleTest
    find_package(GTest REQUIRED)
    set(GTEST_LIBRARIES GTest::gtest)
    set(GTEST_MAIN_LIBRARIES GTest::gtest_main)
endif()

# Adiciona os arquivos de teste
add_executable(runTestsMain test_main.cpp)

# Linka o GoogleTest e pthread
target_link_libraries(runTestsMain ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

# Adiciona os testes
add_test(NAME TestePassageiro COMMAND runTestsMain)
