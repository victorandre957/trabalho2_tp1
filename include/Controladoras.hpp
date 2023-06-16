#ifndef CONTROLADORAS_HPP
#define CONTROLADORAS_HPP

#include "Interfaces.hpp"
#include "./curses.hpp"
#include "ComandosSQL.hpp"
#include "Telas.hpp"

//Controladoras de Servico

class CntrServicoAutenticacao: public IServicoAutenticacao{
    public:
        bool autenticar(Matricula, Senha);
};

class CntrServicoDesenvolvedor: public IServicoDesenvolvedor{
    public:
        bool cadastrar(Desenvolvedor);
        bool descadastrar(Matricula);
        bool editar(Desenvolvedor);
        bool visualizar(Desenvolvedor*);

};

class CntrServicoTeste: public IServicoTeste{
    public:
        bool visualizar(Codigo*);
        bool cadastrar(Teste, Matricula);
        bool editar(Teste);
        bool descadastrar(Codigo);
        //listar testes
};

class CntrServicoCasoDeTeste: public IServicoCasoDeTeste{
        bool visualizar(CasoDeTeste);
        bool cadastrar(CasoDeTeste, Codigo);
        bool descadastrar(Codigo);
        //listar casos de teste
};

#endif  //  CONTROLADORAS_HPP