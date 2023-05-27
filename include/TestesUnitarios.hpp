#ifndef TESTSUNITARIOS_HPP
#define TESTSUNITARIOS_HPP

#include "Dominios.hpp"
#include "Entidades.hpp"

//por: Victor André 211026664 (Codificação) e Luan Guedes (Documentação)
class TestDominio {
    protected:
        bool estado;
        Dominio * dominio;
        const string * DADO_VALIDO;
        const string * DADO_INVALIDO;
        virtual void setUp() = 0;
        void tearDown();
        virtual void testarCasoValido();
        virtual void testarCasoInvalido();

    public:
        bool run();
};

class TestClasse:public TestDominio{
    private:
        void setUp();
};

class TestCodigo:public TestDominio{
    private:
        void setUp();
};

class TestData:public TestDominio{
    private:
        void setUp();
};

class TestMatricula:public TestDominio{
    private:
        void setUp();
};

class TestResultado:public TestDominio{
    private:
        void setUp();
};

class TestSenha:public TestDominio{
    private:
        void setUp();
};

class TestTelefone:public TestDominio{
    private:
        void setUp();
};

class TestTexto:public TestDominio{
    private:
        void setUp();
};

class TestDesenvolvedor {
    private:
       Desenvolvedor * desenvolvedor;
       const string * MATRICULA_VALIDA;
       const string * NOME_VALIDO;
       const string * SENHA_VALIDA;
       const string * TELEFONE_VALIDO;

        bool estado;
        void setUp();
        void tearDown();
        void testarCasoSucesso();
    public:
        bool run();
};

class TestTeste {
    private:
        Teste * teste;
        const string * CODIGO_VALIDO;
        const string * NOME_VALIDO;
        const string * CLASSE_VALIDA;

        bool estado;
        void setUp();
        void tearDown();
        void testarCasoSucesso();

    public:
        bool run();
};

class TestCasoDeTeste {
    private:
        CasoDeTeste * casoDeTeste;
        const string * CODIGO_VALIDO;
        const string * NOME_VALIDO;
        const string * DATA_VALIDA;
        const string * ACAO_VALIDA;
        const string * RESPOSTA_VALIDA;
        const string * RESULTADO_VALIDO;

        bool estado;
        void setUp();
        void tearDown();
        void testarCasoSucesso();

    public:
        bool run();
};

#endif // TESTSUNITARIOS_HPP