#ifndef COMANDOSSQL_HPP
#define COMANDOSSQL_HPP

#include <list>
#include <string>
#include <iostream>

#include "sqlite3.h"
#include "Entidades.hpp"
#include "Dominios.hpp"

using namespace std;

///@brief Classe de Erro para todos os comandos SQL;
class EErroPersistencia {
    private:
        ///@brief Atributo string que repesenta a mensagem do erro ocorrido.
        string mensagem;

    public:
        ///@brief A prórpia função do erro de percistencia que define a mensagem de erro.
        ///@param -parâmetro string: mensagem de erro
        EErroPersistencia(string);

        ///@brief Retorna qual é o erro ocorrido.
        ///@return mensagem de erro. (string) 
        string what();
};

inline string EErroPersistencia::what() {
    return mensagem;
}

inline EErroPersistencia::EErroPersistencia(string mensagem){
    this->mensagem = mensagem;
}

/// @brief Classe de Resultados para todos os comandos SQL
class ElementoResultado {
    private:
        ///@brief Atributo string que armazena o nome da coluna do banco de dados.
        string nomeColuna;

        ///@brief Atributo string que armazena o valor do banco de dados.
        string valorColuna;

    public:
         ///@brief Define o nome da coluna do banco daquele dado.
         ///@param referência a uma string constante
        void setNomeColuna(const string&);

         ///@brief Retorna o nome da coluna do banco daquele dado.
         ///@return Nome da coluna (string). 
        string getNomeColuna() const;

        ///@brief Define o valor dado naquela linha.
        ///@param referência a uma string constante
        void setValorColuna(const string&);

        ///@brief Retorna o valor dado naquela linha.
        ///@return dado (string).
        string getValorColuna() const;
};

inline string ElementoResultado::getNomeColuna() const {
    return nomeColuna;
}

inline string ElementoResultado::getValorColuna() const {
    return valorColuna;
}

///@brief Classe base dos comandos SQl para todos os outros comandos a seguir.
class ComandoSQL {
    private:

        ///@brief  Um Atributo char armazenando o nome do Banco de Dados em uso.
        const char *nomeBancoDados;

        ///@brief Atributo da biblioteca sqlite3.
        sqlite3 *bd;

        ///@brief Atributo contendo a mensagem do erro (se existir).
        char *mensagem;

        ///@brief Atributo contendo o comando do sqlite.
        int rc;

        /// @brief Método usado para conectar com o banco de dados.
        void conectar();

        /// @brief Método usado para desconectar do banco de dados.
        void desconectar();
      
        static int callback(void *, int, char **, char **);

    protected:
        ///@brief Lista de Resultados da consulta.
        static list<ElementoResultado> listaResultado;

        ///@brief Atributo string com o comando SQL a ser execudado.
        string comandoSQL;

    public:
        ///@brief Construtor do comando SQl, define o comando e nome do banco.
        ComandoSQL() {
            nomeBancoDados = "Banco.db";
        }

        ///@brief Executa o comando SQL.
        void executar();
};

///@brief Comando SQL utilizado para cadastrar um desenvolvedor no banco.
class ComandoCadastrarDesenvolvedor:public ComandoSQL {
    public:
        ///@brief Construtor da classe para cadastrar desenvolvedor.
        ///@param Desenvolvedor a ser cadastrado
        ComandoCadastrarDesenvolvedor(Desenvolvedor);
};

///@brief Comando SQL utilizado para consultar um desenvolvedor no banco.
class ComandoConsultarDesenvolvedor:public ComandoSQL {
    public:
        ///@brief Construtor da classe para consultar um desenvolvedor pela matricula.
        ///@param Matricula: matricula do desenvolvedor que se quer consultar
        ComandoConsultarDesenvolvedor(Matricula);

        ///@brief Retorna um objeto desenvolvedor com os dados obtidos na consulta.
        ///@return Retorna o desenvolvedor encontrado (desenvolvedor)
        Desenvolvedor getResultado();
};

///@brief Comando SQL utilizado para editar um desenvolvedor no banco.
class ComandoEditarDesenvolvedor:public ComandoSQL {
    public:
        ///@brief Construtor da classe para editar um desenvolvedor.
        ///@param Desenvolvedor: um objeto com as informações do Desenvolvedor a serem atualizadas.
        ComandoEditarDesenvolvedor(Desenvolvedor);
};

///@brief Comando SQL utilizado para descadastrar um desenvolvedor no banco.
class ComandoDescadastrarDesenvolvedor:public ComandoSQL {
    public:
        ///@brief Construtor da classe para descadastrar um desenvolvedor pela matricula.
        ///@param Matricula: matricula do desenvolvedor que se quer descadastrar.
        ComandoDescadastrarDesenvolvedor(Matricula);
};

#endif  //  COMANDOSSQL_HPP