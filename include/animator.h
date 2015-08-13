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
        unsigned int cid ;
        unsigned int id ;

    public:
        AnimationID(unsigned int a, unsigned int b) :
            id{a}, cid{b} {}

        bool operator==(const AnimationID& a)
        {
            return (cid == a.cid) && (id == a.id) ;
        }

        unsigned int getElementId() const { return cid; }

        friend class Animation ;
        friend class Component ;
        template <typename, typename> friend class DefaultAnimation ;
    };

    class AnimCount
    {
    protected:
        static unsigned int seed ;
        AnimationID id ;

    public:
        bool running, finished ;
        unsigned int duration ;

        AnimCount(unsigned int eid)
        : id{++seed, eid}, running{false}, finished{true} {}
        virtual ~AnimCount() {}
        virtual void operator()() = 0 ;

        AnimationID getId() const { return id; }

        virtual void start() {
            //LOG("Starting animation...");
            running = true;
            GlobalDrawingStates::Redraw = true ;
        }
        void stop() { LOG("Stopping animation..."); running = false; }

    };

    class Animation : public AnimCount
    {
        anim_func anim_impl ;

    public:
        static anim_func NO_ANIMATION ;
        Animation(const anim_func& f, unsigned int element_id)
        :   AnimCount{element_id},
            anim_impl{f} {}
        Animation() : AnimCount{0u}, anim_impl{NO_ANIMATION} {}

        void operator()();
    };

    template <typename Prop,
              typename InterpolationRule>
    class DefaultAnimation : public AnimCount
    {
        InterpolationRule rule ;

        StyleData& style ;
        Prop end, str ;
        Property property_name ;
        unsigned int speed ;

    public:
        DefaultAnimation(unsigned int element_id,
                         StyleData& ptr,
                         Prop const& e,
                         Property pid,
                         float s)
        :   AnimCount{element_id},
            style(ptr), end{e}, speed{s},
            property_name{pid}
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
        if(running) {
            style(property_name, rule.forward());
            finished = rule.isFinished();
        }
        if(finished)
            rule.reset();
        running = !finished ;
        //Component::all_elements[id.cid]->apply_current_changes();
        //END;
    }

    template <typename Prop,
              typename InterpolationRule>
    void DefaultAnimation<Prop, InterpolationRule>::start()
    {
        //START;
        style.extract(property_name, str);
        rule = InterpolationRule{end, str, speed};
        //LOG("From : " << property << " Upto " << end);
        AnimCount::start();
        //END;
    }

}

#endif // __UX_ANIMATOR__
