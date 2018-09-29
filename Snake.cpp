#include "Snake.hpp"

const char Snake::FULL_SEGMENT;

Segment::Direction opposite( Segment::Direction t_direction )
{
    switch ( t_direction )
    {
        case Segment::Direction::Left:
            return Segment::Direction::Right;
        case Segment::Direction::Right:
            return Segment::Direction::Left;
        case Segment::Direction::Up:
            return Segment::Direction::Down;
        case Segment::Direction::Down:
            return Segment::Direction::Up;
    }
}

void centeredmvprintw( int y, std::string t_string )
{
    int x = getmaxx( stdscr ) / 2 - t_string.length() / 2;
    mvprintw( y, x, t_string.c_str() );
}

Snake::Snake()
{
    m_segments.emplace_back( 5, 5, '#' );
} //ctor

Snake::Snake( std::vector<Food>* t_foods ) : m_foods( t_foods )
{
    for ( int i = 0; i < 4; ++i )
    {
        m_segments.emplace_back( 5, 5 + i, '#' );
    }
} //ctor

Snake::~Snake()
{

} //dtor

void Snake::gameOver()
{
    clear();
    int score = m_segments.size();
    
    centeredmvprintw( 3, "GAME OVER\n\n" );
    centeredmvprintw( 6, "Your score: " + std::to_string( score ) );
    centeredmvprintw( 23, "[q] quit\n" );
    refresh();

    flash();
    napms( 50 );
    flash();
    napms( 50 );
    flash();
    napms( 50 );

    while ( getch() != 'q' ) {}
}

void Snake::grow( auto t_point, Segment::Direction t_direction )
{
    m_segments.emplace_back( t_point, FULL_SEGMENT );
    m_segments.back().move( t_direction );
}

void Snake::movementLoop()
{
    nodelay( stdscr, TRUE );
    char ch = ' ';
    auto currentDirection = Segment::Direction::Right;

    while ( move( currentDirection ) )
    {
        ch = getch();

        if ( ch == 'a' || ch == 'd' || ch == 'w' || ch == 's' )
        {
            auto newDirection = static_cast<Segment::Direction>( ch );

            if ( currentDirection != opposite( newDirection ) )
            {
                currentDirection = newDirection;
            }
        }

        napms( m_delay );
    }

    m_over = true;
    return;
}

void Snake::display() const
{
    for ( auto& segment : m_segments )
    {
        segment.display();
    }
}

void Snake::displayFoods() const
{
    for ( auto food : *m_foods )
    {
        food.display();
    }
}

bool Snake::move( Segment::Direction t_direction )
{
    m_segments.front().setPosition( m_segments.back().getPosition() );
    m_segments.front().move( t_direction );
    m_segments.front().setLook( SEGMENT );

    std::rotate( m_segments.begin(), ++m_segments.begin(), m_segments.end() );

    if ( !collides( m_segments.back() ) )
    {
        for ( auto i = begin( *m_foods ); i != end( *m_foods ); ++i )
        {
            if ( m_segments.back().collides( i->getPosition() ) )
            {
                grow( i->getPosition(), t_direction );
                m_foods->erase( i );
                makeFoods( m_foods, 1 );

                break;
            }
        }

        return true;
    }

    return false;
}

bool Snake::collides( const auto& t_segment ) const
{
    for ( auto it = begin( m_segments ); it != --end( m_segments ); ++it )
    {
        if ( it->getPosition() == t_segment.getPosition() )
        {
            return true;
        }
    }

    return false;
}

bool Snake::isOver() const
{
    return m_over;
}

int Snake::getDelay() const
{
    return m_delay;
}
