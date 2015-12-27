#include "../include/component.hpp"

namespace ux
{

    void Component::add(Component *c)
    {
        START;
        add(c, true);
        END;
    }

    void Component::add(Component *c, bool should_imbue)
    {
        START;
        c->m_parent = this;
        m_children.push_back(c);
        all_elements[c->m_id] = (c);
        drawables[c->m_style.m_graphics.m_z].push_back(c);
        if(should_imbue)
            c->imbue();
        END;
    }

    void Component::operator+=(Component& component)
    {
        add(&component);
    }

    void Component::stealFocus()
    {
        for(auto& anim : m_animations[UXEvents::GainedFocus])
            anim->stop();
        for(auto& anim : m_animations[UXEvents::LostFocus])
            anim->start();

        for(auto& f : m_callbacks[UXEvents::LostFocus])
            f(Event{ });

        m_focused = false ;

        for(auto& c : m_children)
            c->stealFocus();
    }

    Component& Component::on(unsigned int event)
    {
        m_anim_info.m_anim_event = event ;
        return *this ;
    }

    Component& Component::animate(Property param)
    {
        m_anim_info.m_anim_param = param ;
        return *this ;
    }

    Component& Component::to(const Color& c)
    {
        m_property.m_color = c ;
        //anim_info.param_change_specified = true ;
        return *this ;
    }

    Component& Component::to(const Vec2f& v)
    {
        m_property.m_dimension = v ;
        //anim_info.param_change_specified = true ;
        return *this ;
    }

    Component& Component::to(float f)
    {
        m_property.m_amount = f ;
        //anim_info.param_change_specified = true ;
        return *this ;
    }

    Component& Component::speed(unsigned int s)
    {
        m_anim_info.m_amount = s ;
        return *this ;
    }

    Component& Component::then()
    {
        m_anim_events.push_back(m_anim_info);
    }

    AnimationID Component::addAnimation(unsigned int e, const anim_func& f)
    {
        START ;
        m_animations[e].push_back(new Animation{f, e});
        LOG("Added " << m_animations[e].size() << " animation(s)...");
        END;
        return m_animations[e].back()->getId();
    }

    AnimationID Component::addAnimation(unsigned int e, AnimCount* ac)
    {
        START ;
        m_animations[e].push_back(ac);
        LOG("Added Custom " << m_animations[e].size() << " animation(s)...");
        END;
        return m_animations[e].back()->getId();
    }

    bool Component::removeAnimation(const AnimationID& aid)
    {
        if(aid.m_id == m_id)
        {
            if(m_animations[aid.m_id][aid.m_cid] != nullptr)
                delete m_animations[aid.m_id][aid.m_cid] ;
            m_animations[aid.m_id][aid.m_cid] = new Animation{};
            return true ;
        }
        return false ;
    }

    void Component::imbue()
    {
        START;
        /*if(updatableChange())
            for(auto& c : m_children)
                c->update(m_style);*/
        apply_current_changes();
        END;
    }

    void Component::pack()
    {
        START;
        AnimCount* anim_ob = nullptr ;
        switch(m_anim_info.m_anim_param)
        {

        case SHAPE_POSITION:
        case ELEMENT_POSITION:
            anim_ob = new DefaultAnimation<Vec2f, Vec2Interpolate>{
                                m_id,
                                m_style,
                                m_property.m_dimension,
                                m_anim_info.m_anim_param,
                                m_anim_info.m_amount
                            };
            break ;

        case SHAPE_COLOR:
        case TEXT_COLOR:
            anim_ob = new DefaultAnimation<Color, ColorInterpolate>{
                                m_id,
                                m_style,
                                m_property.m_color,
                                m_anim_info.m_anim_param,
                                m_anim_info.m_amount
                            };
            break ;
        }
        if(anim_ob != nullptr)
            addAnimation(m_anim_info.m_anim_event, anim_ob);
        //anim_info.param_change_specified = false ;
        END;
    }

    Component& Component::border(const Sides& sides, const Color& color)
    {
        m_style.m_border.m_left = sides.m_left ;
        m_style.m_border.m_right = sides.m_right ;
        m_style.m_border.m_top = sides.m_top ;
        m_style.m_border.m_bottom = sides.m_bottom ;
        m_style.m_border.m_color = color ;
        return *this;
    }

    Component& Component::text(const std::string& text)
    {
        m_style.m_content.m_text = text;
        m_style.m_content.m_auto_size = true;
        return *this;
    }

    Component& Component::text(const std::string& text, const Color& color)
    {
        m_style.m_content.m_text = text;
        m_style.m_content.m_color = color;
        m_style.m_content.m_auto_size = true;
        return *this;
    }

    Component& Component::text(const std::string& text, const Color& color, int fontsize)
    {
        m_style.m_content.m_text = text;
        m_style.m_content.m_color = color;
        m_style.m_content.m_font_size = fontsize;
        m_style.m_content.m_auto_size = false;
        return *this;
    }

    Component& Component::align(Alignment alignment)
    {
        m_style.m_content.m_alignment = alignment;
        return *this;
    }

    Component& Component::border(float amount, const Color& color)
    {
        m_style.m_border.m_bottom = m_style.m_border.m_top = amount;
        m_style.m_border.m_left = m_style.m_border.m_right = amount;
        m_style.m_border.m_color = color;
        return *this;
    }

    Component& Component::margin(float amount)
    {
        m_style.m_margin.m_left = m_style.m_margin.m_right = amount;
        m_style.m_margin.m_top = m_style.m_margin.m_bottom = amount;
        return *this;
    }

    Component& Component::padding(float amount)
    {
        m_style.m_padding.m_left = m_style.m_padding.m_right = amount;
        m_style.m_padding.m_top = m_style.m_padding.m_bottom = amount;
        return *this;
    }

    Component& Component::background(const Color& color)
    {
        m_style.m_shape.m_color = color;
    }

    Component& Component::show()
    {
        m_style.m_visible = true;
        return *this;
    }

    Component& Component::hide()
    {
        m_style.m_visible = false;
        return *this;
    }

    Component& Component::zindex(int z)
    {
        m_style.m_graphics.m_z = z;
        return *this;
    }

    Component& Component::autosize()
    {
        m_style.m_content.m_auto_size = true;
        return *this;
    }

    std::map<int, std::vector<Component*>> Component::drawables ;
    std::map<unsigned int, Component*> Component::all_elements ;
}
