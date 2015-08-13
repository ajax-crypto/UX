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
        style(ELEMENT_POSITION, Vec2f{x, y});
        //std::cout << "style.shape.position = "  << style.shape.position << "\n";
        style.shape.rect.height = h ;
        style.shape.rect.width = w ;
        style.content.text = str ;
        if(str.size() != 0u)
            style.content.font_size = 0.75f * w / static_cast<float>(str.size()) ;
        else
            style.content.font_size = 0u ;
        style.shape.type = RECTANGLE ;
        style.content.color = Color{255, 255, 255};
        style.content.auto_size = true;
        style.content.alignment = CENTER ;
        style.outline.width = 0u ;
        if(style.border.width > 0)
        {
            border_bottom = new RectangleShape(Vec2f{ w, style.border.width });
            border_top = new RectangleShape(Vec2f{ w, style.border.width });
            border_left = new RectangleShape(Vec2f{ style.border.width, h });
            border_right = new RectangleShape(Vec2f{ style.border.width, h });
        }
        else
        {
            if(style.border.left > 0)
                border_left = new RectangleShape(Vec2f{ style.border.width, h });
            if(style.border.right > 0)
                border_right = new RectangleShape(Vec2f{ style.border.width, h });
            if(style.border.top > 0)
                border_top = new RectangleShape(Vec2f{ w, style.border.width });
            if(style.border.bottom > 0)
                border_bottom = new RectangleShape(Vec2f{ w, style.border.width });
        }
        END ;
    }

    void LookAndFeel::imbue_properties()
    {
        START ;
        //prev_style = style ;
        apply_current_changes();
        END ;
    }

    void LookAndFeel::apply_current_changes()
    {
        START;
        auto size = 0u ;
        text_impl = Text{style.content.text, Regular};
        text_impl.setColor(style.content.color);
        text_impl.setStyle(Text::Regular);
        if(style.shape.type != prev_style.shape.type ||
           style.shape.rect.height != prev_style.shape.rect.height ||
           style.shape.rect.width != prev_style.shape.rect.width)
            texture.create(style.shape.rect.width + (2.f * style.outline.width),
                           style.shape.rect.height + (2.f * style.outline.width));
        LOG("Content : " << style.content.text);

        switch(style.shape.type)
        {
            case RECTANGLE:
                LOG("Rectangle!!!");
                typedef RectangleShape R ;
                if(prev_style.shape.type != RECTANGLE)
                {
                    //PAUSE;
                    if(shape_impl != nullptr)
                        delete shape_impl ;
                    shape_impl = new R();
                }
                dynamic_cast<R*>(shape_impl)->setSize(Vec2f{style.shape.rect.width, style.shape.rect.height});
                size = style.content.text.size();
                if(style.content.auto_size)
                {
                    style.content.font_size = (size != 0u) ?
                        0.75f * style.shape.rect.width / static_cast<float>(size) : 0u ;
                }
                text_impl.setCharacterSize(style.content.font_size);
                setText(style.content.text);

                if(style.border.width > 0)
                {
                    border_bottom->setPosition(style.shape.position + Vec2f{0, style.shape.rect.height - style.border.width});
                    border_top->setPosition(style.shape.position);
                    border_left->setPosition(style.shape.position);
                    border_right->setPosition(style.shape.position + Vec2f{style.shape.rect.width - style.border.width, 0});

                    border_bottom->setFillColor(style.border.color);
                    border_top->setFillColor(style.border.color);
                    border_left->setFillColor(style.border.color);
                    border_right->setFillColor(style.border.color);
                }
                else
                {
                    if(style.border.left > 0)
                    {
                        border_left->setPosition(style.shape.position);
                        border_left->setFillColor(style.border.color);
                    }
                    if(style.border.right > 0)
                    {
                        border_right->setPosition(style.shape.position + Vec2f{style.shape.rect.width - style.border.width, 0});
                        border_left->setFillColor(style.border.color);
                    }

                    if(style.border.top > 0)
                    {
                        border_top->setPosition(style.shape.position);
                        border_left->setFillColor(style.border.color);
                    }

                    if(style.border.bottom > 0)
                    {
                        border_bottom->setPosition(style.shape.position + Vec2f{0, style.shape.rect.height - style.border.width});
                        border_left->setFillColor(style.border.color);
                    }
                }
            break;

            case CIRCLE: LOG("Circle!!!"); break;
            case ROUNDED_RECTANGLE: LOG("Rounded Rectangle!!!"); break ;
            case TRIANGLE: LOG("Triangle!!!");break ;
            case ELLIPSE: LOG("Ellipse!!!"); break ;
            default: LOG("Invalid Shape!!!"); return;
        }

        shape_impl->setPosition(style.shape.position);
        shape_impl->setFillColor(style.shape.color);
        shape_impl->setOutlineThickness(style.outline.width);

#ifdef ELEMENT_PROPERTIES
        LOG("*********************Styles**********************");
        LOG("style.content = "  << style.content.text);
        LOG("style.content.size = "  << style.content.text.size());
        LOG("style.content.color = "  << style.content.color);
        LOG("style.shape.color = "  << style.shape.color);
        LOG("style.shape.outline = "  << style.outline.width);
#endif

        GlobalDrawingStates::Redraw = true ;
        prev_style = style ;
        END;
    }

    void LookAndFeel::setText(const std::string& str)
    {
        style.content.text = str ;
        text_impl.setString(str);
        auto metrics = text_impl.getGlobalBounds();
        auto pos = style.content.position ;
        switch(style.content.alignment)
        {
        case CENTER:
           text_impl.setPosition(pos.x + (style.shape.rect.width - metrics.width)/2.f,
                                 pos.y + (int)((style.shape.rect.height - style.content.font_size)/2.f));
        break ;

        case RIGHT:
            text_impl.setPosition(pos.x + style.shape.rect.width - metrics.width,
                                  pos.y + (int)((style.shape.rect.height - style.content.font_size)/2.f));
        break ;
        }
    }

    Font LookAndFeel::Regular ;
    Font LookAndFeel::Bold ;

}
