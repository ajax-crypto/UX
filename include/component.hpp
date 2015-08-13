#ifndef __UX_COMPONENT_
#define __UX_COMPONENT_

#include "event.hpp"
#include "lookandfeel.hpp"
#include "interpolate.hpp"
#include "animator.h"

namespace ux
{

    class AnimationID ;

    class Component :
        public LookAndFeel,
        public EventHandler
    {

        struct AnimInfo
        {
            Property     anim_param ;
            unsigned int anim_event, amount ;
            bool         param_change_specified ;

            AnimInfo() :
                param_change_specified{false}
                {}

        } anim_info ;

        ColorInterpolate cig, cil ;
        LinearInterpolate<float> fi ;

        struct {
            Color color ;
            Vec2f dimension ;
            float amount ;
        } property ;

    protected:
        Component(const std::string& str, float x, float y, float w, float h) :
            LookAndFeel{str, x, y, w, h},
            EventHandler{},
            parent{nullptr}, enabled{true},
            bubble_up{false}
        { START; END; }

        bool enabled ;
        Component* parent ;
        std::vector<Component*> children ;
        std::string name ;

    public:
        void add(Component*);
        void setFocus() { this->focused = true; }
        void removeFocus() { this->focused = false; }
        void enable() { enabled = true; }
        void disable() { enabled = false; }
        void stealFocus();

        AnimationID addAnimation(unsigned int, const anim_func&);
        AnimationID addAnimation(unsigned int, AnimCount*);
        bool removeAnimation(const AnimationID&);
        Component& animate(Property);
        Component& on(unsigned int) ;
        Component& to(const Color&) ;
        Component& to(const std::vector<Color>&) ;
        Component& to(const Vec2f&) ;
        Component& to(const std::vector<Vec2f>&) ;
        Component& to(float);
        Component& speed(unsigned int);
        void       pack() ;

        bool isEnabled() const { return enabled; }
        unsigned int getId() const { return EventHandler::id; }

        bool bubble_up ;

        bool operator==(const Component& c)
        {
            return EventHandler::id == c.id ;
        }

        static std::map<unsigned, Component*> all_elements ;

        friend struct Animator ;
        friend class Window ;
    };
}

#endif
