#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

class Snake
{
    public:
        Snake();
        ~Snake();

        void movement();
    private:
        bool over = false;
        int y = 9;
        int x = 40;
        int i = -1;
        int tempX;
        int tempY;
        int direction = 0;
        int snakeLength = 1;
        int delay = 100;
        std::vector <int> segmentPositionY;
        std::vector <int> segmentPositionX;

        void grow();
        void gameOver();
};

#endif // SNAKE_H
