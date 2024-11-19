#include <gtest/gtest.h>
#include "../main.cpp" // Inclua o arquivo principal para acessar as classes e funções

// Teste para o construtor padrão da classe Passageiro
TEST(PassageiroTest, DefaultConstructor) {
    Passageiro p;
    EXPECT_EQ(p.getId(), 0);
    EXPECT_EQ(p.getNome(), "");
    EXPECT_EQ(p.ehFiel(), false);
    EXPECT_EQ(p.getPontosFidelidade(), 0);
}

// Teste para o construtor parametrizado da classe Passageiro
TEST(PassageiroTest, ParametrizedConstructor) {
    Passageiro p("João", "Rua A", "123456789", true, 100);
    EXPECT_EQ(p.getNome(), "João");
    EXPECT_EQ(p.ehFiel(), true);
    EXPECT_EQ(p.getPontosFidelidade(), 100);
}

// Função principal para rodar todos os testes
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}