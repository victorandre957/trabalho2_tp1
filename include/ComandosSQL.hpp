#ifndef COMANDOSSQL_HPP
#define COMANDOSSQL_HPP

#include <list>
#include <string>
#include <iostream>

#include "sqlite3.hpp"
#include "Entidades.hpp"

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
        ///@param Desenvolvedor: objeto do desenvolvedor que se quer consultar
        ComandoConsultarDesenvolvedor(Desenvolvedor);

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




///@brief Comando SQL utilizado para cadastrar um teste no banco.
class ComandoCadastrarTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para cadastrar teste.
        ///@param Teste a ser cadastrado
        ///@param Matricula do Desenvolvedor que está criando o teste
        ComandoCadastrarTeste(Teste, Matricula);
};

///@brief Comando SQL utilizado para consultar um teste no banco.
class ComandoConsultarTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para consultar um teste pelo codigo.
        ///@param Codigo: codigo do teste que se quer consultar
        ///@param Desenvolvedor: objeto do desenvolvedor dono do teste
        ComandoConsultarTeste(Codigo, Desenvolvedor);

        ///@brief Retorna um objeto teste com os dados obtidos na consulta.
        ///@return Retorna o teste encontrado (teste)
        Teste getResultado();
};

///@brief Comando SQL utilizado para editar um teste no banco.
class ComandoEditarTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para editar um teste.
        ///@param Teste: um objeto com as informações do teste a serem atualizadas.
        ComandoEditarTeste(Teste);
};

///@brief Comando SQL utilizado para descadastrar um teste no banco.
class ComandoDescadastrarTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para descadastrar um teste pela codigo.
        ///@param Codigo: codigo do teste que se quer descadastrar.
        ComandoDescadastrarTeste(Codigo);
};

///@brief Comando SQL utilizado para cadastrar um caso de teste no banco.
class ComandoContarCasosDeTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para cadastrar caso de teste.
        ///@param Codigo do teste do qual esse caso de teste pertence
        ComandoContarCasosDeTeste(Codigo);

        ///@brief Retorna um objeto caso de teste com os dados obtidos na consulta.
        ///@return Retorna o caso de teste encontrado (caso de teste)
        int getResultado();
};

///@brief Comando SQL utilizado para cadastrar um caso de teste no banco.
class ComandoCadastrarCasoDeTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para cadastrar caso de teste.
        ///@param CasoDeTeste a ser cadastrado
        ///@param Codigo do teste do qual esse caso de teste pertence
        ComandoCadastrarCasoDeTeste(CasoDeTeste, Codigo);
};

///@brief Comando SQL utilizado para consultar um caso de teste no banco.
class ComandoConsultarCasoDeTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para consultar um caso de teste pelo codigo.
        ///@param Codigo: codigo do caso de teste que se quer consultar
        ///@param Teste: objeto do teste que se quer dono do caso de teste
        ComandoConsultarCasoDeTeste(Codigo, Teste);

        ///@brief Retorna um objeto caso de teste com os dados obtidos na consulta.
        ///@return Retorna o caso de teste encontrado (caso de teste)
        CasoDeTeste getResultado();
};

///@brief Comando SQL utilizado para editar um caso de teste no banco.
class ComandoEditarCasoDeTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para editar um caso de teste.
        ///@param CasoDeTeste: um objeto com as informações do caso de teste a serem atualizadas.
        ComandoEditarCasoDeTeste(CasoDeTeste);
};

///@brief Comando SQL utilizado para descadastrar um caso de teste no banco.
class ComandoDescadastrarCasoDeTeste:public ComandoSQL {
    public:
        ///@brief Construtor da classe para descadastrar um caso de teste pela codigo.
        ///@param Codigo: codigo do caso de teste que se quer descadastrar.
        ComandoDescadastrarCasoDeTeste(Codigo);
};

#endif  //  COMANDOSSQL_HPP