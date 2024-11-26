#include <gtest/gtest.h>
#define RUNNING_TESTS
#include "../main.cpp" 

// Teste para o método setId da classe Passageiro
TEST(PassageiroTest, SetId) {
    Passageiro p;
    p.setId(10);
    EXPECT_EQ(p.getId(), 10);
}

// Teste para o método setPontosFidelidade da classe Passageiro
TEST(PassageiroTest, SetPontosFidelidade) {
    Passageiro p;
    p.setPontosFidelidade(50);
    EXPECT_EQ(p.getPontosFidelidade(), 50);
}

// Teste para o método increaseFidelidade da classe Passageiro
TEST(PassageiroTest, IncreaseFidelidade) {
    Passageiro p;
    p.increaseFidelidade();
    EXPECT_EQ(p.getPontosFidelidade(), 10);
}

// Teste para o construtor padrão da classe Tripulacao
TEST(TripulacaoTest, DefaultConstructor) {
    Tripulacao t;
    EXPECT_EQ(t.getId(), 1);
    EXPECT_EQ(t.getNome(), "");
    EXPECT_EQ(t.getCargo(), Tripulacao::Cargo::Piloto);
}

// Teste para o construtor parametrizado da classe Tripulacao
TEST(TripulacaoTest, ParametrizedConstructor) {
    Tripulacao t("Carlos", "987654321", Tripulacao::Cargo::Copiloto);
    EXPECT_EQ(t.getNome(), "Carlos");
    EXPECT_EQ(t.getCargo(), Tripulacao::Cargo::Copiloto);
}

// Teste para o método setId da classe Tripulacao
TEST(TripulacaoTest, SetId) {
    Tripulacao t;
    t.setId(20);
    EXPECT_EQ(t.getId(), 20);
}

// Teste para o método verificaCargo da classe Tripulacao
TEST(TripulacaoTest, VerificaCargo) {
    Tripulacao t;
    EXPECT_EQ(t.verificaCargo(1), Tripulacao::Cargo::Piloto);
    EXPECT_EQ(t.verificaCargo(2), Tripulacao::Cargo::Copiloto);
    EXPECT_EQ(t.verificaCargo(3), Tripulacao::Cargo::Comissario);
}

// Teste para o construtor padrão da classe Voo
TEST(VooTest, DefaultConstructor) {
    Voo v;
    EXPECT_EQ(v.getId(), 1);
    EXPECT_EQ(v.getStatus(), false);
    EXPECT_EQ(v.getTarifa(), 0.0);
}

// Teste para o construtor parametrizado da classe Voo
TEST(VooTest, ParametrizedConstructor) {
    Voo v("2023-10-10", "10:00", "São Paulo", "Rio de Janeiro", 1, 1, 2, 3, true, 300.0);
    EXPECT_EQ(v.getStatus(), true);
    EXPECT_EQ(v.getTarifa(), 300.0);
}

// Teste para o método setId da classe Voo
TEST(VooTest, SetId) {
    Voo v;
    v.setId(30);
    EXPECT_EQ(v.getId(), 30);
}

// Teste para o método setTarifa da classe Voo
TEST(VooTest, SetTarifa) {
    Voo v;
    v.setTarifa(500.0);
    EXPECT_EQ(v.getTarifa(), 500.0);
}