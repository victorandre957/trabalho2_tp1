#ifndef CONTROLADORAS_HPP
#define CONTROLADORAS_HPP

#include "Interfaces.hpp"
#include "curses.hpp"
#include "ComandosSQL.hpp"
#include "Telas.hpp"

class CntrApresentacaoPrincipal {
    private:
        Desenvolvedor desenvolvedor;
        IApresentacaoAutenticacao* cntrApresentacaoAutenticacao;
        IApresentacaoDesenvolvedor* cntrApresentacaoDesenvolvedor;
        IApresentacaoTeste* cntrApresentacaoTeste;
        IApresentacaoCasoDeTeste* cntrApresentacaoCasoDeTeste;
        void menuAutenticado(Desenvolvedor*);

    public:
        void executar();
        void setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao*);
        void setCntrApresentacaoDesenvolvedor(IApresentacaoDesenvolvedor*);
        void setCntrlApresentacaoTeste(IApresentacaoTeste*);
        void setCntrlApresentacaoCasoDeTeste(IApresentacaoCasoDeTeste*);
};

void inline CntrApresentacaoPrincipal::setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao* cntr){
    this->cntrApresentacaoAutenticacao = cntr;
}

void inline CntrApresentacaoPrincipal::setCntrApresentacaoDesenvolvedor(IApresentacaoDesenvolvedor* cntr){
    this->cntrApresentacaoDesenvolvedor = cntr;
}

void inline CntrApresentacaoPrincipal::setCntrlApresentacaoTeste(IApresentacaoTeste* cntr){
    this->cntrApresentacaoTeste = cntr;
}

void inline CntrApresentacaoPrincipal::setCntrlApresentacaoCasoDeTeste(IApresentacaoCasoDeTeste* cntr){
    this->cntrApresentacaoCasoDeTeste = cntr;
}

class CntrApresentacaoAutenticacao:public IApresentacaoAutenticacao {
    private:
        IServicoAutenticacao* cntrServicoAutenticacao;
    public:
        bool autenticar(Desenvolvedor*);
        void setCntrServicoAutenticacao(IServicoAutenticacao*);
};

void inline CntrApresentacaoAutenticacao::setCntrServicoAutenticacao(IServicoAutenticacao* cntrServicoAutenticacao){
    this->cntrServicoAutenticacao = cntrServicoAutenticacao;
}

class CntrApresentacaoDesenvolvedor:public IApresentacaoDesenvolvedor {
private:
    IServicoDesenvolvedor* cntrServicoDesenvolvedor;
    bool cadastro;
public:
    void executar(Desenvolvedor*);
    void cadastrar();
    void editar(Desenvolvedor*);
    void setCntrServicoDesenvolvedor(IServicoDesenvolvedor*);
};

void inline CntrApresentacaoDesenvolvedor::setCntrServicoDesenvolvedor(IServicoDesenvolvedor* cntrServicoDesenvolvedor){
    this->cntrServicoDesenvolvedor = cntrServicoDesenvolvedor;
}

class CntrApresentacaoTeste:public IApresentacaoTeste {
    private:
        IServicoTeste* cntrServicoTeste;
        IApresentacaoCasoDeTeste* cntrApresentacaoCasoDeTeste;
    public:
        void executar(Desenvolvedor*);
        void cadastrar(Matricula);
        void editar(Teste*);

        void setCntrServicoTeste(IServicoTeste*);
        void setCntrlApresentacaoCasoDeTeste(IApresentacaoCasoDeTeste*);
};

void inline CntrApresentacaoTeste::setCntrServicoTeste(IServicoTeste* cntrServicoTeste){
    this->cntrServicoTeste = cntrServicoTeste;
}

void inline CntrApresentacaoTeste::setCntrlApresentacaoCasoDeTeste(IApresentacaoCasoDeTeste* cntr){
    this->cntrApresentacaoCasoDeTeste = cntr;
}

class CntrApresentacaoCasoDeTeste:public IApresentacaoCasoDeTeste {
    private:
        IServicoCasoDeTeste* cntrServicoCasoDeTeste;
    public:
        void executar(Teste*);
        void cadastrar(Codigo);
        void editar(CasoDeTeste*);
        void setCntrServicoCasoDeTeste(IServicoCasoDeTeste*);
};

void inline CntrApresentacaoCasoDeTeste::setCntrServicoCasoDeTeste(IServicoCasoDeTeste* cntrServicoCasoDeTeste){
    this->cntrServicoCasoDeTeste = cntrServicoCasoDeTeste;
}

class CntrServicoAutenticacao: public IServicoAutenticacao{
    public:
        Desenvolvedor autenticar(Desenvolvedor);
};

class CntrServicoDesenvolvedor: public IServicoDesenvolvedor{
    public:
        bool consultar(Desenvolvedor*);
        bool cadastrar(Desenvolvedor);
        bool descadastrar(Matricula);
        bool editar(Desenvolvedor);

};
class CntrServicoTeste: public IServicoTeste {
    public:
        bool consultar(Teste*);
        bool cadastrar(Teste, Matricula);
        bool editar(Teste);
        bool descadastrar(Codigo);
        //listar testes
};

class CntrServicoCasoDeTeste: public IServicoCasoDeTeste{
        bool consultar(CasoDeTeste*);
        bool cadastrar(CasoDeTeste, Codigo);
        bool editar(CasoDeTeste);
        bool descadastrar(Codigo);
        //listar casos de teste
};

#endif  //  CONTROLADORAS_HPP