#include <iostream>
#include <ncurses.h>

#include "Interfaces.hpp"
#include "Controladoras.hpp"
#include "Builders.hpp"
#include "Telas.hpp"
#include "Dominios.hpp"
#include "ComandosSQL.hpp"

using namespace std;

int main() {
    initscr();

    refresh();

    getch();

    endwin();
    
    return 0;
}
