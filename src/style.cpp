#include "../include/style.hpp"

namespace ux
{
    bool operator==(const ElementShape& lhs, const ElementShape& rhs)
    {
        bool same_shape = lhs.m_type == rhs.m_type ;
        if(same_shape)
        {
            switch(lhs.m_type)
            {
                case RECTANGLE: same_shape = lhs.m_rect == rhs.m_rect ;
                break ;

                case CIRCLE: same_shape = lhs.m_circle == rhs.m_circle ;
                break ;

                case ROUNDED_RECTANGLE: same_shape = lhs.m_rounded_rect == rhs.m_rounded_rect ;
                break;

                case ELLIPSE: same_shape = lhs.m_ellipse == rhs.m_ellipse ;
                break;

                case SECTOR: same_shape = lhs.m_sector == rhs.m_sector ;
                break;
            }
        }
        return same_shape && lhs.m_position == rhs.m_position && lhs.m_color == rhs.m_color ;
    }

    StyleData& StyleData::operator()(Property p, const Vec2f& vec)
    {

        auto set_content = [&](){
            m_content.m_position.x = vec.x + m_padding.m_left + m_margin.m_left + m_border.m_left ;
            m_content.m_position.y = vec.y + m_padding.m_top + m_margin.m_top + m_border.m_top ;
        };

        auto set_shape = [&]() {
            m_shape.m_position.x = m_position.x + m_margin.m_left + m_border.m_left ;
            m_shape.m_position.y = m_position.y + m_margin.m_top + m_border.m_top ;
        };

        switch(p)
        {
        case ELEMENT_POSITION:
            m_position = vec ;
            break;

        case SHAPE_POSITION:
            set_shape();
            break;

        case CONTENT_POSITION:
            set_content();
            break;

        default: break ;
        }
        return *this ;
    }

    StyleData& StyleData::operator()(Property p, const Color& c)
    {
        switch(p)
        {
        case TEXT_COLOR:
            m_content.m_color = c ;
            break ;

        case SHAPE_COLOR:
            m_shape.m_color = c ;
            break ;

        case SHADOW_COLOR:
            m_shadow.m_color = c ;
            break ;

        default: break ;
        }
        return *this ;
    }

    StyleData& StyleData::operator()(Property p, float amount)
    {
        switch(p)
        {
        case FONT_SIZE:
            if((amount * m_content.m_text.size()) < m_shape.m_rect.m_width ||
               amount < m_shape.m_rect.m_height)
                m_content.m_font_size = amount ;
            break ;

        case SHAPE_HEIGHT:
            m_shape.m_rect.m_height = amount ;
            break;

        case SHAPE_WIDTH:
            m_shape.m_rect.m_width = amount ;
            break ;

        case BORDER_WIDTH:
            m_border.m_right = amount ;
            m_border.m_left = amount ;
            m_border.m_top = amount ;
            m_border.m_bottom = amount ;
            break ;

        case PADDING_WIDTH:
            m_padding.m_right = amount ;
            m_padding.m_left = amount ;
            m_padding.m_top = amount ;
            m_padding.m_bottom = amount ;
            break ;

        case MARGIN_WIDTH:
            m_margin.m_right = amount ;
            m_margin.m_left = amount ;
            m_margin.m_top = amount ;
            m_margin.m_bottom = amount ;
            break ;

        case RADIUS:
            m_shape.m_circle.m_radius = amount ;
            break ;

        case RADIUS_MAJOR:
            m_shape.m_ellipse.m_major = amount ;
            break;

        case RADIUS_MINOR:
            m_shape.m_ellipse.m_minor = amount ;
            break;

        case RADIUS_TOPLEFT:
            m_shape.m_rounded_rect.m_topleft = amount ;
            break;

        case RADIUS_TOPRIGHT:
            m_shape.m_rounded_rect.m_topright = amount ;
            break;

        case RADIUS_BOTTOMLEFT:
            m_shape.m_rounded_rect.m_bottomleft = amount ;
            break;

        case RADIUS_BOTTOMRIGHT:
            m_shape.m_rounded_rect.m_bottomright = amount ;
            break;

        default: break ;
        }
        return *this ;
    }

    StyleData& StyleData::operator()(Property p, const Sides& sides)
    {
        switch(p)
        {
        case BORDER_WIDTH:
            m_border.m_right = sides.m_right ;
            m_border.m_left = sides.m_left ;
            m_border.m_top = sides.m_top ;
            m_border.m_bottom = sides.m_bottom ;
            break ;

        case PADDING_WIDTH:
            m_padding.m_right = sides.m_right ;
            m_padding.m_left = sides.m_left ;
            m_padding.m_top = sides.m_top ;
            m_padding.m_bottom = sides.m_bottom ;
            break ;

        case MARGIN_WIDTH:
            m_margin.m_right = sides.m_right ;
            m_margin.m_left = sides.m_left ;
            m_margin.m_top = sides.m_top ;
            m_margin.m_bottom = sides.m_bottom ;
            break ;

        default: break ;
        }
        return *this ;
    }

    void StyleData::extract(Property p, Color& c)
    {
        switch(p)
        {
        case TEXT_COLOR:
            c = m_content.m_color;
            break ;

        case SHAPE_COLOR:
            c = m_shape.m_color;
            break ;

        case SHADOW_COLOR:
            c = m_shadow.m_color;
            break ;

        case BORDER_COLOR:
            c = m_border.m_color;
            break ;

        default: break ;
        }
    }

    void StyleData::extract(Property p, Vec2f& v)
    {
        switch(p)
        {
        case ELEMENT_POSITION:
            v = m_position ;
            break;

        case SHAPE_POSITION:
            v = m_shape.m_position ;
            break;

        case CONTENT_POSITION:
            v = m_content.m_position ;
            break;

        default: break ;
        }
    }

    StyleData::StyleData()
    {
        m_position.x = m_position.y = 0.f ;
        m_positioning = RELATIVE ;
        m_shape.m_type = NONE;
        m_shape.m_position.x = m_shape.m_position.y = m_content.m_position.x = m_content.m_position.y = 0.f ;
        m_padding.m_top = m_padding.m_bottom = m_padding.m_left = m_padding.m_right = 0.f ;
        m_border.m_top = m_border.m_bottom = m_border.m_left = m_border.m_right = 0.f ;
        m_margin.m_top = m_margin.m_bottom = m_margin.m_left = m_margin.m_right = 0.f ;
        m_shadow.m_spread = 0.f ;
        m_content.m_auto_size = true ;
        m_visible = true ;
        m_graphics.m_z = 0;
        m_graphics.m_repeat = false;
        m_graphics.m_smooth = true;
        m_graphics.m_texture = 0u;
    }

    bool GlobalDrawingStates::Redraw = true ;
}
