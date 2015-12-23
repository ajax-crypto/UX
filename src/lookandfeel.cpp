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
        //std::cout << "style.shape.position = "  << style.shape.position << "\n";
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

    bool LookAndFeel::updatableChange() const
    {
        return m_style.m_content.m_alignment != m_prev_style.m_content.m_alignment ||
               m_style.m_position != m_prev_style.m_position ||
               m_style.m_padding != m_prev_style.m_padding ;
    }

    void LookAndFeel::apply_current_changes()
    {
        START;
        auto size = 0u ;
        m_text_impl = Text{m_style.m_content.m_text, Regular};
        m_text_impl.setColor(m_style.m_content.m_color);
        m_text_impl.setStyle(Text::Regular);
        if(m_style.m_shape.m_type != m_prev_style.m_shape.m_type ||
           m_style.m_shape.m_rect.m_height != m_prev_style.m_shape.m_rect.m_height ||
           m_style.m_shape.m_rect.m_width != m_prev_style.m_shape.m_rect.m_width)
            m_texture.create(m_style.m_shape.m_rect.m_width + m_style.m_border.m_left + m_style.m_border.m_right,
                             m_style.m_shape.m_rect.m_height + m_style.m_border.m_top + m_style.m_border.m_bottom);
        LOG("Content : " << m_style.m_content.m_text);

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
                size = m_style.m_content.m_text.size();
                if(m_style.m_content.m_auto_size)
                {
                    m_style.m_content.m_font_size = (size != 0u) ?
                        0.75f * m_style.m_shape.m_rect.m_width / static_cast<float>(size) : 0u ;
                }
                m_text_impl.setCharacterSize(m_style.m_content.m_font_size);
                setText(m_style.m_content.m_text);


                if(m_style.m_border.m_left > 0.f)
                {
                    m_border_left->setPosition(m_style.m_shape.m_position);
                    m_border_left->setFillColor(m_style.m_border.m_color);
                }
                if(m_style.m_border.m_right > 0.f)
                {
                    m_border_right->setPosition(m_style.m_shape.m_position +
                                                Vec2f{m_style.m_shape.m_rect.m_width - m_style.m_border.m_right, 0});
                    m_border_left->setFillColor(m_style.m_border.m_color);
                }
                if(m_style.m_border.m_top > 0.f)
                {
                    m_border_top->setPosition(m_style.m_shape.m_position);
                    m_border_left->setFillColor(m_style.m_border.m_color);
                }
                if(m_style.m_border.m_bottom > 0.f)
                {
                    m_border_bottom->setPosition(m_style.m_shape.m_position +
                                                 Vec2f{0, m_style.m_shape.m_rect.m_height - m_style.m_border.m_bottom});
                    m_border_left->setFillColor(m_style.m_border.m_color);
                }

            break;

            case CIRCLE: LOG("Circle!!!"); break;
            case ROUNDED_RECTANGLE: LOG("Rounded Rectangle!!!"); break ;
            case TRIANGLE: LOG("Triangle!!!");break ;
            case ELLIPSE: LOG("Ellipse!!!"); break ;
            default: LOG("Invalid Shape!!!"); return;
        }

        m_shape_impl->setPosition(m_style.m_shape.m_position);
        m_shape_impl->setFillColor(m_style.m_shape.m_color);

#ifdef ELEMENT_PROPERTIES
        LOG("*********************Styles**********************");
        LOG("style.content = "  << style.content.text);
        LOG("style.content.size = "  << style.content.text.size());
        LOG("style.content.color = "  << style.content.color);
        LOG("style.shape.color = "  << style.shape.color);
        LOG("style.shape.outline = "  << style.outline.width);
#endif

        GlobalDrawingStates::Redraw = true ;

        m_prev_style = m_style ;
        END;
    }

    void LookAndFeel::setText(const std::string& str)
    {
        m_style.m_content.m_text = str ;
        m_text_impl.setString(str);
        auto metrics = m_text_impl.getGlobalBounds();
        auto pos = m_style.m_content.m_position ;
        switch(m_style.m_content.m_alignment)
        {
        case CENTER:
            m_text_impl.setPosition(pos.x + (m_style.m_shape.m_rect.m_width - metrics.width)/2.f,
                                 pos.y + (int)((m_style.m_shape.m_rect.m_height - m_style.m_content.m_font_size)/2.f));
        break ;

        case RIGHT:
            m_text_impl.setPosition(pos.x + m_style.m_shape.m_rect.m_width - metrics.width,
                                  pos.y + (int)((m_style.m_shape.m_rect.m_height - m_style.m_content.m_font_size)/2.f));
        break ;
        }
    }

    Font LookAndFeel::Regular ;
    Font LookAndFeel::Bold ;

}
