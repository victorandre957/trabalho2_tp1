#include "ComandosSQL.hpp"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

list<ElementoResultado> ComandoSQL::listaResultado;

void ElementoResultado::setNomeColuna(const string& nomeColuna) {
    this->nomeColuna = nomeColuna;
}

void ElementoResultado::setValorColuna(const string& valorColuna){
    this->valorColuna = valorColuna;
}

void ComandoSQL::conectar() {
    rc = sqlite3_open(nomeBancoDados, &bd);
    if( rc != SQLITE_OK )
        throw EErroPersistencia("Erro na conexao ao banco de dados");
}

void ComandoSQL::desconectar() {
    rc =  sqlite3_close(bd);
    if( rc != SQLITE_OK )
        throw EErroPersistencia("Erro na desconexao ao banco de dados");
}

void ComandoSQL::executar() {
    conectar();
    rc = sqlite3_exec(bd, comandoSQL.c_str(), callback, 0, &mensagem);

    if(rc != SQLITE_OK){
        std::cout << mensagem << std::endl;
        sqlite3_free(mensagem);
        desconectar();
        throw EErroPersistencia("Erro na execucao do comando SQL");
    }

    desconectar();
}

int ComandoSQL::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
    NotUsed=0;
    ElementoResultado elemento;
    int i;

    for(i=0; i<argc; i++){
        elemento.setNomeColuna(nomeColuna[i]);
        elemento.setValorColuna(valorColuna[i] ? valorColuna[i]: "NULL");
        listaResultado.push_front(elemento);
    }

    return 0;
}

ComandoCadastrarDesenvolvedor::ComandoCadastrarDesenvolvedor(Desenvolvedor desenvolvedor) {
    comandoSQL = "BEGIN; INSERT INTO Desenvolvedores (Matricula, Nome, Senha, Telefone) VALUES(";
    comandoSQL += "'" + (desenvolvedor.getMatricula().getDado()) + "', ";
    comandoSQL += "'" + (desenvolvedor.getNome().getDado()) + "', ";
    comandoSQL += "'" + (desenvolvedor.getSenha().getDado()) + "', ";
    comandoSQL += "'" + (desenvolvedor.getTelefone().getDado()) + "'); COMMIT";
}

ComandoConsultarDesenvolvedor::ComandoConsultarDesenvolvedor(Desenvolvedor desenvolvedor) {
    comandoSQL = "SELECT * FROM Desenvolvedores WHERE Matricula = '";
    comandoSQL += desenvolvedor.getMatricula().getDado() + "' ";
    comandoSQL += "AND Senha = '" + desenvolvedor.getSenha().getDado() + "'";
}

Desenvolvedor ComandoConsultarDesenvolvedor::getResultado() {
    ElementoResultado resultado;
    Desenvolvedor desenvolvedor;

    if(listaResultado.size() < 4) {
        throw EErroPersistencia("Lista de resultados vazia.");
    }

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Matricula matricula;
    matricula.setDado(resultado.getValorColuna());
    desenvolvedor.setMatricula(matricula);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Texto nome;
    nome.setDado(resultado.getValorColuna());
    desenvolvedor.setNome(nome);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Senha senha;
    senha.setDado(resultado.getValorColuna());
    desenvolvedor.setSenha(senha);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Telefone telefone;
    telefone.setDado(resultado.getValorColuna());
    desenvolvedor.setTelefone(telefone);

    listaResultado.clear();

    return desenvolvedor;
}

ComandoEditarDesenvolvedor::ComandoEditarDesenvolvedor(Desenvolvedor desenvolvedor) {
    comandoSQL = "UPDATE Desenvolvedores ";
    comandoSQL += "SET Nome = '" + desenvolvedor.getNome().getDado();
    comandoSQL += "', Senha = '" + desenvolvedor.getSenha().getDado();
    comandoSQL += "', Telefone = '" + desenvolvedor.getTelefone().getDado();
    comandoSQL += "' WHERE Matricula = " + desenvolvedor.getMatricula().getDado();
}

ComandoDescadastrarDesenvolvedor::ComandoDescadastrarDesenvolvedor(Matricula matricula) {
    comandoSQL = "DELETE FROM CasosDeTeste WHERE Teste IN (SELECT Teste FROM Testes WHERE Desenvolvedor = ";
    comandoSQL += matricula.getDado() + ");";

    comandoSQL = "DELETE FROM Testes WHERE Desenvolvedor = ";
    comandoSQL += matricula.getDado() + ";";

    comandoSQL += "DELETE FROM Desenvolvedores WHERE Matricula = ";
    comandoSQL += matricula.getDado() + ";";
}


ComandoCadastrarTeste::ComandoCadastrarTeste(Teste teste, Matricula matricula) {
    comandoSQL = "BEGIN; INSERT INTO Testes (Codigo, Nome, Classe, Desenvolvedor) VALUES(";
    comandoSQL += "'" + (teste.getCodigo().getDado()) + "', ";
    comandoSQL += "'" + (teste.getNome().getDado()) + "', ";
    comandoSQL += "'" + (teste.getClasse().getDado()) + "', ";
    comandoSQL += "'" + (matricula.getDado()) + "'); COMMIT";
} 

ComandoConsultarTeste::ComandoConsultarTeste(Codigo codigo, Desenvolvedor desenvolvedor) {
    comandoSQL = "SELECT * FROM Testes WHERE Codigo = '";
    comandoSQL += codigo.getDado() + "' ";
    comandoSQL += "AND Desenvolvedor = '" + desenvolvedor.getMatricula().getDado() + "';";
}

Teste ComandoConsultarTeste::getResultado() {
    ElementoResultado resultado;
    Teste teste;

    if(listaResultado.size() < 4) {
        throw EErroPersistencia("Lista de resultados vazia.");
    }

    resultado = listaResultado.back();
    listaResultado.pop_back();

    Codigo codigo;
    codigo.setDado(resultado.getValorColuna());
    teste.setCodigo(codigo);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Texto nome;
    nome.setDado(resultado.getValorColuna());
    teste.setNome(nome);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Classe classe;
    classe.setDado(resultado.getValorColuna());
    teste.setClasse(classe);

    listaResultado.clear();

    return teste;
}

ComandoEditarTeste::ComandoEditarTeste(Teste teste) {
    comandoSQL = "UPDATE Testes ";
    comandoSQL += "SET Nome = '" + teste.getNome().getDado();
    comandoSQL += "', Classe = '" + teste.getClasse().getDado();
    comandoSQL += "' WHERE Codigo = '" + teste.getCodigo().getDado() + "';";
}

ComandoDescadastrarTeste::ComandoDescadastrarTeste(Codigo codigo) {
    comandoSQL = "DELETE FROM CasosDeTeste WHERE Teste = '";
    comandoSQL += codigo.getDado() + "';";

    comandoSQL += "DELETE FROM Testes WHERE Codigo = '";
    comandoSQL += codigo.getDado() + "';";
}

ComandoContarCasosDeTeste::ComandoContarCasosDeTeste(Codigo codigo) {
    comandoSQL = "SELECT Count(*) FROM CasosDeTeste WHERE Teste = '";
    comandoSQL += codigo.getDado() + "' ";
}

int ComandoContarCasosDeTeste::getResultado() {
    ElementoResultado resultado;
    int quantidade;

    if(listaResultado.size() < 1) {
        throw EErroPersistencia("Lista de resultados vazia.");
    }

    resultado = listaResultado.back();
    listaResultado.pop_back();
    quantidade = stoi(resultado.getValorColuna());
    listaResultado.clear();

    return quantidade;
}


ComandoCadastrarCasoDeTeste::ComandoCadastrarCasoDeTeste(CasoDeTeste casoDeTeste, Codigo codigo) {
    comandoSQL = "BEGIN; INSERT INTO CasosDeTeste (Codigo, Nome, Data, Acao, Resposta, Resultado, Teste) VALUES(";
    comandoSQL += "'" + (casoDeTeste.getCodigo().getDado()) + "', ";
    comandoSQL += "'" + (casoDeTeste.getNome().getDado()) + "', ";
    comandoSQL += "'" + (casoDeTeste.getData().getDado()) + "', ";
    comandoSQL += "'" + (casoDeTeste.getAcao().getDado()) + "', ";
    comandoSQL += "'" + (casoDeTeste.getResposta().getDado()) + "', ";
    comandoSQL += "'" + (casoDeTeste.getResultado().getDado()) + "', ";
    comandoSQL += "'" + (codigo.getDado()) + "'); COMMIT";
}

ComandoConsultarCasoDeTeste::ComandoConsultarCasoDeTeste(Codigo codigo, Teste teste) {
    comandoSQL = "SELECT * FROM CasosDeTeste WHERE Codigo = '";
    comandoSQL += codigo.getDado() + "' ";
    comandoSQL += "AND Teste = '" + teste.getCodigo().getDado() + "'";
}

CasoDeTeste ComandoConsultarCasoDeTeste::getResultado() {
    ElementoResultado resultado;
    CasoDeTeste casoDeTeste;

    if(listaResultado.size() < 7) {
        throw EErroPersistencia("Lista de resultados vazia.");
    }

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Codigo codigo;
    codigo.setDado(resultado.getValorColuna());
    casoDeTeste.setCodigo(codigo);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Texto nome;
    nome.setDado(resultado.getValorColuna());
    casoDeTeste.setNome(nome);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Data data;
    data.setDado(resultado.getValorColuna());
    casoDeTeste.setData(data);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Texto acao;
    acao.setDado(resultado.getValorColuna());
    casoDeTeste.setAcao(acao);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Texto resposta;
    resposta.setDado(resultado.getValorColuna());
    casoDeTeste.setResposta(resposta);

    resultado = listaResultado.back();
    listaResultado.pop_back();
    Resultado resultadoDoCaso;
    resultadoDoCaso.setDado(resultado.getValorColuna());
    casoDeTeste.setResultado(resultadoDoCaso);

    listaResultado.clear();

    return casoDeTeste;
}


ComandoEditarCasoDeTeste::ComandoEditarCasoDeTeste(CasoDeTeste casoDeTeste) {
    comandoSQL = "UPDATE CasosDeTeste ";
    comandoSQL += "SET Nome = '" + casoDeTeste.getNome().getDado();
    comandoSQL += "', Data = '" + casoDeTeste.getData().getDado();
    comandoSQL += "', Acao = '" + casoDeTeste.getAcao().getDado();
    comandoSQL += "', Resposta = '" + casoDeTeste.getResposta().getDado();
    comandoSQL += "', Resultado = '" + casoDeTeste.getResultado().getDado();
    comandoSQL += "' WHERE Codigo = '" + casoDeTeste.getCodigo().getDado() + "'";
}

ComandoDescadastrarCasoDeTeste::ComandoDescadastrarCasoDeTeste(Codigo codigo) {
    comandoSQL = "DELETE FROM CasosDeTeste WHERE Codigo = '";
    comandoSQL += codigo.getDado() + "';";
}