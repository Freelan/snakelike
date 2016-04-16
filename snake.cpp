#include <curses.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "snake.h"

int getx()
{
    int tempx, tempy;
    getyx( stdscr, tempy, tempx );
    return tempx;
}

int gety()
{
    int tempx, tempy;
    getyx( stdscr, tempy, tempx );
    return tempy;
}

int getMaxX()
{
    int tempx, tempy;
    getmaxyx( stdscr, tempy, tempx );
    return tempx;
}

int getMaxY()
{
    int tempx, tempy;
    getmaxyx( stdscr, tempy, tempx );
    return tempy;
}

void centeredmvprintw( int y, std::string String )
{
    int x = getMaxX()/2 - String.length()/2;
    mvprintw( y, x, String.c_str() );
}

void printFood()
{
    srand( time( 0 ) );
    int randX = ( rand() % getMaxX()-3 ) + 3;
    int randY = ( rand() % getMaxY()-3 ) + 3;
    if( mvinch( randY, randX ) == 35 )  { //#
        printFood();
    }
    mvprintw( randY, randX, "*" );
}

snake::snake()
{
    segmentPositionX.resize( snakeLength+1 );
    segmentPositionY.resize( snakeLength+1 );
    //ctor
}

snake::~snake()
{
    //dtor
}

void snake::gameOver()
{
    clear();
    centeredmvprintw( 3, "GAME OVER\n\n" );
    int score = segmentPositionY.size();
    centeredmvprintw( 6, "Your score: " + std::to_string(score) );
    centeredmvprintw( 23, "[q] quit\n" );
    refresh();

    flash();
    napms(50);
    flash();
    napms(50);
    flash();
    napms(50);

    while( getch() != 'q' ) {}

    over = true;
//    endwin();
//    exit(0);
}

void snake::grow()
{
    if( mvinch( y, x ) == 42 ){
        flash();
        snakeLength++;
        segmentPositionX.resize( snakeLength+1 );
        segmentPositionY.resize( snakeLength+1 );
        printFood();
        //delay -= 5;
    }
}

void snake::movement()
{
    char Char;

    nodelay( stdscr,TRUE );

    while( (Char = getch()) < 0  && over != true)
    {
//        mvprintw( 0, 0, "                                                            ");
//        mvprintw( 0, 0, "i: %d, x: %d, y: %d, segY: %d, segX: %d, dir: %d, segx0: %d, segy0: %d",
//                  i+1, x, y, segmentPositionY.size(), segmentPositionX.size(), direction, segmentPositionX[0], segmentPositionY[0] );
        i++;

        mvprintw( segmentPositionY[i], segmentPositionX[i], " " );

        mvprintw( y, x, "#" );
        move( y, x );

        for( int j = 0; j < snakeLength; j++ )
        {
            segmentPositionX[i] = getx();
            segmentPositionY[i] = gety();
        }

        if( x > getMaxX() )
            x = -1;
        else if( x < 0 )
            x = getMaxX()+1;

        if( y > getMaxY() )
            y = -1;
        else if( y < 0 )
            y = getMaxY()+1;

        switch( direction )
        {
        case 1:
            if( mvinch( y, x+1 ) != '#' )
            {
                x++;
                grow();
            }else
                gameOver();
            break;
        case -1:
            if( mvinch( y, x-1 ) != '#' )
            {
                x--;
                grow();
            }else
                gameOver();
            break;
        case -2:
            if( mvinch( y+1, x ) != '#' )
            {
                y++;
                grow();
            }else
                gameOver();
            break;
        case 2:
            if( mvinch( y-1, x ) != '#' )
            {
                y--;
                grow();
            }else
                gameOver();
            break;
        }

        refresh();
        napms(delay);

        if( i == snakeLength ){
            i = -1;
        }
    }

    if( over == false )
    {
        nodelay(stdscr,FALSE);

        int oldDirection = direction;

        switch( Char )
        {
        case 'd':
            direction = 1;
            break;
        case 'a':
            direction = -1;
            break;
        case 's':
            direction = -2;
            break;
        case 'w':
            direction = 2;
            break;
        }

        if( direction == -oldDirection )
            direction = oldDirection;

        movement();
    }
}
