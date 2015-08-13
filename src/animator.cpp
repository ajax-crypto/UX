#include "../include/animator.h"

namespace ux
{
    bool GlobalDrawingStates::IsWithin(const StyleData& e,
                                       float x, float y)
    {
        switch(e.shape.type)
        {
            case RECTANGLE:
                return IsRectWithin(x, y, e.position.x, e.position.y, e.shape.rect.width, e.shape.rect.height);

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
        finished = anim_impl(running);
        running = !finished ;
        END;
    }

    unsigned int AnimCount::seed = 0;
    anim_func Animation::NO_ANIMATION = [](bool){ return true; };
}
