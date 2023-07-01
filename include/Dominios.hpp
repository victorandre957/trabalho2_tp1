#ifndef DOMINIOS_HPP
#define DOMINIOS_HPP

#include <string>

using namespace std;

/**
 * @brief Classe abstrata, que tem como uníco atributo uma string.
 * @details Será utilizada por outras classes de domínios.
 * por: Luan Guedes 211026628
 */
class Dominio {
    protected: 
        /**
         * @brief Atributo principal da classe.
         * @details Segue o padrão de formatação da string.
         */
        string dado;
        virtual void validar(string dado) = 0;

    public:
        /**
         * @brief Retorna a string formatada que esta armazenada em "dado".
         * @return string dado
         */
        string getDado() const;
        /**
         * @brief Armazena o dado da string passada no atributo dado se a 
         *  string estiver corretamente formatada de acordo com as regras da classe.
         * 
         * @return  -string dado: string que será armazenada no atributo. 
         *  Esse dado deverá seguir as regras de formatação da classe.
         * 
         * @throw -invalid_argument : se o dado passado nao estiver de 
         * acordo com as regras de formatação.
         */
        void setDado(string dado);
};

inline string Dominio::getDado() const {
    return dado;
}

/**
 *  @brief Representa as diferentes classes que um teste pode ser.
 *  @details O valor armazenado deve ser de um dos tipos abaixo:
 *  <ul>
 *     <li>  UNIDADE    </li>
 *     <li>  INTEGRACAO </li>
 *     <li>  FUMACA     </li>
 *     <li>  SISTEMA    </li>
 *     <li>  REGRESSAO  </li>
 *     <li>  ACEITACAO  </li>
 *  </ul>
 * por: Victor André 211026664
 */
class Classe: public Dominio {
    private:
        void validar(string);
};

/**
 * @brief Conjunto de 6 caracteres representam uma informação.
 * @details o formato do código deverá ser "LLLDDD", sendo:
 *     <ul>
 *          <li> "L" uma letra maiuscula ou minuscula </li>
 *          <li> "D" uma digito entre 0 e 9           </li>
 *     </ul>
 * por: Luan Guedes 211026628
 */
class Codigo: public Dominio {

    private:
        void validar(string);
};

/**
 * @brief Forma de representação da data atual, a partir do ano 2000.
 * @details Regras de formatação:
 * <ul>
 *      <li> DD/MM/AA, em que D, M e A representam respectivamente Dia, Mês e Ano </li>
 *      <li> Dias: 1 a 31                                                         </li>
 *      <li> Meses: JAN, FEV, MAR ...                                             </li>
 *      <li> Anos: 2000 à 2999                                                    </li>
 *      <li> Há verificação de ano bissexto                                       </li>
 * </ul>
 * por: Luan Guedes 211026628
 */
class Data: public Dominio {

    private:
        void validar(string);

};
/**
 *  @brief Conjunto de numeros que possibilita registrar um Desenvolvedor no sistema.
 *  @details Formato: "DDDDDDX" (7 numeros), onde:
 *  <ul>
 *     <li> D é um numero de 0 à 9    </li>
 *     <li> X é um dígito verificador </li>
 *  </ul>
 * por: Luan Guedes 211026628
*/

class Matricula: public Dominio{

    private:
        void validar(string);
};

/**
 * @brief Determina o Resultado do teste.
 * @details o resultado pode ser "APROVADO" ou "REPROVADO"
 * por: Victor André 211026664
 */
class Resultado: public Dominio {

    private:
        void validar(string);
};

/**
 * @brief Sequência de  caracteres alfanuméricos que permite o acesso aos dados.
 * @details Formato: "XXXXXX" (6 caracteres) onde X é uma letra, um número ou um símbulo
 *  e todos os caracteres são diferentes.
 * por: Victor André 211026664
 */

class Senha: public Dominio {

    private:
        void validar(string);
};

/**
 * @brief Sequência de números referente ao telefone do Desenvolvedor.
 * @details Formato: são numeros de 0 à 9 com 7 á 15 digitos.
 * por: Victor André 211026664
 */
class Telefone: public Dominio {

    private:
        void validar(string);
};

/**
 * @brief Representa uma sequência de caracteres.
 * @details O valor armazenado segue as seguintes regras:
 * <ul>
 *     <li> Deve ter no mínimo 10 caracteres e no máximo 20 </li>
 *     <li> 
 *          Cada caractere deve ser letra (de A-Z ou a-z), dígito (0-9) 
 *          ou sinal de pontuação (. , ; ? ! : - ) ou simbulos (@,#,$,%,&) 
 *     </li>
 *     <li> Nao podem haver espaços em branco em sequência. </li>
 *     <li> Nao há sinal de acentuação</li>
 * </ul>
 * por: Victor André 211026664
 */
class Texto: public Dominio {

    private:
        void validar(string);
};

#endif // DOMINIOS_HPP