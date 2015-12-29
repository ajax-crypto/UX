#include "../include/lookandfeel.hpp"

namespace ux
{

    bool LookAndFeel::LoadFonts()
    {
        if(!Regular.loadFromFile("NotoSans-Regular.ttf"))
        {
            LOG("Error loading regular font!!!");
            return false ;
        }
        if(!Bold.loadFromFile("NotoSans-Bold.ttf"))
        {
            LOG("Error loading bold font!!!");
            return false;
        }
        return true ;
    }

    LookAndFeel::LookAndFeel(const std::string& str, int x, int y, int w, int h)
     : LookAndFeel()
    {
        START ;
        m_style(ELEMENT_POSITION, Vec2f{x, y});
        m_style.m_shape.m_rect.m_height = h ;
        m_style.m_shape.m_rect.m_width = w ;
        m_style.m_content.m_text = str ;
        if(str.size() != 0u)
            m_style.m_content.m_font_size = 0.75f * w / static_cast<float>(str.size()) ;
        else
            m_style.m_content.m_font_size = 0u ;
        m_style.m_shape.m_type = RECTANGLE ;
        m_style.m_content.m_color = Color{255, 255, 255};
        m_style.m_content.m_auto_size = true;
        m_style.m_content.m_alignment = CENTER ;
        if(m_style.m_border.m_left > 0)
            m_border_left = new RectangleShape(Vec2f{ m_style.m_border.m_left, h });
        if(m_style.m_border.m_right > 0)
            m_border_right = new RectangleShape(Vec2f{ m_style.m_border.m_right, h });
        if(m_style.m_border.m_top > 0)
            m_border_top = new RectangleShape(Vec2f{ w, m_style.m_border.m_top });
        if(m_style.m_border.m_bottom > 0)
            m_border_bottom = new RectangleShape(Vec2f{ w, m_style.m_border.m_bottom });
        END ;
    }

    bool LookAndFeel::childrenNeedUpdate() const
    {
        return m_style.m_content.m_alignment != m_prev_style.m_content.m_alignment ||
               m_style.m_position != m_prev_style.m_position ||
               m_style.m_padding != m_prev_style.m_padding ||
               m_style.m_margin != m_prev_style.m_margin;
    }
    
    bool LookAndFeel::isDirty() const
    {
        return m_style != m_prev_style ;
    }

    void LookAndFeel::apply_current_changes()
    {
        START;
        auto size = 0u ;
        if(m_style.m_shape.m_type != m_prev_style.m_shape.m_type ||
           m_style.m_shape.m_rect.m_height != m_prev_style.m_shape.m_rect.m_height ||
           m_style.m_shape.m_rect.m_width != m_prev_style.m_shape.m_rect.m_width)
            m_texture.create(m_style.m_shape.m_rect.m_width, m_style.m_shape.m_rect.m_height);

        switch(m_style.m_shape.m_type)
        {
        case RECTANGLE:
            LOG("Rectangle!!!");
            typedef RectangleShape R ;
            if(m_prev_style.m_shape.m_type != RECTANGLE)
            {
                if(m_shape_impl != nullptr)
                    delete m_shape_impl ;
                m_shape_impl = new R();
            }
            dynamic_cast<R*>(m_shape_impl)->setSize(
                Vec2f{m_style.m_shape.m_rect.m_width, m_style.m_shape.m_rect.m_height});
            setBorders();
        break;

        case CIRCLE: LOG("Circle!!!"); break;
        case ROUNDED_RECTANGLE: LOG("Rounded Rectangle!!!"); break ;
        case TRIANGLE: LOG("Triangle!!!");break ;
        case ELLIPSE: LOG("Ellipse!!!"); break ;
        default: LOG("Invalid Shape!!!"); return;
        }

        if(m_style.m_content.m_text.size() > 0u)
            setText();
        m_shape_impl->setPosition(m_style.m_shape.m_position);
        m_shape_impl->setFillColor(m_style.m_shape.m_color);
        GlobalDrawingStates::Redraw = true ;

        LOGSTYLE ;

        m_prev_style = m_style ;
        END;
    }

    void LookAndFeel::setBorders()
    {
        if(m_style.m_border.m_left > 0.f)
        {
            if(m_border_left == nullptr)
                m_border_left = new RectangleShape(
                    Vec2f{ m_style.m_border.m_left, m_style.m_shape.m_rect.m_height });
            m_border_left->setPosition(m_style.m_shape.m_position);
            m_border_left->setFillColor(m_style.m_border.m_color);
        }
        if(m_style.m_border.m_right > 0.f)
        {
            if(m_border_right == nullptr)
                m_border_right = new RectangleShape(
                    Vec2f{ m_style.m_border.m_left, m_style.m_shape.m_rect.m_height });
            m_border_right->setPosition(m_style.m_shape.m_position +
                Vec2f{ m_style.m_shape.m_rect.m_width - m_style.m_border.m_right, 0 });
            m_border_right->setFillColor(m_style.m_border.m_color);
        }
        if(m_style.m_border.m_top > 0.f)
        {
            if(m_border_top == nullptr)
                m_border_top = new RectangleShape(
                    Vec2f{ m_style.m_shape.m_rect.m_width, m_style.m_border.m_top });
            m_border_top->setPosition(m_style.m_shape.m_position);
            m_border_top->setFillColor(m_style.m_border.m_color);
        }
        if(m_style.m_border.m_bottom > 0.f)
        {
            if(m_border_bottom == nullptr)
                m_border_bottom = new RectangleShape(
                    Vec2f{ m_style.m_shape.m_rect.m_width, m_style.m_border.m_bottom });
            m_border_bottom->setPosition(m_style.m_shape.m_position +
                Vec2f{ 0, m_style.m_shape.m_rect.m_height - m_style.m_border.m_bottom });
            m_border_bottom->setFillColor(m_style.m_border.m_color);
        }
    }

    void LookAndFeel::setText()
    {
        START;
        switch(m_style.m_shape.m_type)
        {
        case RECTANGLE:
            m_style.m_content.m_bounding_box.m_top =
                m_style.m_position.y + m_style.m_padding.m_top + m_style.m_border.m_top ;
            m_style.m_content.m_bounding_box.m_left =
                m_style.m_position.x + m_style.m_padding.m_left + m_style.m_border.m_left ;
            m_style.m_content.m_bounding_box.m_right =
                m_style.m_position.x + m_style.m_shape.m_rect.m_width - m_style.m_padding.m_right - m_style.m_border.m_right ;
            m_style.m_content.m_bounding_box.m_bottom =
                m_style.m_position.y + m_style.m_shape.m_rect.m_height - m_style.m_padding.m_bottom - m_style.m_border.m_bottom ;
        break;
        }

        auto bb = m_style.m_content.m_bounding_box ;
        auto size = m_style.m_content.m_text.size();

        if(m_style.m_content.m_auto_size)
        {
            m_style.m_content.m_font_size = (size != 0u) ?
                0.75f * (bb.m_right - bb.m_left) / static_cast<float>(size) : 0u ;
        }

        m_text_impl.setColor(m_style.m_content.m_color);
        m_text_impl.setStyle(Text::Regular);
        m_text_impl.setFont(LookAndFeel::Regular);
        m_text_impl.setCharacterSize(m_style.m_content.m_font_size);
        m_text_impl.setString(m_style.m_content.m_text);

        auto metrics = m_text_impl.getGlobalBounds();
        LOG("Text Width: " << metrics.width);
        float x, y = bb.m_top + (int)(((bb.m_bottom - bb.m_top) - m_style.m_content.m_font_size)/2.f);
        switch(m_style.m_content.m_alignment)
        {
        case CENTER:
            x = bb.m_left + ((bb.m_right - bb.m_left) - metrics.width)/2.f ;
        break ;

        case RIGHT:
            x = bb.m_right - metrics.width;
        break ;

        case LEFT:
            x = bb.m_left;
        break;
        }
        LOG("Content Position: " << x << ", " << y);
        m_style.m_content.m_position = Vec2f{x, y};
        m_text_impl.setPosition(m_style.m_content.m_position);

        LOG("Content: " << m_style.m_content);
        END;
    }

    Font LookAndFeel::Regular ;
    Font LookAndFeel::Bold ;

}
