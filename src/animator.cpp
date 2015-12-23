#include "../include/animator.h"

namespace ux
{
    bool GlobalDrawingStates::IsWithin(const StyleData& e,
                                       float x, float y)
    {
        switch(e.m_shape.m_type)
        {
            case RECTANGLE:
                return IsRectWithin(x, y, e.m_position.x, e.m_position.y,
                                    e.m_shape.m_rect.m_width, e.m_shape.m_rect.m_height);

        }
        return false ;
    }

    bool GlobalDrawingStates::IsRectWithin(float x, float y,
                                           float originx, float originy,
                                           float width, float height)
    {
        return (x > originx) && (y > originy) && (x < originx + width) && (y < originy + height) ;
    }

    bool GlobalDrawingStates::IsCircleWithin(float x, float y,
                                             float originx, float originy,
                                             float radius)
    {
        x = x - originx ;
        y = y - originy ;
        return (x*x + y*y) <= radius*radius ;
    }

    void Animation::operator()()
    {
        START ;
        m_finished = m_anim_impl(m_running);
        m_running = !m_finished ;
        END;
    }

    unsigned int AnimCount::seed = 0;
    anim_func Animation::NO_ANIMATION = [](bool){ return true; };
}
