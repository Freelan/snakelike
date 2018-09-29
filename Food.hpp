#ifndef FOOD_H
#define FOOD_H

#include "Segment.hpp"

class Food
{
    public:
        Food() {}
        
        Food( int t_y, int t_x )
        {
            m_position.y = t_y;
            m_position.x = t_x;
        }

        ~Food() {}

        void display() const
        {
            mvprintw( m_position.y, m_position.x, "%c", m_look );
        }

        Point getPosition() const
        {
            return m_position;
        }

    private:
        char m_look{ '*' };
        Point m_position;
};

#endif
