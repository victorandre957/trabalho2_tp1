#ifndef CONTROLADORAS_HPP
#define CONTROLADORAS_HPP

#include "Interfaces.hpp"
#include "curses.hpp"
#include "ComandosSQL.hpp"
#include "Telas.hpp"

class CntrApresentacaoControle {
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

inline void CntrApresentacaoControle::setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao* cntr){
    cntrApresentacaoAutenticacao = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoDesenvolvedor(IApresentacaoDesenvolvedor* cntr){
    cntrApresentacaoDesenvolvedor = cntr;
}

inline void CntrApresentacaoControle::setCntrlApresentacaoTeste(IApresentacaoTeste* cntr){
    cntrApresentacaoTeste = cntr;
}

inline void CntrApresentacaoControle::setCntrlApresentacaoCasoDeTeste(IApresentacaoCasoDeTeste* cntr){
    cntrApresentacaoCasoDeTeste = cntr;
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
    void setCntrServicoDesenvolvedor(IServicoDesenvolvedor*);
};

void inline CntrApresentacaoDesenvolvedor::setCntrServicoDesenvolvedor(IServicoDesenvolvedor* cntrServicoDesenvolvedor){
    this->cntrServicoDesenvolvedor = cntrServicoDesenvolvedor;
}

class CntrApresentacaoTeste:public IApresentacaoTeste {
    private:
        IServicoTeste* cntrServicoTeste;
    public:
        void executar(Desenvolvedor*);
        void setCntrServicoTeste(IServicoTeste*);
};

void inline CntrApresentacaoTeste::setCntrServicoTeste(IServicoTeste* cntrServicoTeste){
    this->cntrServicoTeste = cntrServicoTeste;
}

class CntrApresentacaoCasoDeTeste:public IApresentacaoCasoDeTeste {
    private:
        IServicoCasoDeTeste* cntrServicoCasoDeTeste;
    public:
        void executar(Desenvolvedor*);
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