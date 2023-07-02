#include "Controladoras.hpp"
#include "ComandosSQL.hpp"
#include "Telas.hpp"

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
            continue;
        }
        else if (opcaoControle == '2') {
            cntrApresentacaoDesenvolvedor->cadastrar();
            continue;
        }
        else if (opcaoControle == '3') {
            return;
        }
        else {
            telaMensagem.apresentar("Opcao invalida.");
            continue;
        }
    }
    return;
}

void CntrApresentacaoPrincipal::menuAutenticado(Desenvolvedor *desenvolvedor) {

    TelaMenu telaMenu;
    char opcao;
    const vector<string> campos({
        "1 - Meu Perfil: ", 
        "2 - Testes e Casos de Teste: ",
        "3 - Sair da Plataforma: ",
    });

    while(true) {
        opcao = (telaMenu.apresentar("Bem Vindo!", campos)).c_str()[0];

        switch(opcao) {
        case '1':
            try {
                cntrApresentacaoDesenvolvedor->executar(desenvolvedor);
            } catch(const invalid_argument) {
                return;
            }
            continue;
        case '2':
            cntrApresentacaoTeste->executar(desenvolvedor);
            continue;
        case '3':
            return;
        default:
            TelaMensagem telaMensagem;
            telaMensagem.apresentar("Opcao Invalida");
            continue;
        }

        if (desenvolvedor->getNome().getDado() != "") {
            break;
        }
    }
}

bool CntrApresentacaoAutenticacao::autenticar(Desenvolvedor* desenvolvedor){
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

    return cntrServicoAutenticacao->autenticar(desenvolvedor);
};

void CntrApresentacaoDesenvolvedor::executar(Desenvolvedor* desenvolvedor) {
    TelaMenu telaMenu;
    TelaMensagem telaMensagem;
    TelaConsultarDesenvolvedor telaDev;
    TelaConfirmarDescadastrar telaDescadastrar;
    char opcao;
    const vector<string> campos({
        "1 - Dados Pessoais: ", 
        "2 - Editar dados: ",
        "3 - Descadastrar: ",
        "4 - Voltar: ",
    });

    while(true) {
        opcao = (telaMenu.apresentar("Meu Perfil", campos)).c_str()[0];

        switch(opcao) {
            case '1':
                telaDev.apresentar(*desenvolvedor);
                continue;
            case '2':
                this->editar(desenvolvedor);
                continue;
            case '3':
                if (telaDescadastrar.apresentar()) {
                    if (cntrServicoDesenvolvedor->descadastrar(desenvolvedor->getMatricula())) {
                        telaMensagem.apresentar("Desenvolvedor Descadastrado com Sucesso.");
                        desenvolvedor = new Desenvolvedor();
                        throw invalid_argument("Descadastrado");
                    } else {
                        telaMensagem.apresentar("Não foi possivel descadastrar, tente novamente.");
                        continue;
                    }
                }
                continue;
            case '4':
                return;
            default:
                TelaMensagem telaMensagem;
                telaMensagem.apresentar("Opcao Invalida");
                continue;
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
        "1 - Nome: ", 
        "2 - Senha: ",
        "3 - Telefone: ",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Editar dados", campos, novosDados);

    while(true) {
        try {
            nome.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Nome nao esta em um formato valido");
            novosDados[0] = telaCampo.apresentar("Editar dados", "1 - Nome: ");
            continue;
        }

        try {
            senha.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A senha nao esta em um formato valido");
            novosDados[1] = telaCampo.apresentar("Editar dados", "2 - Senha: ");
            continue;
        }

        try {
            telefone.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Telefone nao esta em um formato valido");
            novosDados[2] = telaCampo.apresentar("Editar dados", "3 - Telefone: ");
            continue;
        }

        Desenvolvedor dev;
        dev.setMatricula(desenvolvedor->getMatricula());
        dev.setNome(nome);
        dev.setSenha(senha);
        dev.setTelefone(telefone);
        if (cntrServicoDesenvolvedor->editar(dev)) {
            desenvolvedor->setNome(nome);
            desenvolvedor->setSenha(senha);
            desenvolvedor->setTelefone(telefone);
            telaMensagem.apresentar("Desenvolvedor Editado com Sucesso.");
        } else {
            telaMensagem.apresentar("Nao foi possivel editar, tente novamente.");
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
        "1 - Matricula: ", 
        "2 - Nome: ",
        "3 - Senha: ",
        "4 - Telefone: ",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Cadastro", campos, novosDados);

    while(true) {
        try {
            matricula.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Matricula nao esta em um formato valido");
            novosDados[0] = telaCampo.apresentar("Cadastro", "1 - Matricula: ");
            continue;
        }

        try {
            nome.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Nome nao esta em um formato valido");
            novosDados[1] = telaCampo.apresentar("Cadastro", "2 - Nome: ");
            continue;
        }

        try {
            senha.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A senha nao esta em um formato valido");
            novosDados[2] = telaCampo.apresentar("Cadastro", "3 - Senha: ");
            continue;
        }

        try {
            telefone.setDado(novosDados[3]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Telefone nao esta em um formato valido");
            novosDados[3] = telaCampo.apresentar("Cadastro", "4 - Telefone: ");
            continue;
        }

        Desenvolvedor dev;
        dev.setMatricula(matricula);
        dev.setNome(nome);
        dev.setSenha(senha);
        dev.setTelefone(telefone);

        if (!cntrServicoDesenvolvedor->cadastrar(dev)) {
            telaMensagem.apresentar("Nao foi possivel cadastrar, tente novamente.");
        } else {
            telaMensagem.apresentar("Desenvolvedor Cadastrado com Sucesso.");
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
        "1 - Cadastrar Teste: ", 
        "2 - Consultar Teste: ",
        "3 - Voltar: ",
    });
    const vector<string> menuTeste({
        "1 - Informacoes do Teste: ", 
        "2 - Editar Dados do Teste: ",
        "3 - Casos de Teste: ",
        "4 - Descadastrar: ",
        "5 - Voltar: ",
    });

    Codigo* codigo = new Codigo();
    Teste* teste = new Teste();

    string code;

    while(true) {
        opcaoMenuPricipal = (
            telaMenu.apresentar(
                "Menu do Teste", 
                menuPricipal
            )
        ).c_str()[0];

        switch(opcaoMenuPricipal) {
            case '1':
                this->cadastrar(desenvolvedor->getMatricula());
                continue;
            case '2':
                while(true) {
                    code = telaCampo.apresentar(
                        "Consultar Teste",
                        "Informe o Codigo do Teste ou digite 0 para voltar: "
                    );

                    if(code.length() == 1 && code.c_str()[0] == '0') {
                        break;
                    }

                    try {
                        codigo->setDado(code);
                        teste->setCodigo(*codigo);
                        if(!cntrServicoTeste->consultar(teste, *desenvolvedor)) {
                            telaMensagem.apresentar("Codigo Nao Encontrado");
                            continue;
                        }
                    }
                    catch(const invalid_argument) {
                        telaMensagem.apresentar("Codigo Invalido");
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
                                continue;
                            case '2':
                                this->editar(teste);
                                continue;
                            case '3':
                                cntrApresentacaoCasoDeTeste->executar(teste);
                                continue;
                            case '4':
                                if (telaDescadastrar.apresentar()) {
                                    if (cntrServicoTeste->descadastrar(teste->getCodigo())) {
                                        telaMensagem.apresentar("Teste Descadastrado com Sucesso.");
                                        teste = new Teste();
                                        return;
                                    } else {
                                        telaMensagem.apresentar("Não foi possivel descadastrar, tente novamente.");
                                        continue;
                                    }
                                }
                                continue;
                            case '5':
                                return;
                            default:
                                telaMensagem.apresentar("Opcao Invalida");
                                continue;
                        }
                    }
                    continue;
                }
                continue;
            case '3':
                return;
            default:
                telaMensagem.apresentar("Opcao Invalida");
                continue;
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
        "1 - Codigo: ", 
        "2 - Nome: ",
        "3 - Classe: ",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Cadastrar Teste", campos, novosDados);

    while(true) {
        try {
            codigo.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("0 Codigo nao esta em um formato valido");
            novosDados[0] = telaCampo.apresentar("Cadastrar Teste", "1 - Codigo: ");
            continue;
        }

        try {
            nome.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Nome nao esta em um formato valido");
            novosDados[1] = telaCampo.apresentar("Cadastrar Teste", "2 - Nome: ");
            continue;
        }

        try {
            classe.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Classe nao esta em um formato valido");
            novosDados[2] = telaCampo.apresentar("Cadastrar Teste", "3 - Classe: ");
            continue;
        }

        Teste teste;
        teste.setCodigo(codigo);
        teste.setNome(nome);
        teste.setClasse(classe);

        if (!cntrServicoTeste->cadastrar(teste, matricula)) {
            telaMensagem.apresentar("Nao foi possivel cadastrar o teste, tente novamente.");
        } else {
            telaMensagem.apresentar("Teste Cadastrado com Sucesso.");
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
        "1 - Nome: ",
        "2 - Classe: ",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Editar Teste", campos, novosDados);

    while(true) {
        try {
            nome.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Nome nao esta em um formato valido");
            novosDados[0] = telaCampo.apresentar("Editar Teste", "1 - Nome: ");
            continue;
        }

        try {
            classe.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Classe nao esta em um formato valido");
            novosDados[1] = telaCampo.apresentar("Editar Teste", "2 - Classe: ");
            continue;
        }

        Teste editedTeste;
        editedTeste.setCodigo(teste->getCodigo());
        editedTeste.setNome(nome);
        editedTeste.setClasse(classe);

        if (cntrServicoTeste->editar(editedTeste)) {
            teste->setNome(nome);
            teste->setClasse(classe);
            telaMensagem.apresentar("Teste Editado com Sucesso.");
        } else {
            telaMensagem.apresentar("Nao foi possivel Editar o teste, tente novamente.");
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
        "1 - Cadastrar Caso de Teste: ", 
        "2 - Consultar Caso de Teste: ",
        "3 - Voltar: ",
    });
    const vector<string> menuTeste({
        "1 - Informacoes do Caso de Teste: ", 
        "2 - Editar Dados do Case de Teste: ",
        "3 - Descadastrar: ",
        "4 - Voltar: ",
    });
    
    Codigo* codigo = new Codigo();
    CasoDeTeste* casoDeTeste = new CasoDeTeste();

    string code;

    while(true) {
        opcaoMenuPricipal = (
            telaMenu.apresentar(
                "Menu do Teste", 
                menuPricipal
            )
        ).c_str()[0];

        switch(opcaoMenuPricipal) {
            case '1':
                this->cadastrar(teste->getCodigo());
                continue;
            case '2':
                while(true) {
                    code = telaCampo.apresentar(
                        "Consultar Caso de Teste",
                        "Informe o Codigo do Caso de Teste ou digite 0 para voltar: "
                    );

                    if(code.length() == 1 && code.c_str()[0] == '0') {
                        break;
                    }

                    try {
                        codigo->setDado(code);
                        casoDeTeste->setCodigo(*codigo);
                        if(!cntrServicoCasoDeTeste->consultar(casoDeTeste, *teste)) {
                            telaMensagem.apresentar("Codigo Nao Encontrado");
                            continue;
                        }
                    }
                    catch(const invalid_argument) {
                        telaMensagem.apresentar("Codigo Invalido");
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
                                continue;
                            case '2':
                                this->editar(casoDeTeste);
                                continue;
                            case '3':
                                if (telaDescadastrar.apresentar()) {
                                    if (cntrServicoCasoDeTeste->descadastrar(casoDeTeste->getCodigo())) {
                                        telaMensagem.apresentar("Caso de Teste Descadastrado com Sucesso.");
                                        casoDeTeste = new CasoDeTeste();
                                        return;
                                    } else {
                                        telaMensagem.apresentar("Não foi possivel descadastrar, tente novamente.");
                                        continue;
                                    }
                                }
                                continue;
                            case '4':
                                return;
                            default:
                                telaMensagem.apresentar("Opcao Invalida");
                                continue;
                        }
                    }
                }
                continue;
            case '3':
                return;
            default:
                telaMensagem.apresentar("Opcao Invalida");
                continue;
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
        "1 - Nome: ",
        "2 - Data: ",
        "3 - Acao: ",
        "4 - Resposta: ",
        "5 - Resultado: ",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Editar Caso de Teste", campos, novosDados);

    while(true) {
        try {
            nome.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Nome nao esta em um formato valido");
            novosDados[0] = telaCampo.apresentar("Editar Caso de Teste", "1 - Nome: ");
            continue;
        }

        try {
            data.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Data nao esta em um formato valido");
            novosDados[1] = telaCampo.apresentar("Editar Caso de Teste", "2 - Data: ");
            continue;
        }

        try {
            acao.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Acao nao esta em um formato valido");
            novosDados[2] = telaCampo.apresentar("Editar Caso de Teste", "3 - Acao: ");
            continue;
        }

        try {
            resposta.setDado(novosDados[3]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Resposta nao esta em um formato valido");
            novosDados[3] = telaCampo.apresentar("Editar Caso de Teste", "4 - Resposta: ");
            continue;
        }

        try {
            resultado.setDado(novosDados[4]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Resultado nao esta em um formato valido");
            novosDados[4] = telaCampo.apresentar("Editar Caso de Teste", "5 - Resultado: ");
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
            casoDeTeste->setNome(nome);
            casoDeTeste->setData(data);
            casoDeTeste->setAcao(acao);
            casoDeTeste->setResposta(resposta);
            casoDeTeste->setResultado(resultado);
            telaMensagem.apresentar("Caso de Teste Editado com Sucesso.");
        } else {
            telaMensagem.apresentar("Nao foi possivel Editar o teste, tente novamente.");
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
        "1 - Codigo: ",
        "2 - Nome: ",
        "3 - Data: ",
        "4 - Acao: ",
        "5 - Resposta: ",
        "6 - Resultado: ",
    });

    string novosDados[campos.size()];

    telaForm.apresentar("Cadastrar Caso de Teste", campos, novosDados);

    while(true) {

        try {
            codigo.setDado(novosDados[0]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("0 Codigo nao esta em um formato valido");
            novosDados[0] = telaCampo.apresentar("Cadastrar Caso de Teste", "1 - Codigo: ");
            continue;
        }

        try {
            nome.setDado(novosDados[1]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Nome nao esta em um formato valido");
            novosDados[1] = telaCampo.apresentar("Cadastrar Caso de Teste", "2 - Nome: ");
            continue;
        }

        try {
            data.setDado(novosDados[2]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Data nao esta em um formato valido");
            novosDados[2] = telaCampo.apresentar("Cadastrar Caso de Teste", "3 - Data: ");
            continue;
        }

        try {
            acao.setDado(novosDados[3]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Acao nao esta em um formato valido");
            novosDados[3] = telaCampo.apresentar("Cadastrar Caso de Teste", "4 - Acao: ");
            continue;
        }

        try {
            resposta.setDado(novosDados[4]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("A Resposta nao esta em um formato valido");
            novosDados[4] = telaCampo.apresentar("Cadastrar Caso de Teste", "5 - Resposta: ");
            continue;
        }

        try {
            resultado.setDado(novosDados[5]);
        } catch (const invalid_argument) {
            telaMensagem.apresentar("O Resultado nao esta em um formato valido");
            novosDados[5] = telaCampo.apresentar("Cadastrar Caso de Teste", "6 - Resultado: ");
            continue;
        }

        CasoDeTeste casoDeTeste;
        casoDeTeste.setCodigo(codigo);
        casoDeTeste.setNome(nome);
        casoDeTeste.setData(data);
        casoDeTeste.setAcao(acao);
        casoDeTeste.setResposta(resposta);
        casoDeTeste.setResultado(resultado);

        if (!cntrServicoCasoDeTeste->checkQuantidade(codigoTeste)) {
            telaMensagem.apresentar("Voce nao pode cadastrar mais de 10 casos de teste");
            return;
        }

        if (!cntrServicoCasoDeTeste->cadastrar(casoDeTeste, codigoTeste)) {
            telaMensagem.apresentar("Nao foi possivel cadastrar o Caso de Teste, tente novamente.");
        } else {
            telaMensagem.apresentar("Caso de Teste Cadastrado com Sucesso.");
        };
        return;
    }
}

bool CntrServicoAutenticacao::autenticar(Desenvolvedor* desenvolvedor) {
    ComandoConsultarDesenvolvedor comandoConsultar(*desenvolvedor);
    TelaMensagem telaMensagem;
    Desenvolvedor desenvolvedorVazio;

    try {
        comandoConsultar.executar();
    } catch (EErroPersistencia &e) {
        return false;
    }

    try {
        *desenvolvedor = comandoConsultar.getResultado();
    } catch (EErroPersistencia &e) {
        return false;
    } catch (invalid_argument &e) {
        return false;
    }

    return true;
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
    ComandoConsultarDesenvolvedor cmdConsultar(*desenvolvedor);

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
    
    desenvolvedor->setMatricula(visualizar.getMatricula());
    desenvolvedor->setNome(visualizar.getNome());
    desenvolvedor->setSenha(visualizar.getSenha());
    desenvolvedor->setTelefone(visualizar.getTelefone());

    return true;
};


bool CntrServicoTeste::consultar(Teste* teste, Desenvolvedor desenvolvedor){
    ComandoConsultarTeste cmdConsultar(teste->getCodigo(), desenvolvedor);
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

    teste->setCodigo(testeConsultado.getCodigo());
    teste->setNome(testeConsultado.getNome());
    teste->setClasse(testeConsultado.getClasse());

    return true;

};

bool CntrServicoTeste::cadastrar(Teste teste, Matricula matricula) {
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

bool CntrServicoCasoDeTeste::consultar(CasoDeTeste* casoDeTeste, Teste teste) {
    ComandoConsultarCasoDeTeste cmdConsultar(casoDeTeste->getCodigo(), teste);
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
    
    casoDeTeste->setCodigo(casoTesteConsultado.getCodigo());
    casoDeTeste->setNome(casoTesteConsultado.getNome());
    casoDeTeste->setData(casoTesteConsultado.getData());
    casoDeTeste->setAcao(casoTesteConsultado.getAcao());
    casoDeTeste->setResposta(casoTesteConsultado.getResposta());
    casoDeTeste->setResultado(casoTesteConsultado.getResultado());

    return true;
};

bool CntrServicoCasoDeTeste::checkQuantidade(Codigo codigo) {
    ComandoContarCasosDeTeste comandoContarCasosDeTeste(codigo);

    try {
        comandoContarCasosDeTeste.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    int quantidade;

    try {
        quantidade = comandoContarCasosDeTeste.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    } catch (invalid_argument &e) {
        return false;
    }

    if (quantidade >= 10) {
        return false;
    }

    return true;
}

bool CntrServicoCasoDeTeste::cadastrar(CasoDeTeste casodeteste, Codigo codigo) {
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