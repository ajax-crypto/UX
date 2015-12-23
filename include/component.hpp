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
            Property     m_anim_param ;
            unsigned int m_anim_event, m_amount ;
            bool         m_param_change_specified ;

            AnimInfo() :
                m_param_change_specified{false}
                {}

        } m_anim_info ;

        std::vector<AnimInfo> m_anim_events ;
        ColorInterpolate m_cig, m_cil ;
        LinearInterpolate<float> m_fi ;

        struct {
            Color m_color ;
            Vec2f m_dimension ;
            float m_amount ;
        } m_property ;

    protected:
        Component(const std::string& str, float x, float y, float w, float h) :
            LookAndFeel{str, x, y, w, h},
            EventHandler{},
            m_parent{nullptr}, m_enabled{true},
            m_bubble_up{false}
        { START; END; }

        bool m_enabled ;
        Component* m_parent ;
        std::vector<Component*> m_children ;
        std::string m_name ;

    public:
        void add(Component*);
        void setFocus() { m_focused = true; }
        void removeFocus() { m_focused = false; }
        void enable() { m_enabled = true; }
        void disable() { m_enabled = false; }
        void stealFocus();
        void operator+=(Component&);

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
        Component& then();
        void       pack() ;
        void       imbue_properties();

        Component& margin(float);
		Component& margin(const Sides&);
		Component& padding(float);
        Component& padding(const Sides&);
        Component& content(const Content&);
        Component& text(const std::string&);
        Component& text(const std::string&, const Color&);
        Component& text(const std::string&, const Color&, int);
        Component& align(Alignment);
        Component& border(float, const Color&);
        Component& border(const Sides&, const Color&);
        Component& background(const Color&);
        Component& background(uint64_t);
        Component& zindex(int);
        Component& show();
        Component& hide();
        Component& autosize();
        Component& shadow(const Shadow&);

        bool isEnabled() const { return m_enabled; }
        unsigned int getId() const { return EventHandler::m_id; }

        bool m_bubble_up ;

        bool operator==(const Component& c)
        {
            return EventHandler::m_id == c.m_id ;
        }

        static std::map<unsigned, Component*> all_elements ;

        friend struct Animator ;
        friend class  Window ;
    };
}

#endif
