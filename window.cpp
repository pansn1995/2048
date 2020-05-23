#include "window.h"

void initialize()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));
}

void shutdown(){
    endwin();
}
