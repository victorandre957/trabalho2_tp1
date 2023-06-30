#ifndef BUILDERS_HPP
#define BUILDERS_HPP

#include "Interfaces.hpp"
#include "Controladoras.hpp"

class BuilderSistema {
    private:
        CntrApresentacaoPrincipal* cntrApresentacaoControle;
        IApresentacaoAutenticacao* cntrApresentacaoAutenticacao;
        IApresentacaoDesenvolvedor* cntrApresentacaoDesenvolvedor;
        IApresentacaoTeste* cntrApresentacaoTeste;
        IApresentacaoCasoDeTeste* cntrApresentacaoCasoDeTeste;

        IServicoAutenticacao *cntrServicoAutenticacao;
        IServicoDesenvolvedor *cntrServicoDesenvolvedor;
        IServicoTeste* cntrServicoTeste;
        IServicoCasoDeTeste* cntrServicoCasoDeTeste;

    public:
        CntrApresentacaoPrincipal* construir();
        ~BuilderSistema();
};

#endif // BUILDERS_HPP