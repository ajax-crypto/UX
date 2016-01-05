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
    
    bool operator==(const Shadow& lhs, const Shadow& rhs)
    {
        return lhs.m_color == rhs.m_color &&
               lhs.m_spread == rhs.m_spread &&
               lhs.m_smooth == rhs.m_smooth ;
    }
    
    bool operator==(const Graphics& lhs, const Graphics& rhs)
    {
        return lhs.m_texture == rhs.m_texture &&
               lhs.m_z == rhs.m_z &&
               lhs.m_smooth == rhs.m_smooth &&
               lhs.m_repeat == rhs.m_repeat;
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
            
        case BORDER_COLOR:
            m_shape.m_border.m_color = c ;
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
            c = m_shape.m_border.m_color;
            break ;
            
        case BORDER_TOP_COLOR:
            c = m_shape.m_border_top.m_color;
            break;
            
        case BORDER_BOTTOM_COLOR:
            c = m_shape.m_border_bottom.m_color;
            break;
           
        case BORDER_LEFT_COLOR:
            c = m_shape.m_border_left.m_color;
            break;
            
        case BORDER_RIGHT_COLOR:
            c = m_shape.m_border_right.m_color;
            break;

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
    
    bool StyleData::operator==(const StyleData& another) const
    {
        return (m_position == another.m_position) &&
               (m_shape == another.m_shape) &&
               (m_content == another.m_content) &&
               (m_padding == another.m_padding) &&
               (m_margin == another.m_margin) &&
               (m_border == another.m_border) &&
               (m_graphics == another.m_graphics);
    }
    
    bool StyleData::operator!=(const StyleData& another) const
    {
        return !(operator==(another));
    }

    bool GlobalDrawingStates::Redraw = true ;

    std::ostream& operator<<(std::ostream& stream, const Sides& s)
	{
	    stream << "{ Top:" << s.m_top << " Bottom:" << s.m_bottom <<
               " Left:" << s.m_left << " Right:" << s.m_right << " }";
        return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const Border& b)
	{
	    stream << "{ Dim:{ Top:" << b.m_top << " Bottom:" << b.m_bottom <<
               " Left:" << b.m_left << " Right:" << b.m_right << " }, Color:" <<
               b.m_color << " }";
        return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const Content& c)
	{
	    auto align = [&c]() {
            switch(c.m_alignment) {
            case LEFT: return "LEFT";
            case RIGHT: return "RIGHT";
            case CENTER: return "CENTER";
            }
            return "UNDEFINED";
	    };

	    stream << "{ Text:" << c.m_text << " Position:" << c.m_position << " Font-size:"
	           << c.m_font_size << " Auto-size?:" << c.m_auto_size << " Bounding-box:"
	           << c.m_bounding_box << " Alignment:" << align() << " }";
        return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const ElementShape& s)
	{
	    auto type = [&s]() {
            switch(s.m_type) {
            case RECTANGLE: return "RECTANGLE";
            case CIRCLE: return "CIRCLE";
            }
            return "UNDEFINED";
	    };

	    stream << "{ Type:" << type() << " Color:" << s.m_color
	           << " Position:" << s.m_position << " }";
        return stream;
	}
}
