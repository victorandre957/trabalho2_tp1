#include <iostream>

#ifdef WIN32
    #include "curses.hpp"
#else
    #include <ncurses.h>
#endif  // WIN32

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
