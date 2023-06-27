#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "Entidades.hpp"
#include "Dominios.hpp"

// Interfaces de serviço

class IServicoAutenticacao {
    public:
        virtual Desenvolvedor autenticar(Matricula, Senha) = 0;
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
        virtual bool cadastrar(Teste) = 0;
        virtual bool editar(Teste) = 0;
        virtual bool descadastrar(Teste) = 0;
        virtual ~IServicoTeste(){}
};

class IServicoCasoDeTeste{
    public:
        virtual bool consultar(CasoDeTeste*) = 0;
        virtual bool cadastrar(CasoDeTeste) = 0;
        virtual bool descadastrar(CasoDeTeste) = 0;
        virtual ~IServicoCasoDeTeste(){}
};

#endif  //  INTERFACES_HPP_INCLUDED