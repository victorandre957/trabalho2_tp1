#ifndef TELAS_HPP_INCLUDED
#define TELAS_HPP_INCLUDED

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include "Entidades.hpp"
#include "Dominios.hpp"

#ifdef WIN32
    #include "curses.hpp"
#else
    #include <ncurses.h>
#endif  // WIN32


using namespace std;
//por: Victor André 211026664
class Tela {
public:
  const int LIMITE_CHAR = 40;
protected:
    void mostrarLinhas(vector<string>, int, int, int);
    void mostrarLinhas(vector<string>, int, int);
};

//por: Victor André 211026664
template <class entidade>
class TelaApresentacao:public Tela {
  public:
  virtual void apresentar(entidade) = 0;
};

//por: Victor André 211026664
class TelaMenu:public Tela {
  public:
  string apresentar(string, vector<string>);
};

//por: Victor André 211026664
class TelaCampo:public Tela {
  public:
  string apresentar(string, string);
};

//por: Victor André 211026664
class TelaFormulario:public Tela {
  public:
  void apresentar(string, vector<string>, string *);
};

//por: Victor André 211026664
class TelaMensagem:public Tela {
  public:
  void apresentar(string);
};

//por: Victor André 211026664
class TelaMensagens:public Tela {
  public:
    void apresentar(vector<string>);
};

//por: Victor André 211026664
class TelaConfirmarDescadastrar:public Tela {
  public:
    bool apresentar();
};

//por: Victor André 211026664
class TelaControle {
public:
    char apresentar();
};

//por: Victor André 211026664
class TelaAutenticacao: public Tela {
  public:
    void apresentar(Desenvolvedor*);
};

//por: Victor André 211026664
class TelaConsultaCodigo: public Tela {
  public:
    void apresentar(Codigo*);
};

//por: Victor André 211026664
class TelaConsultarDesenvolvedor: public Tela {
  public:
    void apresentar(Desenvolvedor);
};

//por: Victor André 211026664
class TelaConsultarTeste: public Tela {
  public:
    void apresentar(Teste);
};

//por: Victor André 211026664
class TelaConsultarCasoDeTeste: public Tela {
  public:
    void apresentar(CasoDeTeste);
};

#endif  //  TELAS_HPP_INCLUDED