#ifndef DRAWINGTHREAD_H
#define DRAWINGTHREAD_H

class DrawingThread
{
    public:
        DrawingThread( Snake& t_snake ) : m_snake( t_snake ) {}

        void operator()() const
        {
            while ( !m_snake.isOver() )
            {
                clear();
                m_snake.display();
                m_snake.displayFoods();
                refresh();
            }
        }

    private:
        Snake& m_snake;
};

#endif
