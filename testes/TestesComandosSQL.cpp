#include <gtest/gtest.h>

#include "ComandosSQL.hpp"
#include "Entidades.hpp"
#include "Dominios.hpp"

// Cadastrar um desenvolvedor no banco

TEST(testComandoSQL, cadastrarDesenvolvedor) {
  Desenvolvedor desenvolvedor;

  Matricula matricula;
  matricula.setDado("1234566");
  desenvolvedor.setMatricula(matricula);

  Texto nome;
  nome.setDado("Victor Andre");
  desenvolvedor.setNome(nome);

  Senha senha;
  senha.setDado("A1B2C3");
  desenvolvedor.setSenha(senha);

  Telefone telefone;
  telefone.setDado("+61993121401");
  desenvolvedor.setTelefone(telefone);

  ComandoCadastrarDesenvolvedor comandoCadastrar(desenvolvedor);
  try {
    comandoCadastrar.executar();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro ao executar\n" << e.what();
  }
}

// Consultar um desenvolvedor no banco

TEST(testComandoSQL, consultarDesenvolvedor) {

  Matricula matricula;
  matricula.setDado("1234566");

  ComandoConsultarDesenvolvedor comandoConsultar(matricula);
  try {
    comandoConsultar.executar();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro ao executar\n" << e.what();
  }

  Desenvolvedor desenvolvedorConsultado;
  
  try {
      desenvolvedorConsultado = comandoConsultar.getResultado();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro em getResultado\n" << e.what();
  } catch (invalid_argument &e) {
    FAIL() << e.what();
  }

  EXPECT_STREQ(desenvolvedorConsultado.getMatricula().getDado().c_str(), "1234566");
  EXPECT_STREQ(desenvolvedorConsultado.getNome().getDado().c_str(), "Victor Andre");
  EXPECT_STREQ(desenvolvedorConsultado.getSenha().getDado().c_str(), "A1B2C3");
  EXPECT_STREQ(desenvolvedorConsultado.getTelefone().getDado().c_str(), "+61993121401");
}

// Editar um desenvolvedor no banco

TEST(testComandoSQL, editarDesenvolvedor) {
  Desenvolvedor desenvolvedor;

  Matricula matricula;
  matricula.setDado("1234566");

  ComandoConsultarDesenvolvedor comandoConsultar(matricula);
  try {
    comandoConsultar.executar();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro ao executar\n" << e.what();
  }

  Desenvolvedor desenvolvedorEditar;
  
  try {
      desenvolvedorEditar = comandoConsultar.getResultado();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro em getResultado\n" << e.what();
  } catch (invalid_argument &e) {
    FAIL() << e.what();
  }

  Texto nome;
  nome.setDado("Luan Guedes");
  desenvolvedorEditar.setNome(nome);

  Senha senha;
  senha.setDado("C3B2A1");
  desenvolvedorEditar.setSenha(senha);

  ComandoEditarDesenvolvedor comandoEditar(desenvolvedorEditar);
  try {
    comandoEditar.executar();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro ao executar\n" << e.what();
  }

  Desenvolvedor desenvolvedorEditado;

  try {
      comandoConsultar.executar();
      desenvolvedorEditado = comandoConsultar.getResultado();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro em getResultado\n" << e.what();
  } catch (invalid_argument &e) {
    FAIL() << e.what();
  }

  EXPECT_STREQ(desenvolvedorEditado.getMatricula().getDado().c_str(), "1234566");
  EXPECT_STREQ(desenvolvedorEditado.getNome().getDado().c_str(), "Luan Guedes");
  EXPECT_STREQ(desenvolvedorEditado.getSenha().getDado().c_str(), "C3B2A1");
  EXPECT_STREQ(desenvolvedorEditado.getTelefone().getDado().c_str(), "+61993121401");
}

// Descadastrar um desenvolvedor do banco

TEST(testComandoSQL, descadastrarDesenvolvedor) {

  Matricula matricula;
  matricula.setDado("1234566");

  ComandoDescadastrarDesenvolvedor comandoDescadastrar(matricula);
  try {
    comandoDescadastrar.executar();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro ao executar\n" << e.what();
  }

  ComandoConsultarDesenvolvedor comandoConsultar(matricula);
  try {
    comandoConsultar.executar();
  } catch (EErroPersistencia &e) {
      FAIL() << "Erro ao executar\n" << e.what();
  }

  ASSERT_THROW(comandoConsultar.getResultado(), EErroPersistencia);
}