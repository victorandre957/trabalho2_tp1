#include "Controladoras.hpp"

#include "ComandosSQL.hpp"
#include "Entidades.hpp"
#include "Dominios.hpp"

void CntrApresentacaoPrincipal::executar(){

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

void CntrApresentacaoPrincipal::menuAutenticado(Desenvolvedor *desenvolvedor) {

    TelaMenu telaMenu;
    char opcao;
    const vector<string> campos({
        "1 - Meu Perfil", 
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

        if (desenvolvedor->getNome().getDado() != "") {
            break;
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

void CntrApresentacaoDesenvolvedor::executar(Desenvolvedor* desenvolvedor) {
    TelaMenu telaMenu;
    TelaConsultarDesenvolvedor telaDev;
    TelaConfirmarDescadastrar telaDescadastrar;
    char opcao;
    const vector<string> campos({
        "1 - Dados Pessoais", 
        "2 - Editar dados",
        "3 - Descadastrar",
        "4 - Voltar",
    });

    while(true) {
        opcao = (telaMenu.apresentar("Meu Perfil", campos)).c_str()[0];

        switch(opcao) {
            case '1':
                telaDev.apresentar(*desenvolvedor);
            case '2':
                this->editar(desenvolvedor);
            case '3':
                if (telaDescadastrar.apresentar()) {
                    cntrServicoDesenvolvedor->descadastrar(desenvolvedor->getMatricula());
                    desenvolvedor = new Desenvolvedor();
                    continue;
                }
            case '4':
                return;
            default:
                TelaMensagem telaMensagem;
                telaMensagem.apresentar("Opcao Invalida");
        }
    }
}

void CntrApresentacaoDesenvolvedor::editar(Desenvolvedor* desenvolvedor) {
    TelaFormulario telaForm;
    TelaCampo telaCampo;
    TelaMensagem telaMensagem;

    Texto nome;
    Senha senha;
    Telefone telefone;

    const vector<string> campos({
        "1 - Nome", 
        "2 - Senha",
        "3 - Telefone",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Editar dados", campos, novosDados);

    while(true) {
        try {
            nome.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            string* newName;
            telaMensagem.apresentar("O Nome não está em um formato valido");
            telaCampo.apresentar("Editar dados", "1 - Nome", newName);
            novosDados[0] = *newName;
            continue;
        }

        try {
            senha.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            string* newSenha;
            telaMensagem.apresentar("A senha não está em um formato valido");
            telaCampo.apresentar("Editar dados", "2 - Senha", newSenha);
            novosDados[1] = *newSenha;
            continue;
        }

        try {
            telefone.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            string* newTelefone;
            telaMensagem.apresentar("O Telefone não está em um formato valido");
            telaCampo.apresentar("Editar dados", "3 - Telefone", newTelefone);
            novosDados[2] = *newTelefone;
            continue;
        }

        Desenvolvedor dev;
        dev.setMatricula(desenvolvedor->getMatricula());
        dev.setNome(nome);
        dev.setSenha(senha);
        dev.setTelefone(telefone);
        if (cntrServicoDesenvolvedor->editar(dev)) {
            desenvolvedor = &dev;
        } else {
            telaMensagem.apresentar("Não foi possível editar, tente novamente.");
        };
        return;
    }
}

void CntrApresentacaoDesenvolvedor::cadastrar() {
    TelaFormulario telaForm;
    TelaCampo telaCampo;
    TelaMensagem telaMensagem;

    Matricula matricula;
    Texto nome;
    Senha senha;
    Telefone telefone;

    const vector<string> campos({
        "1 - Matricula", 
        "2 - Nome",
        "3 - Senha",
        "4 - Telefone"
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Cadastro", campos, novosDados);

    while(true) {
        try {
            matricula.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            string* newMatricula;
            telaMensagem.apresentar("A Matricula não está em um formato valido");
            telaCampo.apresentar("Cadastro", "1 - Matricula", newMatricula);
            novosDados[0] = *newMatricula;
            continue;
        }

        try {
            nome.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            string* newName;
            telaMensagem.apresentar("O Nome não está em um formato valido");
            telaCampo.apresentar("Cadastro", "2 - Nome", newName);
            novosDados[1] = *newName;
            continue;
        }

        try {
            senha.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            string* newSenha;
            telaMensagem.apresentar("A senha não está em um formato valido");
            telaCampo.apresentar("Cadastro", "3 - Senha", newSenha);
            novosDados[2] = *newSenha;
            continue;
        }

        try {
            telefone.setDado(novosDados[3]);
        } catch (const invalid_argument) {
            string* newTelefone;
            telaMensagem.apresentar("O Telefone não está em um formato valido");
            telaCampo.apresentar("Cadastro", "4 - Telefone", newTelefone);
            novosDados[3] = *newTelefone;
            continue;
        }

        Desenvolvedor dev;
        dev.setMatricula(matricula);
        dev.setNome(nome);
        dev.setSenha(senha);
        dev.setTelefone(telefone);

        if (!cntrServicoDesenvolvedor->cadastrar(dev)) {
            telaMensagem.apresentar("Não foi possível cadastrar, tente novamente.");
        }
        return;
    }
}

void CntrApresentacaoTeste::executar(Desenvolvedor* desenvolvedor) {
    TelaMenu telaMenu;
    TelaCampo telaCampo;
    TelaConsultarTeste showTeste;
    TelaConfirmarDescadastrar telaDescadastrar;
    TelaMensagem telaMensagem;
    char opcaoMenuPricipal;
    char opcaoMenuTeste;
    const vector<string> menuPricipal({
        "1 - Cadastrar Teste", 
        "2 - Consultar Teste",
        "3 - Voltar",
    });
    const vector<string> menuTeste({
        "1 - Informações do Teste", 
        "2 - Editar Dados do Teste",
        "3 - Consultar Casos de Teste",
        "4 - Descadastrar",
        "5 - Voltar",
    });

    Codigo codigo;
    Teste* teste;

    while(true) {
        opcaoMenuPricipal = (
            telaMenu.apresentar(
                "Menu do Teste", 
                menuTeste
            )
        ).c_str()[0];

        switch(opcaoMenuPricipal) {
            case '1':
                this->cadastrar(desenvolvedor->getMatricula());
            case '2':
                while(true) {
                    string* code;
                    telaCampo.apresentar(
                        "Consultar Teste",
                        "Informe o Codigo do Teste ou digite 0 para voltar", 
                        code
                    );

                    if(code->length() == 1 && code->c_str()[0] == '0') {
                        break;
                    }

                    try {
                        codigo.setDado(*code);
                        teste->setCodigo(codigo);
                        if(!cntrServicoTeste->consultar(teste)) {
                            telaMensagem.apresentar("Codigo Não Encontrado");
                            continue;
                        }
                    }
                    catch(const invalid_argument) {
                        telaMensagem.apresentar("Codigo Inválido");
                        continue;
                    }

                    while(true) {
                        opcaoMenuTeste = (
                            telaMenu.apresentar(
                                "Teste " + teste->getCodigo().getDado(), 
                                menuTeste
                            )
                        ).c_str()[0];

                        switch(opcaoMenuTeste) {
                            case '1':
                                showTeste.apresentar(*teste);
                            case '2':
                                this->editar(teste);
                            case '3':
                                cntrApresentacaoCasoDeTeste->executar(teste);
                            case '4':
                                if (telaDescadastrar.apresentar()) {
                                    cntrServicoTeste->descadastrar(teste->getCodigo());
                                    teste = new Teste();
                                    break;
                                }
                                continue;
                            case '5':
                                break;
                            default:
                                telaMensagem.apresentar("Opcao Invalida");
                        }
                    }
                }
            case '3':
                return;
            default:
                telaMensagem.apresentar("Opcao Invalida");
        }
    }
}

void CntrApresentacaoTeste::cadastrar(Matricula matricula) {
    TelaFormulario telaForm;
    TelaCampo telaCampo;
    TelaMensagem telaMensagem;

    Codigo codigo;
    Texto nome;
    Classe classe;

    const vector<string> campos({
        "1 - Codigo", 
        "2 - Nome",
        "3 - Classe",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Cadastrar Teste", campos, novosDados);

    while(true) {
        try {
            codigo.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            string* newCode;
            telaMensagem.apresentar("0 Codigo não está em um formato valido");
            telaCampo.apresentar("Cadastrar Teste", "1 - Codigo", newCode);
            novosDados[0] = *newCode;
            continue;
        }

        try {
            nome.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            string* newName;
            telaMensagem.apresentar("O Nome não está em um formato valido");
            telaCampo.apresentar("Cadastrar Teste", "2 - Nome", newName);
            novosDados[1] = *newName;
            continue;
        }

        try {
            classe.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            string* newClass;
            telaMensagem.apresentar("A Classe não está em um formato valido");
            telaCampo.apresentar("Cadastrar Teste", "3 - Classe", newClass);
            novosDados[2] = *newClass;
            continue;
        }

        Teste teste;
        teste.setCodigo(codigo);
        teste.setNome(nome);
        teste.setClasse(classe);

        if (!cntrServicoTeste->cadastrar(teste, matricula)) {
            telaMensagem.apresentar("Não foi possível cadastrar o teste, tente novamente.");
        };
        return;
    }
}

void CntrApresentacaoTeste::editar(Teste* teste) {
    TelaFormulario telaForm;
    TelaCampo telaCampo;
    TelaMensagem telaMensagem;

    Codigo codigo;
    Texto nome;
    Classe classe;

    const vector<string> campos({
        "1 - Nome",
        "2 - Classe",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Editar Teste", campos, novosDados);

    while(true) {
        try {
            nome.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            string* newName;
            telaMensagem.apresentar("O Nome não está em um formato valido");
            telaCampo.apresentar("Editar Teste", "1 - Nome", newName);
            novosDados[1] = *newName;
            continue;
        }

        try {
            classe.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            string* newClass;
            telaMensagem.apresentar("A Classe não está em um formato valido");
            telaCampo.apresentar("Editar Teste", "2 - Classe", newClass);
            novosDados[1] = *newClass;
            continue;
        }

        Teste editedTeste;
        editedTeste.setCodigo(teste->getCodigo());
        editedTeste.setNome(nome);
        editedTeste.setClasse(classe);

        if (cntrServicoTeste->editar(editedTeste)) {
            teste = &editedTeste;
        } else {
            telaMensagem.apresentar("Não foi possível Editar o teste, tente novamente.");
        }
        return;
    }
}

void CntrApresentacaoCasoDeTeste::executar(Teste* teste) {
    TelaMenu telaMenu;
    TelaCampo telaCampo;
    TelaConsultarCasoDeTeste showCasoDeTeste;
    TelaConfirmarDescadastrar telaDescadastrar;
    TelaMensagem telaMensagem;
    char opcaoMenuPricipal;
    char opcaoMenuCasoDeTeste;

    const vector<string> menuPricipal({
        "1 - Cadastrar Caso de Teste", 
        "2 - Consultar Caso de Teste",
        "3 - Voltar",
    });
    const vector<string> menuTeste({
        "1 - Informações do Caso de Teste", 
        "2 - Editar Dados do Case de Teste",
        "3 - Descadastrar",
        "4 - Voltar",
    });
    
    Codigo codigo;
    CasoDeTeste* casoDeTeste;

    while(true) {
        opcaoMenuPricipal = (
            telaMenu.apresentar(
                "Menu do Teste", 
                menuTeste
            )
        ).c_str()[0];

        switch(opcaoMenuPricipal) {
            case '1':
                this->cadastrar(teste->getCodigo());
            case '2':
                while(true) {
                    string* code;
                    telaCampo.apresentar(
                        "Consultar Caso de Teste",
                        "Informe o Codigo do Caso de Teste ou digite 0 para voltar", 
                        code
                    );

                    if(code->length() == 1 && code->c_str()[0] == '0') {
                        break;
                    }

                    try {
                        codigo.setDado(*code);
                        casoDeTeste->setCodigo(codigo);
                        if(!cntrServicoCasoDeTeste->consultar(casoDeTeste)) {
                            telaMensagem.apresentar("Codigo Não Encontrado");
                            continue;
                        }
                    }
                    catch(const invalid_argument) {
                        telaMensagem.apresentar("Codigo Inválido");
                        continue;
                    }

                    while(true) {
                        opcaoMenuCasoDeTeste = (
                            telaMenu.apresentar(
                                "Caso de Teste " + casoDeTeste->getCodigo().getDado(), 
                                menuTeste
                            )
                        ).c_str()[0];

                        switch(opcaoMenuCasoDeTeste) {
                            case '1':
                                showCasoDeTeste.apresentar(*casoDeTeste);
                            case '2':
                                this->editar(casoDeTeste);
                            case '3':
                                if (telaDescadastrar.apresentar()) {
                                    cntrServicoCasoDeTeste->descadastrar(casoDeTeste->getCodigo());
                                    casoDeTeste = new CasoDeTeste();
                                    break;
                                }
                                continue;
                            case '4':
                                break;
                            default:
                                telaMensagem.apresentar("Opcao Invalida");
                        }
                    }
                }
            case '3':
                return;
            default:
                telaMensagem.apresentar("Opcao Invalida");
        }
    }
}

void CntrApresentacaoCasoDeTeste::editar(CasoDeTeste* casoDeTeste) {
    TelaFormulario telaForm;
    TelaCampo telaCampo;
    TelaMensagem telaMensagem;

    Texto nome;
    Data data;
    Texto acao;
    Texto resposta;
    Resultado resultado;

    const vector<string> campos({
        "1 - Nome",
        "2 - Data",
        "3 - Acao",
        "4 - Resposta",
        "5 - Resultado",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Editar Caso de Teste", campos, novosDados);

    while(true) {
        try {
            nome.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            string* newName;
            telaMensagem.apresentar("O Nome não está em um formato valido");
            telaCampo.apresentar("Editar Caso de Teste", "1 - Nome", newName);
            novosDados[1] = *newName;
            continue;
        }

        try {
            data.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            string* newDate;
            telaMensagem.apresentar("A Data não está em um formato valido");
            telaCampo.apresentar("Editar Caso de Teste", "2 - Data", newDate);
            novosDados[1] = *newDate;
            continue;
        }

        try {
            acao.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            string* newAcao;
            telaMensagem.apresentar("A Acao não está em um formato valido");
            telaCampo.apresentar("Editar Caso de Teste", "3 - Acao", newAcao);
            novosDados[2] = *newAcao;
            continue;
        }

        try {
            resposta.setDado(novosDados[3]);
        } catch (const invalid_argument) {
            string* newResposta;
            telaMensagem.apresentar("A Resposta não está em um formato valido");
            telaCampo.apresentar("Editar Caso de Teste", "4 - Resposta", newResposta);
            novosDados[3] = *newResposta;
            continue;
        }

        try {
            resultado.setDado(novosDados[4]);
        } catch (const invalid_argument) {
            string* newResultado;
            telaMensagem.apresentar("O Resultado não está em um formato valido");
            telaCampo.apresentar("Editar Caso de Teste", "5 - Resultado", newResultado);
            novosDados[4] = *newResultado;
            continue;
        }

        CasoDeTeste editedCasoDeTeste;
        editedCasoDeTeste.setCodigo(casoDeTeste->getCodigo());
        editedCasoDeTeste.setNome(nome);
        editedCasoDeTeste.setData(data);
        editedCasoDeTeste.setAcao(acao);
        editedCasoDeTeste.setResposta(resposta);
        editedCasoDeTeste.setResultado(resultado);

        if (cntrServicoCasoDeTeste->editar(editedCasoDeTeste)) {
            casoDeTeste = &editedCasoDeTeste;
        } else {
            telaMensagem.apresentar("Não foi possível Editar o teste, tente novamente.");
        }
        return;
    }
}

void CntrApresentacaoCasoDeTeste::cadastrar(Codigo codigoTeste) {
    TelaFormulario telaForm;
    TelaCampo telaCampo;
    TelaMensagem telaMensagem;

    Codigo codigo;
    Texto nome;
    Data data;
    Texto acao;
    Texto resposta;
    Resultado resultado;

    const vector<string> campos({
        "1 - Codigo",
        "2 - Nome",
        "3 - Data",
        "4 - Acao",
        "5 - Resposta",
        "6 - Resultado",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Cadastrar Caso de Teste", campos, novosDados);

    while(true) {

        try {
            codigo.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            string* newCode;
            telaMensagem.apresentar("0 Codigo não está em um formato valido");
            telaCampo.apresentar("Cadastrar Caso de Teste", "1 - Codigo", newCode);
            novosDados[0] = *newCode;
            continue;
        }

        try {
            nome.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            string* newName;
            telaMensagem.apresentar("O Nome não está em um formato valido");
            telaCampo.apresentar("Cadastrar Caso de Teste", "2 - Nome", newName);
            novosDados[1] = *newName;
            continue;
        }

        try {
            data.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            string* newDate;
            telaMensagem.apresentar("A Data não está em um formato valido");
            telaCampo.apresentar("Cadastrar Caso de Teste", "3 - Data", newDate);
            novosDados[2] = *newDate;
            continue;
        }

        try {
            acao.setDado(novosDados[3]);
        } catch (const invalid_argument) {
            string* newAcao;
            telaMensagem.apresentar("A Acao não está em um formato valido");
            telaCampo.apresentar("Cadastrar Caso de Teste", "4 - Acao", newAcao);
            novosDados[3] = *newAcao;
            continue;
        }

        try {
            resposta.setDado(novosDados[4]);
        } catch (const invalid_argument) {
            string* newResposta;
            telaMensagem.apresentar("A Resposta não está em um formato valido");
            telaCampo.apresentar("Cadastrar Caso de Teste", "5 - Resposta", newResposta);
            novosDados[4] = *newResposta;
            continue;
        }

        try {
            resultado.setDado(novosDados[5]);
        } catch (const invalid_argument) {
            string* newResultado;
            telaMensagem.apresentar("O Resultado não está em um formato valido");
            telaCampo.apresentar("Cadastrar Caso de Teste", "6 - Resultado", newResultado);
            novosDados[5] = *newResultado;
            continue;
        }

        CasoDeTeste casoDeTeste;
        casoDeTeste.setCodigo(codigo);
        casoDeTeste.setNome(nome);
        casoDeTeste.setData(data);
        casoDeTeste.setAcao(acao);
        casoDeTeste.setResposta(resposta);
        casoDeTeste.setResultado(resultado);

        if (!cntrServicoCasoDeTeste->cadastrar(casoDeTeste, codigoTeste)) {
            telaMensagem.apresentar("Não foi possível cadastrar o Caso de Teste, tente novamente.");
        };
        return;
    }
}

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

bool CntrServicoCasoDeTeste::editar(CasoDeTeste casodeteste){
    ComandoEditarCasoDeTeste cmdEditar(casodeteste);

    try {
        cmdEditar.executar();
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