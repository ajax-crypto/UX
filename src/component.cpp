#include "..\include\component.hpp"

namespace ux
{
    void Component::stealFocus()
    {
        for(auto& anim : animations[UXEvents::GainedFocus])
            anim->stop();
        for(auto& anim : animations[UXEvents::LostFocus])
            anim->start();

        for(auto& f : callbacks[UXEvents::LostFocus])
            f(Event{ });

        focused = false ;

        for(auto& c : children)
            c->stealFocus();
    }

    Component& Component::on(unsigned int event)
    {
        anim_info.anim_event = event ;
        return *this ;
    }

    Component& Component::animate(Property param)
    {
        anim_info.anim_param = param ;
        return *this ;
    }

    Component& Component::to(const Color& c)
    {
        property.color = c ;
        anim_info.param_change_specified = true ;
        return *this ;
    }

    Component& Component::to(const Vec2f& v)
    {
        property.dimension = v ;
        anim_info.param_change_specified = true ;
        return *this ;
    }

    Component& Component::to(float f)
    {
        property.amount = f ;
        anim_info.param_change_specified = true ;
        return *this ;
    }

    Component& Component::speed(unsigned int s)
    {
        anim_info.amount = s ;
        return *this ;
    }

    void Component::add(Component *c)
    {
        START;
        c->parent = this;
        children.push_back(c);
        all_elements[c->id] = (c);
        c->imbue_properties();
        END;
    }

    AnimationID Component::addAnimation(unsigned int e, const anim_func& f)
    {
        START ;
        animations[e].push_back(new Animation{f, e});
        LOG("Added " << animations[e].size() << " animations...");
        END;
        return animations[e].back()->getId();
    }

    AnimationID Component::addAnimation(unsigned int e, AnimCount* ac)
    {
        START ;
        animations[e].push_back(ac);
        LOG("Added Custom " << animations[e].size() << " animations...");
        END;
        return animations[e].back()->getId();
    }

    bool Component::removeAnimation(const AnimationID& aid)
    {
        if(aid.id == id)
        {
            if(animations[aid.id][aid.cid] != nullptr)
                delete animations[aid.id][aid.cid] ;
            animations[aid.id][aid.cid] = new Animation{};
            return true ;
        }
        return false ;
    }

    void Component::pack()
    {
        START;
        AnimCount* anim_ob = nullptr ;
        switch(anim_info.anim_param)
        {

        case SHAPE_POSITION:
        case ELEMENT_POSITION:
            anim_ob = new DefaultAnimation<Vec2f, Vec2Interpolate>{
                                id,
                                style,
                                property.dimension,
                                anim_info.anim_param,
                                anim_info.amount
                            };
            break ;

        case SHAPE_COLOR:
        case TEXT_COLOR:
            anim_ob = new DefaultAnimation<Color, ColorInterpolate>{
                                id,
                                style,
                                property.color,
                                anim_info.anim_param,
                                anim_info.amount
                            };
            break ;
        }
        if(anim_ob != nullptr)
            addAnimation(anim_info.anim_event, anim_ob);
        anim_info.param_change_specified = false ;
        END;
    }

    std::map<unsigned int, Component*> Component::all_elements ;
}
