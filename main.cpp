#include <windows.h>
#include <SFML/Audio.hpp>
#include <curses.h>
#include "snake.h"
#include "resource.h"

using namespace std;

void printFood();

void LoadFileInResource(int name, int type, DWORD& size, const char*& data)
{
    HMODULE handle = ::GetModuleHandle(NULL);
    HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(name),
        MAKEINTRESOURCE(type));
    HGLOBAL rcData = ::LoadResource(handle, rc);
    size = ::SizeofResource(handle, rc);
    data = static_cast<const char*>(::LockResource(rcData));
}

int main()
{
    DWORD size = 0;
    const char* data = NULL;
    LoadFileInResource(IDR_MUSIC, 10, size, data);
    char* buffer = new char[size+1];
    ::memcpy(buffer, data, size);
    buffer[size] = 0; // NULL terminator

    initscr();
    noecho();
    curs_set(0);

    sf::Music music;
    music.openFromMemory( buffer, 637752);
    music.setLoop(true);
    music.play();

    printFood();

    snake Snake;
    Snake.movement();

    music.stop();
    //getch();
    //delete[] buffer;
    endwin();
    return 0;
}
