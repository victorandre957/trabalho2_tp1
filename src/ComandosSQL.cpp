#include "ComandosSQL.hpp"

#include <string>

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

ComandoConsultarDesenvolvedor::ComandoConsultarDesenvolvedor(Matricula matricula) {
    comandoSQL = "SELECT * FROM Desenvolvedores WHERE Matricula = ";
    comandoSQL += matricula.getDado();
}

Desenvolvedor ComandoConsultarDesenvolvedor::getResultado() {
        ElementoResultado resultado;
        Desenvolvedor desenvolvedor;

        if(listaResultado.size() < 4)
            throw EErroPersistencia("Lista de resultados vazia.");

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
        comandoSQL = "DELETE FROM Desenvolvedores WHERE Matricula = ";
        comandoSQL += matricula.getDado() + ";";
}