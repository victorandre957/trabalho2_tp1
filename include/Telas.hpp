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

class Tela {
public:
  const int LIMITE_CHAR = 40;
protected:
    void mostrarLinhas(vector<string>, int, int, int);
    void mostrarLinhas(vector<string>, int, int);
};

template <class entidade>
class TelaApresentacao:public Tela {
  public:
  virtual void apresentar(entidade) = 0;
};

class TelaMenu:public Tela {
  public:
  string apresentar(string, vector<string>);
};

class TelaCampo:public Tela {
  public:
  string apresentar(string, string);
};

class TelaFormulario:public Tela {
  public:
  void apresentar(string, vector<string>, string *);
};

class TelaMensagem:public Tela {
  public:
  void apresentar(string);
};

class TelaMensagens:public Tela {
  public:
    void apresentar(vector<string>);
};

class TelaConfirmarDescadastrar:public Tela {
  public:
    bool apresentar();
};

class TelaControle {
public:
    char apresentar();
};

class TelaAutenticacao: public Tela {
  public:
    void apresentar(Desenvolvedor*);
};

class TelaConsultaCodigo: public Tela {
  public:
    void apresentar(Codigo*);
};

class TelaConsultarDesenvolvedor: public Tela {
  public:
    void apresentar(Desenvolvedor);
};

class TelaConsultarTeste: public Tela {
  public:
    void apresentar(Teste);
};

class TelaConsultarCasoDeTeste: public Tela {
  public:
    void apresentar(CasoDeTeste);
};

#endif  //  TELAS_HPP_INCLUDED