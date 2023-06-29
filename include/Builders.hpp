#ifndef BUILDERS_HPP
#define BUILDERS_HPP

#include "Interfaces.hpp"
#include "Controladoras.hpp"

class BuilderSistema {
    private:
        CntrApresentacaoControle* cntrApresentacaoControle;
        IApresentacaoAutenticacao* cntrApresentacaoAutenticacao;
        IApresentacaoDesenvolvedor* cntrApresentacaoDesenvolvedor;
        IApresentacaoTeste* cntrApresentacaoTeste;
        IApresentacaoCasoDeTeste* cntrApresentacaoCasoDeTeste;

        IServicoAutenticacao *cntrServicoAutenticacao;
        IServicoDesenvolvedor *cntrServicoDesenvolvedor;
        IServicoTeste* cntrServicoTeste;
        IServicoCasoDeTeste* cntrServicoCasoDeTeste;

    public:
        CntrApresentacaoControle* construir();
        ~BuilderSistema();
};

#endif // BUILDERS_HPP