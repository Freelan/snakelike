#ifdef _WIN32
#include <windows.h>
#include "resource.h"
#endif // _WIN32

#include <SFML/Audio.hpp>
#include <curses.h>
#include "snake.h"

using namespace std;

#ifdef _WIN32
void LoadFileInResource(int name, int type, DWORD& size, const char*& data)
{
    HMODULE handle = ::GetModuleHandle(NULL);
    HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(name),
        MAKEINTRESOURCE(type));
    HGLOBAL rcData = ::LoadResource(handle, rc);
    size = ::SizeofResource(handle, rc);
    data = static_cast<const char*>(::LockResource(rcData));
}
#endif // _WIN32

void printFood();

int main()
{
    #ifdef _WIN32
    DWORD size = 0;
    const char* data = NULL;
    LoadFileInResource(IDR_MUSIC, 10, size, data);
    char* buffer = new char[size+1];
    ::memcpy(buffer, data, size);
    buffer[size] = 0; // NULL terminator
    #endif // _WIN32

    initscr();
    noecho();
    curs_set(0);

    sf::Music music;

    #ifdef _WIN32
    music.openFromMemory( buffer, 637752 );
    #else
    music.openFromFile( "music.ogg" );
    #endif

    music.setLoop(true);
    music.play();

    printFood();

    snake Snake;
    Snake.movement();

    music.stop();
    endwin();
    return 0;
}
