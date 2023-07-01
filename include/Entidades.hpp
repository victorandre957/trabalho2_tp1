#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

#include "Dominios.hpp"

using namespace std;

///@brief Trata-se de uma entidade que representa um usuário responsável pela criação de testes no sistama.
//por: Victor André 211026664 (Codificação) e Luan Guedes (Documentação)
class Desenvolvedor {
    private:
        Matricula matricula;
        Texto nome;
        Senha senha;
        Telefone telefone;

    public:
        ///@brief Retorna o número da matrícula do Desenvolvedor.
        ///@return Matrícula matrícula.
        Matricula getMatricula() const;

        ///@brief Armazena a matrícula do Desenvolvedor caso o parâmetro esteja corretamente passado.
        ///@param - Matricula matricula.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setMatricula(const Matricula &);
        
        /// @brief Retorna o nome do Desenvolvedor.
        ///@return Texto nome. 
        Texto getNome() const;

        ///@brief Armazena o nome do Desenvolvedor caso o parâmetro esteja corretamente passado.
        ///@param - Texto nome.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setNome(const Texto &);

        ///@brief Retorna a senha do Desenvolvedor.
        ///@return Senha senha.
        Senha getSenha() const;

        ///@brief Armazena a senha do Desenvolvedor caso o parâmetro esteja corretamente passado.
        ///@param - Senha senha.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setSenha(const Senha &);

        /// @brief Retorna o telefone do Desenvolvedor.
        /// @return Telefone telefone.
        Telefone getTelefone() const;

        ///@brief Armazena o telefone do Desenvolvedor caso o parâmetro esteja corretamente passado.
        ///@param - Telefone telefone.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setTelefone(const Telefone &);
};

inline void Desenvolvedor::setMatricula(const Matricula &matricula) {
    this->matricula = matricula;
}

inline Matricula Desenvolvedor::getMatricula() const {
    return matricula;
}

inline void Desenvolvedor::setNome(const Texto &nome) {
    this->nome = nome;
}

inline Texto Desenvolvedor::getNome() const {
    return nome;
}

inline void Desenvolvedor::setSenha(const Senha &senha) {
    this->senha = senha;
}

inline Senha Desenvolvedor::getSenha() const {
    return senha;
}

inline void Desenvolvedor::setTelefone(const Telefone &telefone) {
    this->telefone = telefone;
}

inline Telefone Desenvolvedor::getTelefone() const {
    return telefone;
}

/// @brief Trata-se de uma entidade que representa um tipo de teste criado por um desenvolvedor.
//por: Victor André 211026664 (Codificação) e Luan Guedes (Documentação)
class Teste {
    private:
        Codigo codigo;
        Texto nome;
        Classe classe;

    public:
        /// @brief Retorna o código do Teste.
        /// @return Codigo codigo.
        Codigo getCodigo() const;

        /// @brief Armazena o código caso o parâmetro esteja corretamente passado.
        /// @param - Codigo codigo.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setCodigo(const Codigo &);

        /// @brief Retorna o nome do Teste.
        /// @return Texto nome.
        Texto getNome() const;

        /// @brief Armazena o nome do Teste caso o parâmetro esteja corretamente passado.
        /// @param - Texto nome.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setNome(const Texto &);

        /// @brief Retorna a classe do Teste.
        /// @return Classe classe.
        Classe getClasse() const;

        // @brief Armazena a classe do Teste caso o parâmetro esteja corretamente passado.
        /// @param - Classe classe.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setClasse(const Classe &);
};

inline void Teste::setCodigo(const Codigo &codigo) {
    this->codigo = codigo;
}

inline Codigo Teste::getCodigo() const {
    return codigo;
}

inline void Teste::setNome(const Texto &nome) {
    this->nome = nome;
}

inline Texto Teste::getNome() const {
    return nome;
}

inline void Teste::setClasse(const Classe &classe) {
    this->classe = classe;
}

inline Classe Teste::getClasse() const {
    return classe;
}

/// @brief Trata-se de uma entidade que representa uma condição particular a ser testada.
//por: Victor André 211026664 (Codificação) e Luan Guedes (Documentação)
class CasoDeTeste {
    private:
        Codigo codigo;
        Texto nome;
        Data data;
        Texto acao;
        Texto resposta;
        Resultado resultado;

    public:

        /// @brief Retorna o codigo do CasoDeTeste.
        /// @return Codigo codigo.
        Codigo getCodigo() const;

        /// @brief Armazena o codigo do CasoDeTeste caso o parâmetro esteja corretamente passado.
        /// @param - Codigo codigo.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setCodigo(const Codigo &);

        /// @brief Retorna o nome do CasoDeTeste.
        /// @return Texto nome.
        Texto getNome() const;

        /// @brief Armazena o nome do CasoDeTeste caso o parâmetro esteja corretamente passado.
        /// @param - Texto nome.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setNome(const Texto &);

        /// @brief Retorna a data do CasoDeTeste.
        /// @return Data data.
        Data getData() const;

        /// @brief Armazena a data do CasoDeTeste caso o parâmetro esteja corretamente passado.
        /// @param - Data data.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setData(const Data &);

        /// @brief Retorna a acao do CasoDeTeste.
        /// @return Texto acao.
        Texto getAcao() const;

        /// @brief Armazena a acao do CasoDeTeste caso o parâmetro esteja corretamente passado.
        /// @param - Texto acao.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setAcao(const Texto &);

        /// @brief Retorna a resposta do CasoDeTeste.
        /// @return Texto resposta.
        Texto getResposta() const;

        /// @brief Armazena a resposta do CasoDeTeste caso o parâmetro esteja corretamente passado.
        /// @param - Texto resposta.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setResposta(const Texto &);

        /// @brief Retorna o resultado do CasoDeTeste.
        /// @return Resultado resultado.
        Resultado getResultado() const;

        /// @brief Armazena o resultado do CasoDeTeste caso o parâmetro esteja corretamente passado.
        /// @param - Resultado resultado.
        ///@throw - invalid_argument: caso o argumento passado nao esteja no padrão definido.
        void setResultado(const Resultado &);
};

inline void CasoDeTeste::setCodigo(const Codigo &codigo) {
    this->codigo = codigo;
}

inline Codigo CasoDeTeste::getCodigo() const {
    return codigo;
}

inline void CasoDeTeste::setNome(const Texto &nome) {
    this->nome = nome;
}

inline Texto CasoDeTeste::getNome() const {
    return nome;
}

inline void CasoDeTeste::setData(const Data &data) {
    this->data = data;
}

inline Data CasoDeTeste::getData() const {
    return data;
}

inline void CasoDeTeste::setAcao(const Texto &acao) {
    this->acao = acao;
}

inline Texto CasoDeTeste::getAcao() const {
    return acao;
}

inline void CasoDeTeste::setResposta(const Texto &resposta) {
    this->resposta = resposta;
}

inline Texto CasoDeTeste::getResposta() const {
    return resposta;
}

inline void CasoDeTeste::setResultado(const Resultado &resultado) {
    this->resultado = resultado;
}

inline Resultado CasoDeTeste::getResultado() const {
    return resultado;
}

#endif // ENTIDADES_HPP_INCLUDED