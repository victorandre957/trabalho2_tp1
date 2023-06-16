#include "Controladoras.hpp"

//Controladoras de Serviço

// ERRO - NÃO CONSEGUI RESOLVER
bool CntrServicoAutenticacao::autenticar(Matricula *matricula, Senha senha ) {
    Desenvolvedor desenvolvedor;
    desenvolvedor.setMatricula(*matricula);
    desenvolvedor.setSenha(senha);

    //Comando do banco de dados
    //return autenticar(desenvolvedor);
};

// ERRO - NÃO CONSEGUI RESOLVER
bool CntrServicoDesenvolvedor::cadastrar(Desenvolvedor desenvolvedor){
    //Aparecer tela

    // ERRO 
    CadastrarDesenvolvedor cmdCadastrar;
    int consulta;

    try {
        consulta = cmdCadastrar.executar(desenvolvedor);
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};

bool CntrServicoDesenvolvedor::descadastrar(Matricula matricula){
    //Aparecer tela

    ComandoDescadastrarDesenvolvedor cmdDescadastrar(matricula);

    try {
        cmdDescadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
};

bool CntrServicoDesenvolvedor::editar(Desenvolvedor desenvolvedor){
    //Aparecer tela
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


// ERRO - NÃO CONSEGUI RESOLVER
bool CntrServicoTeste::visualizar(Codigo* codigo){
    ComandoConsultarTeste cmdConsultar(codigo->getDado());
    Teste visualizar;

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
    
    codigo = visualizar;

    return true;

};

bool CntrServicoTeste::cadastrar(Teste teste, Matricula matricula){
    //Aparecer tela
    ComandoCadastrarTeste cmdCadastrar(teste, matricula);
    int consulta;

    try {
        cmdCadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
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

//ERRO - Não consegui resolver
bool CntrServicoCasoDeTeste::visualizar(Codigo* codigo){
    //Aparecer tela

    ComandoConsultarCasoDeTeste cmdConsultar(*codigo->getDado());

    CasoDeTeste visualizar;
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
    
    *codigo = visualizar;

    return true;
};

bool CntrServicoCasoDeTeste::cadastrar(CasoDeTeste casodeteste, Codigo codigo){
    //Aparecer tela

    ComandoCadastrarCasoDeTeste cmdCadastrar(casodeteste, codigo);
    int consulta;

    try {
        cmdCadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
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