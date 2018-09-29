#ifndef SEGMENT_H
#define SEGMENT_H

#include <curses.h>

struct Point
{
    Point() {}
    Point( int t_y, int t_x ) : y( t_x ), x( t_x ) {}

    int y{ 0 };
    int x{ 0 };

    bool operator==( const Point& rhs ) const
    {
        return y == rhs.y && x == rhs.x;
    }
};

class Snake;

class Segment
{
    public:
        Segment() {}

        Segment( const Point& t_position, char t_look = '#' ) : m_position( t_position ), m_look( t_look )
        {

        }

        Segment( int t_y, int t_x, char t_look = '#' ) :  m_look( t_look )
        {
            setPosition( t_y, t_x );
        }

        ~Segment() {}

        enum class Direction
        {
            Left = 'a',
            Right = 'd',
            Up = 'w',
            Down = 's'
        };

        void display() const
        {
            mvprintw( m_position.y, m_position.x, "%c", m_look );
        }

        Point getPosition() const
        {
            return m_position;
        }

        void setPosition( const int t_y, const int t_x )
        {
            m_position.y = t_y;
            m_position.x = t_x;
        }

        void setPosition( Point t_point )
        {
            m_position = t_point;
        }

        void move( Direction t_direction )
        {
            switch ( t_direction )
            {
                case Direction::Left:
                    m_position.x -= 1;
                    break;
                case Direction::Right:
                    m_position.x += 1;
                    break;
                case Direction::Up:
                    m_position.y -= 1;
                    break;
                case Direction::Down:
                    m_position.y += 1;
                    break;
            }

            auto maxy = getmaxy( stdscr );
            auto maxx = getmaxx( stdscr );
            m_position.y = ( maxy + ( m_position.y % maxy ) ) % maxy;
            m_position.x = ( maxx + ( m_position.x % maxx ) ) % maxx;
        }

        bool collides( const Point& t_point ) const
        {
            return ( t_point == getPosition() );
        }

        void setLook( const char t_look )
        {
            m_look = t_look;
        }

        char getLook() const
        {
            return m_look;
        }

    private:
        Point m_position;
        char m_look{ '#' };
};

#endif
