#include "../include/window.hpp"

namespace ux
{
    Window::Window(int w, int h) :
    Component{"", 0, 0, w, h}
    {
        START ;
        closed = false ;
        background_color = Color{200, 200, 200};
        shape.setSize(Vec2f{w, h});
        shape.setFillColor(background_color);
        LookAndFeel::LoadFonts();
        //this->parent = nullptr ;
        END ;
    }

    void Window::draw(Window_Impl* w)
    {
        //START ;
        shape.setFillColor(background_color);
        w->draw(shape);
        for(auto c : children)
            c->draw(w);
        GlobalDrawingStates::Redraw = false;
        Animator::Animate();
        LOG("Drawing calls #" << dcalls++) ;
        //END ;
    }

    void Window::handleEvents(const Event& event)
    {
        switch(event.type)
        {
            case Event::LostFocus:
                focused = false ;
                last_event = UXEvents::LostFocus ;
                for(auto& c : children)
                    c->stealFocus();
            break;

            case Event::GainedFocus:
                focused = true ;
                last_event = UXEvents::GainedFocus ;
            break;

            case Event::MouseLeft:
                focused = false ;
                for(auto& c : children)
                    c->stealFocus();
            break ;

            case Event::Closed:
                closed = true;
            break;

            case Event::MouseButtonPressed:
                last_event = UXEvents::MouseButtonPressed;
            break ;

            case Event::MouseButtonReleased:
                last_event = UXEvents::MouseButtonReleased;
            break;

            case Event::MouseMoved:
                last_event = UXEvents::MouseMoved;
            break ;

            case Event::Resized:
                GlobalDrawingStates::Redraw = false ;
                shape.setSize(Vec2f{event.size.width, event.size.height});
            break ;
        }

        //LOG("Sending to children..");
        for(auto c : children)
        {
            c->handleEvents(event);
        }
    }

    bool Animator::Animate()
    {
        //START;
        for(auto& c : Component::all_elements)
        {
            //LOG("Number of animation : " << c.second->animations.size());
            for(auto& anim : c.second->animations) {
                //LOG("PAnimations : " << anim.second.size());
                for(auto am : anim.second) {
                    if(am->running) {
                        (*am)();
                        Component::all_elements[am->getId().getElementId()]->apply_current_changes();
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds{global_delta});
        //END;
        return true ;
    }

    unsigned int Animator::global_delta = 10 ;
}
