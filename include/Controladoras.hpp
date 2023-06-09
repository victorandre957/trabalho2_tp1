#ifndef CONTROLADORAS_HPP
#define CONTROLADORAS_HPP

#include "Interfaces.hpp"
#include "Dominios.hpp"
#include "curses.hpp"

//por: Victor André 211026664
class CntrApresentacaoPrincipal {
    private:
        Desenvolvedor desenvolvedor;
        IApresentacaoAutenticacao* cntrApresentacaoAutenticacao;
        IApresentacaoDesenvolvedor* cntrApresentacaoDesenvolvedor;
        IApresentacaoTeste* cntrApresentacaoTeste;
        void menuAutenticado(Desenvolvedor*);

    public:
        void executar();
        void setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao*);
        void setCntrApresentacaoDesenvolvedor(IApresentacaoDesenvolvedor*);
        void setCntrlApresentacaoTeste(IApresentacaoTeste*);
};

inline void CntrApresentacaoPrincipal::setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao* cntr){
    this->cntrApresentacaoAutenticacao = cntr;
}

inline void CntrApresentacaoPrincipal::setCntrApresentacaoDesenvolvedor(IApresentacaoDesenvolvedor* cntr){
    this->cntrApresentacaoDesenvolvedor = cntr;
}

inline void CntrApresentacaoPrincipal::setCntrlApresentacaoTeste(IApresentacaoTeste* cntr){
    this->cntrApresentacaoTeste = cntr;
}

//por: Victor André 211026664
class CntrApresentacaoAutenticacao:public IApresentacaoAutenticacao {
    private:
        IServicoAutenticacao* cntrServicoAutenticacao;
    public:
        bool autenticar(Desenvolvedor*);
        void setCntrServicoAutenticacao(IServicoAutenticacao*);
};

void inline CntrApresentacaoAutenticacao::setCntrServicoAutenticacao(IServicoAutenticacao* cntr){
    this->cntrServicoAutenticacao = cntr;
}

//por: Victor André 211026664
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

void inline CntrApresentacaoDesenvolvedor::setCntrServicoDesenvolvedor(IServicoDesenvolvedor* cntr){
    this->cntrServicoDesenvolvedor = cntr;
}

//por: Victor André 211026664
class CntrApresentacaoTeste: public IApresentacaoTeste {
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

//por: Victor André 211026664
class CntrApresentacaoCasoDeTeste: public IApresentacaoCasoDeTeste {
    private:
        IServicoCasoDeTeste* cntrServicoCasoDeTeste;
    public:
        void executar(Teste*);
        void cadastrar(Codigo);
        void editar(CasoDeTeste*);

        void setCntrServicoCasoDeTeste(IServicoCasoDeTeste*);
};

void inline CntrApresentacaoCasoDeTeste::setCntrServicoCasoDeTeste(IServicoCasoDeTeste* cntr){
    this->cntrServicoCasoDeTeste = cntr;
}

//por: Luan Guedes 211026628
class CntrServicoAutenticacao: public IServicoAutenticacao{
    public:
        bool autenticar(Desenvolvedor*);
};

//por: Luan Guedes 211026628
class CntrServicoDesenvolvedor: public IServicoDesenvolvedor{
    public:
        bool consultar(Desenvolvedor*);
        bool cadastrar(Desenvolvedor);
        bool descadastrar(Matricula);
        bool editar(Desenvolvedor);

};

//por: Luan Guedes 211026628
class CntrServicoTeste: public IServicoTeste {
    public:
        bool consultar(Teste*, Desenvolvedor);
        bool cadastrar(Teste, Matricula);
        bool editar(Teste);
        bool descadastrar(Codigo);
};

//por: Luan Guedes 211026628
class CntrServicoCasoDeTeste: public IServicoCasoDeTeste {
        bool consultar(CasoDeTeste*, Teste);
        bool checkQuantidade(Codigo); // Codigo do teste
        bool cadastrar(CasoDeTeste, Codigo);
        bool editar(CasoDeTeste);
        bool descadastrar(Codigo);
};

#endif  //  CONTROLADORAS_HPP