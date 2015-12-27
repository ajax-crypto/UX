#include "../include/basic_element.hpp"

namespace ux
{
    BasicElement::BasicElement(const std::string& t, int x, int y, int w, int h, bool def_anim) :
    Component{t, x, y, w, h}
    {
        START ;
        m_name = "BasicElement_" + std::to_string(m_id);
        LOG("Created : " << m_name);
        END ;
    }

    void BasicElement::draw(Window_Impl* w)
    {
        START;
        if(m_style.m_visible)
        {
            //if(m_style.m_graphics.m_texture == 0u)
            //{
                std::string str = m_text_impl.getString();
                LOG("Text: " << str);
                LOG("Position: " << m_text_impl.getPosition());
                LOG("Font Size: " << m_text_impl.getCharacterSize());
                LOG("Color: " << m_text_impl.getColor());

                m_texture.clear(Color{ 0, 0, 0, 255 });
                m_texture.draw(*m_shape_impl);
                ASSERT(m_shape_impl != nullptr, "Damn!");
                if(m_border_left != nullptr)
                    m_texture.draw(*m_border_left);
                if(m_border_right != nullptr)
                    m_texture.draw(*m_border_right);
                if(m_border_top != nullptr)
                    m_texture.draw(*m_border_top);
                if(m_border_bottom != nullptr)
                    m_texture.draw(*m_border_bottom);
                m_texture.draw(m_text_impl);
                m_texture.display();
                Sprite sprite{m_texture.getTexture()};
                sprite.setPosition(m_style.m_position);
                w->draw(sprite);
            //}
            //else
            //{
                /*
                Sprite sprite{TextureStore[m_style.m_texture].getTexture()};
                sprite.setPosition(style.position);
                w->draw(sprite);
                */
            //}
        }
        END;
    }

    void BasicElement::update(int x, int y)
    {
        m_style(ELEMENT_POSITION, Vec2f{ x, y });
        imbue();
    }

    void BasicElement::handleEvents(Event const& event)
    {
        EVENT_START;
        unsigned int ev = UXEvents::None ;
        bool prev = m_focused ;

        switch(event.type)
        {
            case Event::MouseMoved:
                m_focused = true ;
                if(m_focused && !prev)
                {
                    ev = UXEvents::GainedFocus;
                    for(auto& anim : m_animations[UXEvents::GainedFocus])
                        anim->start();
                    for(auto& anim : m_animations[UXEvents::LostFocus])
                        anim->stop();
                }
                else if(!m_focused && prev)
                {
                    ev = UXEvents::LostFocus ;
                    for(auto& anim : m_animations[UXEvents::GainedFocus])
                        anim->stop();
                    for(auto& anim : m_animations[UXEvents::LostFocus])
                        anim->start();
                }
                else if(m_focused && prev)
                    ev = UXEvents::InFocus ;
                else
                    ev = UXEvents::OutFocus ;

            break;

            case Event::MouseButtonPressed:
                for(auto& anim : m_animations[UXEvents::MouseButtonReleased])
                    anim->stop();
                for(auto& anim : m_animations[UXEvents::MouseButtonPressed])
                    anim->start();
                ev = UXEvents::MouseButtonPressed ;
            break;

            case Event::MouseButtonReleased:
                for(auto& anim : m_animations[UXEvents::MouseButtonPressed])
                    anim->stop();
                for(auto& anim : m_animations[UXEvents::MouseButtonReleased])
                    anim->start();
                ev = UXEvents::MouseButtonReleased ;
            break;
        }

        if(ev != UXEvents::None)
            for(auto& f : m_callbacks[ev])
                f(event);

        if(m_bubble_up)
            this->m_parent->handleEvents(event);

        EVENT_END;
    }

    void ToggleButton::addAnimations()
    {
         auto change_color = [&](bool running) mutable {
            LOG("Toggling");
            if(running)
            {
                if(m_toggle)
                    m_style.m_shape.m_color = m_toggle_color ;
                else
                    m_style.m_shape.m_color = m_normal_color ;
                this->apply_current_changes();
                GlobalDrawingStates::Redraw = true ;
            }
            return true ;
        };
        addAnimation(UXEvents::StateToggled, change_color);
    }

    ToggleButton::ToggleButton(const std::string& n, int x, int y, int w, int h,
                               const Color& tc, const Color& nc)
        : BasicElement{n, x, y, w, h},
          m_toggle{false}, m_toggle_color{tc}, m_normal_color{nc}
    {
        m_style.m_shape.m_color = m_normal_color ;
        addAnimations();
    }

    ToggleButton::ToggleButton()
    : BasicElement{"", 0, 0, 0, 0}
    {
       addAnimations();
    }

    void ToggleButton::toggleState(bool state)
    {
        m_toggle = state ;
    }

    void ToggleButton::setNormalColor(const Color& c)
    {
        m_normal_color = c;
        m_style.m_shape.m_color = m_normal_color ;
        imbue();
    }

    void ToggleButton::handleEvents(Event const& event)
    {
        EVENT_START;
        unsigned int ev = UXEvents::None ;
        bool prev = m_focused ;

        switch(event.type)
        {
            case Event::MouseMoved:
                m_focused = true ;
                if(m_focused && !prev)
                {
                    ev = UXEvents::GainedFocus;
                    for(auto& anim : m_animations[UXEvents::GainedFocus])
                        anim->start();
                    for(auto& anim : m_animations[UXEvents::LostFocus])
                        anim->stop();
                    GlobalDrawingStates::Redraw = true ;
                }
                else if(!m_focused && prev)
                {
                    ev = UXEvents::LostFocus ;
                    for(auto& anim : m_animations[UXEvents::GainedFocus])
                        anim->stop();
                    for(auto& anim : m_animations[UXEvents::LostFocus])
                        anim->start();
                    GlobalDrawingStates::Redraw = true ;
                }
            break;

            case Event::MouseButtonReleased:
                if(m_focused)
                {
                    ev = UXEvents::MouseButtonReleased ;
                    // Not working!!!!
                    //toggle = !toggle ;
                    m_toggle = m_toggle ? false : true ;
                    for(auto& f : m_callbacks[UXEvents::StateToggled])
                        f(event);
                    for(auto& anim : m_animations[UXEvents::StateToggled])
                        anim->start();
                }
            break;
        }

        if(ev != UXEvents::None)
            for(auto& f : m_callbacks[ev])
                f(event);

        EVENT_END;
    }
}
