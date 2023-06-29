#include "Controladoras.hpp"

#include "ComandosSQL.hpp"
#include "Entidades.hpp"
#include "Dominios.hpp"

void CntrApresentacaoControle::executar(){

    TelaControle telaControle;
    TelaMensagem telaMensagem;
    char opcaoControle;
    char opcaoMenu;

    while(true){
        opcaoControle = telaControle.apresentar();

        if(opcaoControle == '1') {
            if (cntrApresentacaoAutenticacao->autenticar(&desenvolvedor)) {
                this->menuAutenticado(&desenvolvedor);
            }
            else {
                telaMensagem.apresentar("Falha na autenticacao");
            }
        }
        else if (opcaoControle == '2') {
            cntrApresentacaoDesenvolvedor->cadastrar();
        }
        else if (opcaoControle == '3') {
            return;
        }
        else {
            telaMensagem.apresentar("Opcao invalida.");
        }
    }
    return;
}

void CntrApresentacaoControle::menuAutenticado(Desenvolvedor *desenvolvedor) {

    TelaMenu telaMenu;
    char opcao;
    const vector<string> campos({
        "1 - Meus Dados", 
        "2 - Testes e Casos de Teste",
        "3 - Sair da Plataforma",
    });

    while(true) {
        opcao = (telaMenu.apresentar("Bem Vindo!", campos)).c_str()[0];

        switch(opcao) {
        case '1':
            cntrApresentacaoDesenvolvedor->executar(desenvolvedor);
        case '2':
            cntrApresentacaoTeste->executar(desenvolvedor);
        case '3':
            return;
        default:
            TelaMensagem telaMensagem;
            telaMensagem.apresentar("Opcao Invalida");
        }
    }
}

bool CntrApresentacaoAutenticacao::autenticar(Desenvolvedor* desenvolvedor){

    Desenvolvedor resultado;

    while(true) {

        try {
            TelaAutenticacao telaAutenticacao;
            telaAutenticacao.apresentar(desenvolvedor);
            break;
        }
        catch (const invalid_argument &exp) {
            TelaMensagem telaMensagem;
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    *desenvolvedor = cntrServicoAutenticacao->autenticar(*desenvolvedor);
    if (desenvolvedor->getNome().getDado() != "") {
        return true;
    }
    return false;
};










Desenvolvedor CntrServicoAutenticacao::autenticar(Desenvolvedor desenvolvedor) {
    ComandoConsultarDesenvolvedor comandoConsultar(desenvolvedor.getMatricula());
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

    if (desenvolvedorConsultado.getSenha().getDado() == desenvolvedor.getSenha().getDado()) {
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

bool CntrServicoDesenvolvedor::consultar(Desenvolvedor* desenvolvedor){
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


bool CntrServicoTeste::consultar(Teste* teste){
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

    return true;
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

bool CntrServicoCasoDeTeste::consultar(CasoDeTeste* casoDeTeste){
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