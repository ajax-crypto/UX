#ifndef __UX_ANIMATOR_
#define __UX_ANIMATOR_

#include <chrono>
#include <thread>

#include "typedefs.hpp"
#include "style.hpp"

namespace ux
{
    class Window;

    class AnimationID
    {
        unsigned int m_cid ;
        unsigned int m_id ;

    public:
        AnimationID(unsigned int a, unsigned int b) :
            m_id{a}, m_cid{b} {}

        bool operator==(const AnimationID& a)
        {
            return (m_cid == a.m_cid) && (m_id == a.m_id) ;
        }

        unsigned int getElementId() const { return m_cid; }

        friend class Animation ;
        friend class Component ;
        template <typename, typename> friend class DefaultAnimation ;
    };

    class AnimCount
    {
    protected:
        static unsigned int seed ;
        AnimationID m_id ;

    public:
        bool m_running, m_finished ;
        unsigned int m_duration ;

        AnimCount(unsigned int eid)
        : m_id{++seed, eid}, m_running{false}, m_finished{true} {}
        virtual ~AnimCount() {}
        virtual void operator()() = 0 ;

        AnimationID getId() const { return m_id; }

        virtual void start() {
            //LOG("Starting animation...");
            m_running = true;
            GlobalDrawingStates::Redraw = true ;
        }
        void stop() { LOG("Stopping animation..."); m_running = false; }

    };

    class Animation : public AnimCount
    {
        anim_func m_anim_impl ;

    public:
        static anim_func NO_ANIMATION ;
        Animation(const anim_func& f, unsigned int element_id)
        :   AnimCount{element_id},
            m_anim_impl{f} {}
        Animation() : AnimCount{0u}, m_anim_impl{NO_ANIMATION} {}

        void operator()();
    };

    template <typename Prop,
              typename InterpolationRule>
    class DefaultAnimation : public AnimCount
    {
        InterpolationRule m_rule ;

        StyleData& m_style ;
        Prop m_end, m_str ;
        Property m_property_name ;
        unsigned int m_speed ;

    public:
        DefaultAnimation(unsigned int element_id,
                         StyleData& ptr,
                         Prop const& e,
                         Property pid,
                         float s)
        :   AnimCount{element_id},
            m_style(ptr), m_end{e}, m_speed{s},
            m_property_name{pid}
        {}
        DefaultAnimation() : AnimCount{0u, 0u} {}

        void operator()();
        void start();

    };

    template <typename Prop,
              typename InterpolationRule>
    void DefaultAnimation<Prop, InterpolationRule>::operator()()
    {
        //START ;
        //LOG(property << " -->> " << end);
        if(m_running) {
            m_style(m_property_name, m_rule.forward());
            m_finished = m_rule.isFinished();
        }
        if(m_finished)
            m_rule.reset();
        m_running = !m_finished ;
        //END;
    }

    template <typename Prop,
              typename InterpolationRule>
    void DefaultAnimation<Prop, InterpolationRule>::start()
    {
        //START;
        m_style.extract(m_property_name, m_str);
        m_rule = InterpolationRule{m_end, m_str, m_speed};
        //LOG("From : " << property << " Upto " << end);
        AnimCount::start();
        //END;
    }

}

#endif // __UX_ANIMATOR__
