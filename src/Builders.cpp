#include "Builders.hpp"


CntrApresentacaoPrincipal* BuilderSistema::construir(){

    // Instanciar controladoras da camada de apresentacao.

    cntrApresentacaoControle = new CntrApresentacaoPrincipal();
    cntrApresentacaoAutenticacao = new CntrApresentacaoAutenticacao();
    cntrApresentacaoDesenvolvedor = new CntrApresentacaoDesenvolvedor();
    cntrApresentacaoTeste = new CntrApresentacaoTeste();
    cntrApresentacaoCasoDeTeste = new CntrApresentacaoCasoDeTeste();

    // Instanciar controladoras da camada de servico.

    cntrServicoDesenvolvedor = new CntrServicoDesenvolvedor();
    cntrServicoAutenticacao = new CntrServicoAutenticacao();
    cntrServicoTeste = new CntrServicoTeste();
    cntrServicoCasoDeTeste = new CntrServicoCasoDeTeste();

    // Interligar as controladoras.

    cntrApresentacaoControle->setCntrApresentacaoAutenticacao(cntrApresentacaoAutenticacao);
    cntrApresentacaoControle->setCntrApresentacaoDesenvolvedor(cntrApresentacaoDesenvolvedor);
    cntrApresentacaoControle->setCntrlApresentacaoTeste(cntrApresentacaoTeste);

    cntrApresentacaoAutenticacao->setCntrServicoAutenticacao(cntrServicoAutenticacao);

    cntrApresentacaoDesenvolvedor->setCntrServicoDesenvolvedor(cntrServicoDesenvolvedor);

    cntrApresentacaoTeste->setCntrServicoTeste(cntrServicoTeste);
    cntrApresentacaoTeste->setCntrlApresentacaoCasoDeTeste(cntrApresentacaoCasoDeTeste);

    cntrApresentacaoCasoDeTeste->setCntrServicoCasoDeTeste(cntrServicoCasoDeTeste);

    return cntrApresentacaoControle;
} 

BuilderSistema::~BuilderSistema(){
        delete cntrApresentacaoControle;
        delete cntrApresentacaoAutenticacao;
        delete cntrApresentacaoDesenvolvedor;
        delete cntrApresentacaoTeste;
        delete cntrApresentacaoCasoDeTeste;

        delete cntrServicoAutenticacao;
        delete cntrServicoDesenvolvedor;
        delete cntrServicoTeste;
        delete cntrServicoCasoDeTeste;
}
