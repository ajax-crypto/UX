#include "../include/style.hpp"

namespace ux
{
    StyleData& StyleData::operator()(Property p, const Vec2f& vec)
    {

        auto set_content = [&](){
            content.position.x = (padding.left > 0) ?
                vec.x + padding.left + ((margin.left > 0) ? margin.left : margin.width) :
                vec.x + padding.width + ((margin.left > 0) ? margin.left : margin.width) ;

           content.position.y = (padding.top > 0) ?
                vec.y + padding.top + ((margin.top > 0) ? margin.top : margin.width) :
                vec.y + padding.width + ((margin.top > 0) ? margin.top : margin.width) ;
        };

        auto set_shape = [&]() {
            shape.position.x = (padding.left > 0) ?
                position.x + padding.left :
                position.x + padding.width ;

            shape.position.y = (padding.top > 0) ?
                position.y + padding.top :
                position.y + padding.width ;
        };

        switch(p)
        {
        case ELEMENT_POSITION:
            position = vec ;
            break;

        case SHAPE_POSITION:
            set_shape();
            break;

        case CONTENT_POSITION:
            set_content();
            break;

        }
        return *this ;
    }

    StyleData& StyleData::operator()(Property p, const Color& c)
    {
        switch(p)
        {
        case TEXT_COLOR:
            content.color = c ;
            break ;

        case SHAPE_COLOR:
            shape.color = c ;
            break ;

        case SHADOW_COLOR:
            shadow.color = c ;
            break ;

        case OUTLINE_COLOR:
            outline.color = c ;
            break ;
        }
        return *this ;
    }

    StyleData& StyleData::operator()(Property p, float amount)
    {
        switch(p)
        {
        case FONT_SIZE:
            if((amount * content.text.size()) < shape.rect.width ||
               amount < shape.rect.height)
                content.font_size = amount ;
            break ;

        case SHAPE_HEIGHT:
            shape.rect.height = amount ;
            break;

        case SHAPE_WIDTH:
            shape.rect.width = amount ;
            break ;

        case SHAPE_RADIUS:
            shape.circle.radius = amount ;
            break ;
        }
        return *this ;
    }

    void StyleData::extract(Property p, Color& c)
    {
        switch(p)
        {
        case TEXT_COLOR:
            c = content.color;
            break ;

        case SHAPE_COLOR:
            c = shape.color;
            break ;

        case SHADOW_COLOR:
            c = shadow.color;
            break ;

        case OUTLINE_COLOR:
            c = outline.color;
            break ;
        }
    }

    void StyleData::extract(Property p, Vec2f& v)
    {
        switch(p)
        {
        case ELEMENT_POSITION:
            v = position ;
            break;

        case SHAPE_POSITION:
            v = shape.position ;
            break;

        case CONTENT_POSITION:
            v = content.position ;
            break;
        }
    }

    StyleData::StyleData()
    {
        position.x = position.y = 0.f ;
        shape.type = NONE;
        shape.position.x = shape.position.y = content.position.x = content.position.y = 0.f ;
        padding.width = padding.top = padding.bottom = padding.left = padding.right = 0.f ;
        border.width = border.top = border.bottom = border.left = border.right = 0.f ;
        margin.width = margin.top = margin.bottom = margin.left = margin.right = 0.f ;
        shadow.spread = 0.f ;
        content.auto_size = true ;
        visible = true ;
    }

    bool GlobalDrawingStates::Redraw = true ;
}
