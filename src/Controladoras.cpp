#include "Controladoras.hpp"

#include "ComandosSQL.hpp"
#include "Entidades.hpp"
#include "Dominios.hpp"

Desenvolvedor CntrServicoAutenticacao::autenticar(Matricula matricula, Senha senha ) {
    ComandoConsultarDesenvolvedor comandoConsultar(matricula);
    try {
        comandoConsultar.executar();
    } catch (EErroPersistencia &e) {
        throw invalid_argument("Erro ao consultar Desenvolvedor");
    }

    Desenvolvedor desenvolvedorConsultado;
    
    try {
        desenvolvedorConsultado = comandoConsultar.getResultado();
    } catch (EErroPersistencia &e) {
        throw invalid_argument("Desenvolvedor não encontrado");
    } catch (invalid_argument &e) {
        throw invalid_argument(e.what());
    }

    if (desenvolvedorConsultado.getSenha().getDado() == senha.getDado()) {
        return desenvolvedorConsultado;
    }

    Desenvolvedor desenvolvedorVazio;

    return desenvolvedorVazio;
};

bool CntrServicoDesenvolvedor::cadastrar(Desenvolvedor desenvolvedor){
    ComandoCadastrarDesenvolvedor cmdCadastrar(desenvolvedor);
    int consulta;

    try {
        cmdCadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};

bool CntrServicoDesenvolvedor::descadastrar(Matricula matricula){
    ComandoDescadastrarDesenvolvedor cmdDescadastrar(matricula);

    try {
        cmdDescadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};

bool CntrServicoDesenvolvedor::editar(Desenvolvedor desenvolvedor){
    ComandoEditarDesenvolvedor cmdEditar(desenvolvedor);

    try {
        cmdEditar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};

bool CntrServicoDesenvolvedor::visualizar(Desenvolvedor* desenvolvedor){
    //Aparecer tela
    ComandoConsultarDesenvolvedor cmdConsultar(desenvolvedor->getMatricula());

    Desenvolvedor visualizar;
    try {
        cmdConsultar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
    
    try {
        visualizar = cmdConsultar.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
    
    *desenvolvedor = visualizar;

    return true;
};


bool CntrServicoTeste::visualizar(Teste* teste){
    ComandoConsultarTeste cmdConsultar(teste->getCodigo());
    Teste testeConsultado;

    try {
        cmdConsultar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
    
    try {
        testeConsultado = cmdConsultar.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    teste = &testeConsultado;

    return true;

};

bool CntrServicoTeste::cadastrar(Teste teste, Matricula matricula){
    ComandoCadastrarTeste cmdCadastrar(teste, matricula);
    int consulta;

    try {
        cmdCadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return false;
};

bool CntrServicoTeste::editar(Teste teste){
    ComandoEditarTeste cmdEditar(teste);

    try {
        cmdEditar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};

bool CntrServicoTeste::descadastrar(Codigo codigo){
    ComandoDescadastrarTeste cmdDescadastrar(codigo);

    try {
        cmdDescadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};

bool CntrServicoCasoDeTeste::visualizar(CasoDeTeste* casoDeTeste){
    ComandoConsultarCasoDeTeste cmdConsultar(casoDeTeste->getCodigo());
    CasoDeTeste casoTesteConsultado;

    try {
        cmdConsultar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
    
    try {
        casoTesteConsultado = cmdConsultar.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
    
    casoDeTeste = &casoTesteConsultado;

    return true;
};

bool CntrServicoCasoDeTeste::cadastrar(CasoDeTeste casodeteste, Codigo codigo){
    ComandoCadastrarCasoDeTeste cmdCadastrar(casodeteste, codigo);

    try {
        cmdCadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};

bool CntrServicoCasoDeTeste::descadastrar(Codigo codigo){
    ComandoDescadastrarCasoDeTeste cmdDescadastrar(codigo);

    try {
        cmdDescadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};