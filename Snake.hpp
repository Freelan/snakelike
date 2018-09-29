#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <string>
#include <algorithm>

#include <curses.h>

#include "Segment.hpp"
#include "Food.hpp"

void makeFoods( auto*, int );

class Snake
{
    public:
        static const char FOOD_CHAR = '*';
        static const char SEGMENT = '#';
        static const char FULL_SEGMENT = '@';

        Snake();
        Snake( std::vector<Food>*  );
        ~Snake();

        void movementLoop();
        void display() const;
        void displayFoods() const;
        void gameOver();
        bool move( Segment::Direction t_direction );
        bool collides( const auto& t_segment ) const;
        bool isOver() const;
        int getDelay() const;

    private:
        void grow( auto, Segment::Direction );

        int  m_delay{ 100 };
        bool m_over{ false };
        std::vector<Segment> m_segments;
        std::vector<Food>*   m_foods;
};

#endif // SNAKE_H
