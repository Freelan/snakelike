#include <thread>
#include <random>
#include <ctime>

#include <curses.h>

#include "Snake.hpp"
#include "Food.hpp"
#include "DrawingThread.hpp"

void makeFoods( auto* foods, int amount )
{
    std::mt19937 gen;
    gen.seed( std::time( NULL ) );
    std::uniform_int_distribution<> randx( 0, getmaxx( stdscr ) ) ;
    std::uniform_int_distribution<> randy( 0, getmaxy( stdscr ) ) ;

    for ( int i = 0; i < amount; ++i )
    {
        foods->emplace_back( randy( gen ), randx( gen ) );
    }
}

int main()
{
    initscr();
    noecho();
    curs_set( 0 );

    std::vector<Food> foods;
    Snake snake( &foods );

    makeFoods( &foods, 1 );

    DrawingThread drawing( snake );
    std::thread drawingThread( drawing );

    snake.movementLoop();
    drawingThread.join();
    snake.gameOver();

    getch();
    endwin();
    return 0;
}
