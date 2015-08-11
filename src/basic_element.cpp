#include "..\include\basic_element.hpp"

namespace ux
{
    BasicElement::BasicElement(const std::string& t, int x, int y, int w, int h, bool def_anim) :
    Component{t, x, y, w, h}
    {
        START ;
        name = "BasicElement_" + id ;
        LOG(name);
        END ;
    }

    void BasicElement::draw(Window_Impl* w)
    {
        START;
        if(style.visible)
        {
            texture.clear(Color{ 0, 0, 0, 255 });
            texture.draw(*shape_impl);
            texture.draw(text_impl);
            ASSERT(shape_impl != nullptr, "Damn!");
            if(border_left != nullptr)
                texture.draw(*border_left);
            if(border_right != nullptr)
                texture.draw(*border_right);
            if(border_top != nullptr)
                texture.draw(*border_top);
            if(border_bottom != nullptr)
                texture.draw(*border_bottom);
            texture.display();
            Sprite sprite{texture.getTexture()};
            sprite.setPosition(style.position);
            w->draw(sprite);
        }
        END;
    }

    void BasicElement::update(int _x, int _y)
    {
        style(ELEMENT_POSITION, Vec2f{ _x, _y });
        this->imbue_properties();
    }

    void BasicElement::handleEvents(Event const& event)
    {
#ifdef EVENT_DEBUG
        START ;
#endif
        unsigned int ev = UXEvents::None ;
        bool prev = focused ;

        switch(event.type)
        {
            case Event::MouseMoved:
                focused = true ;
                if(focused && !prev)
                {
                    ev = UXEvents::GainedFocus;
                    LOG("Gained Focus...");
                    for(auto& anim : animations[UXEvents::GainedFocus])
                        anim->start();
                    for(auto& anim : animations[UXEvents::LostFocus])
                        anim->stop();
                }
                else if(!focused && prev)
                {
                    ev = UXEvents::LostFocus ;
                    LOG("Lost Focus...");
                    for(auto& anim : animations[UXEvents::GainedFocus])
                        anim->stop();
                    for(auto& anim : animations[UXEvents::LostFocus])
                        anim->start();
                }
                else if(focused && prev)
                    ev = UXEvents::InFocus ;
                else
                    ev = UXEvents::OutFocus ;

            break;

            case Event::MouseButtonPressed:
                for(auto& anim : animations[UXEvents::MouseButtonReleased])
                    anim->stop();
                for(auto& anim : animations[UXEvents::MouseButtonPressed])
                    anim->start();
                ev = UXEvents::MouseButtonPressed ;
            break;

            case Event::MouseButtonReleased:
                for(auto& anim : animations[UXEvents::MouseButtonPressed])
                    anim->stop();
                for(auto& anim : animations[UXEvents::MouseButtonReleased])
                    anim->start();
                ev = UXEvents::MouseButtonReleased ;
            break;
        }

        if(ev != UXEvents::None)
            for(auto& f : callbacks[ev])
                f(event);

        if(bubble_up)
            this->parent->handleEvents(event);

#ifdef EVENT_DEBUG
        END ;
#endif
    }

    void ToggleButton::addAnimations()
    {
         auto change_color = [&](bool running) mutable {
            LOG("Toggling");
            if(running)
            {
                if(toggle)
                    style.shape.color = toggle_color ;
                else
                    style.shape.color = normal_color ;
                this->apply_current_changes();
                GlobalDrawingStates::Redraw = true ;
            }
            return true ;
        };

        this->addAnimation(UXEvents::StateToggled, change_color);
    }

    ToggleButton::ToggleButton(const std::string& n, int x, int y, int w, int h,
                               const Color& tc, const Color& nc)
        : BasicElement{n, x, y, w, h},
          toggle{false}, toggle_color{tc}, normal_color{nc}
    {
        style.shape.color = normal_color ;
        addAnimations();
    }

    ToggleButton::ToggleButton()
    : BasicElement{"", 0, 0, 0, 0}
    {
       addAnimations();
    }

    void ToggleButton::toggleState(bool state)
    {
        toggle = state ;
    }

    void ToggleButton::setNormalColor(const Color& c)
    {
        normal_color = c;
        style.shape.color = normal_color ;
        imbue_properties();
    }

    void ToggleButton::handleEvents(Event const& event)
    {
        unsigned int ev = UXEvents::None ;
        bool prev = focused ;

        switch(event.type)
        {
            case Event::MouseMoved:
                focused = true ;
                if(focused && !prev)
                {
                    ev = UXEvents::GainedFocus;
                    //LOG("Gained Focus...");
                    for(auto& anim : animations[UXEvents::GainedFocus])
                        anim->start();
                    for(auto& anim : animations[UXEvents::LostFocus])
                        anim->stop();
                    GlobalDrawingStates::Redraw = true ;
                }
                else if(!focused && prev)
                {
                    ev = UXEvents::LostFocus ;
                    //LOG("Lost Focus...");
                    for(auto& anim : animations[UXEvents::GainedFocus])
                        anim->stop();
                    for(auto& anim : animations[UXEvents::LostFocus])
                        anim->start();
                    GlobalDrawingStates::Redraw = true ;
                }
            break;

            case Event::MouseButtonReleased:
                if(focused)
                {
                    ev = UXEvents::MouseButtonReleased ;
                    // Not working!!!!
                    //toggle = !toggle ;
                    toggle = toggle ? false : true ;
                    LOG("State Toggled... " << toggle);
                    for(auto& f : callbacks[UXEvents::StateToggled])
                        f(event);
                    for(auto& anim : animations[UXEvents::StateToggled])
                        anim->start();
                }
            break;
        }

        if(ev != UXEvents::None)
            for(auto& f : callbacks[ev])
                f(event);
    }
}
