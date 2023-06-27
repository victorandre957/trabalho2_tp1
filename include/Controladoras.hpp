#ifndef CONTROLADORAS_HPP
#define CONTROLADORAS_HPP

#include "Interfaces.hpp"
#include "curses.hpp"
#include "ComandosSQL.hpp"
#include "Telas.hpp"

class CntrServicoAutenticacao: public IServicoAutenticacao{
    public:
        Desenvolvedor autenticar(Matricula, Senha);
};

class CntrServicoDesenvolvedor: public IServicoDesenvolvedor{
    public:
        bool consultar(Desenvolvedor*);
        bool cadastrar(Desenvolvedor);
        bool descadastrar(Matricula);
        bool editar(Desenvolvedor);

};
class CntrServicoTeste: public IServicoTeste{
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