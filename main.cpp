#include <iostream>

#include <ncurses.h>

#include "Interfaces.hpp"
#include "Controladoras.hpp"
#include "Builders.hpp"
#include "Telas.hpp"
#include "Dominios.hpp"
#include "ComandosSQL.hpp"

TelaMensagem telaMensagem;

using namespace std;

int main() {
    telaMensagem.apresentar("Dado em formato incorreto");
    return 0;
}
