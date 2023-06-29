#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "Entidades.hpp"
#include "Dominios.hpp"
class IServicoAutenticacao {
    public:
        virtual Desenvolvedor autenticar(Desenvolvedor) = 0;
        virtual ~IServicoAutenticacao(){}
};

class IServicoDesenvolvedor {
    public:
        virtual bool consultar(Desenvolvedor*) = 0;
        virtual bool cadastrar(Desenvolvedor) = 0;
        virtual bool descadastrar(Matricula) = 0;
        virtual bool editar(Desenvolvedor) = 0;
        virtual ~IServicoDesenvolvedor(){}
};

class IServicoTeste {
    public:
        virtual bool consultar(Teste*) = 0;
        virtual bool cadastrar(Teste, Matricula) = 0;
        virtual bool editar(Teste) = 0;
        virtual bool descadastrar(Codigo) = 0;
        virtual ~IServicoTeste(){}
};

class IServicoCasoDeTeste{
    public:
        virtual bool consultar(CasoDeTeste*) = 0;
        virtual bool cadastrar(CasoDeTeste, Codigo);
        virtual bool editar(CasoDeTeste) = 0;
        virtual bool descadastrar(Codigo) = 0;
        virtual ~IServicoCasoDeTeste(){}
};

class IApresentacaoAutenticacao {
    public:
        virtual bool autenticar(Desenvolvedor*) = 0;
        virtual void setCntrServicoAutenticacao(IServicoAutenticacao*) = 0;
        virtual ~IApresentacaoAutenticacao(){}
};

class IApresentacaoDesenvolvedor {
    public:
        virtual void executar(Desenvolvedor*) = 0;
        virtual void cadastrar() = 0;
        virtual void setCntrServicoDesenvolvedor(IServicoDesenvolvedor*) = 0;

        virtual ~IApresentacaoDesenvolvedor(){}
};

class IApresentacaoTeste {
    public:
        virtual void executar(Desenvolvedor*) = 0;
        virtual void setCntrServicoTeste(IServicoTeste*) = 0;
        virtual ~IApresentacaoTeste(){}
};

class IApresentacaoCasoDeTeste {
    public:
        virtual void executar(Desenvolvedor*) = 0;
        virtual void setCntrServicoCasoDeTeste(IServicoCasoDeTeste*) = 0;
        virtual ~IApresentacaoCasoDeTeste(){}
};

#endif  //  INTERFACES_HPP_INCLUDED