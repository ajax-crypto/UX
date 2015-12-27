#include "../include/window.hpp"

namespace ux
{
    Window::Window(int w, int h) :
    Component{"", 0, 0, w, h}
    {
        START ;
        m_closed = false ;
        m_background_color = Color{200, 200, 200};
        m_shape.setSize(Vec2f{w, h});
        m_shape.setFillColor(m_background_color);
        LookAndFeel::LoadFonts();
        END ;
    }

    void Window::draw(Window_Impl* w)
    {
        START ;
        m_shape.setFillColor(m_background_color);
        w->draw(m_shape);
        //for(auto c : m_children)
            //c->draw(w);
        for(auto&& pair : drawables) {
            LOG("Drawing z-level: " << pair.first);
            for(auto&& element : pair.second)
                element->draw(w);
        }
        GlobalDrawingStates::Redraw = false;
        Animator::Animate();
        LOG("Drawing call completed #" << m_dcalls++) ;
        END ;
    }

    void Window::handleEvents(const Event& event)
    {
        switch(event.type)
        {
            case Event::LostFocus:
                m_focused = false ;
                m_last_event = UXEvents::LostFocus ;
                for(auto& c : m_children)
                    c->stealFocus();
            break;

            case Event::GainedFocus:
                m_focused = true ;
                m_last_event = UXEvents::GainedFocus ;
            break;

            case Event::MouseLeft:
                m_focused = false ;
                for(auto& c : m_children)
                    c->stealFocus();
            break ;

            case Event::Closed:
                m_closed = true;
            break;

            case Event::MouseButtonPressed:
                m_last_event = UXEvents::MouseButtonPressed;
            break ;

            case Event::MouseButtonReleased:
                m_last_event = UXEvents::MouseButtonReleased;
            break;

            case Event::MouseMoved:
                m_last_event = UXEvents::MouseMoved;
            break ;

            case Event::Resized:
                GlobalDrawingStates::Redraw = false ;
                m_shape.setSize(Vec2f{event.size.width, event.size.height});
            break ;
        }

        //LOG("Sending to children..");
        for(auto c : m_children)
        {
            c->handleEvents(event);
        }
    }

    bool Animator::Animate()
    {
        //START;
        for(auto&& c : Component::all_elements)
        {
            //LOG("Number of animation : " << c.second->animations.size());
            for(auto&& anim : c.second->m_animations) {
                //LOG("PAnimations : " << anim.second.size());
                for(auto&& am : anim.second) {
                    if(am->m_running) {
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
