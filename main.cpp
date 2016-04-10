#include <SFML/Audio.hpp>
#include <curses.h>
#include "snake.h"

using namespace std;

void printFood();

int main()
{
    initscr();
    noecho();
    curs_set(0);

    sf::Music music;
    music.openFromFile( "music.ogg" );
    music.setLoop(true);
    music.play();

    printFood();

    snake Snake;
    Snake.movement();

    music.stop();
    endwin();
    return 0;
}
