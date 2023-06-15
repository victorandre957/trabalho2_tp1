#ifndef CONTROLADORAS_HPP
#define CONTROLADORAS_HPP

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
        bool visualizar(Teste*);
        bool cadastrar(Teste);
        bool editar(Teste);
        bool descadastrar(Teste);
};

class CntrServicoCasoDeTeste: public IServicoCasoDeTeste{
        bool visualizar(CasoDeTeste*);
        bool cadastrar(CasoDeTeste);
        bool descadastrar(CasoDeTeste);
};

#endif  //  CONTROLADORAS_HPP