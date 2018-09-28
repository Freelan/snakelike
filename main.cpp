#include <curses.h>
#include "Snake.hpp"

void printFood();

int main()
{
    initscr();
    noecho();
    curs_set( 0 );

    printFood();

    Snake snake;
    snake.movement();

    endwin();
    return 0;
}
