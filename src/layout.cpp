#include "../include/layout.hpp"

namespace ux
{
    FlexBox::FlexBox(unsigned int r, unsigned int c, float x, float y, float w, float h)
    :   m_row{r}, m_col{c}, m_x{x}, m_y{y}, m_width{w/c}, m_height{h/r}, m_id{0}, m_custom_region{false},
        Component{"", x, y, w, h}, m_current_region{0u}, m_prev_region{0u}
    {
        START;
        for(auto i = 0u; i < m_row; ++i)
            for(auto j = 0u; j < m_col; ++j)
                m_regions.push_back(Coordinates{pair{i, j}, pair{i+1, j+1}});
        m_boxes = std::vector<std::vector<Component*>>{ m_row * m_col, std::vector<Component*>{}};
        m_id = m_row * m_col ;
        LOG("Regions : " << m_regions.size());
        END;
    }

    unsigned int FlexBox::createRegion(const pair& start, const pair& end)
    {
        START ;
        if(!m_custom_region)
        {
            m_regions.clear();
            m_boxes.clear();
            m_id = 0u ;
        }
        m_custom_region = true ;
        if(std::get<0>(start) >= 0u && std::get<1>(start) >= 0u &&
           std::get<0>(end) < m_row && std::get<1>(end) < m_col)
        {
            ASSERT(std::get<0>(start) < std::get<0>(end), "Invalid Region");
            ASSERT(std::get<1>(start) < std::get<1>(end), "Invalid Region");
            m_regions.push_back(Coordinates{start, end});
            ++m_id ;
        }
        END ;
        return m_id;
    }

    unsigned int FlexBox::merge(unsigned int what, unsigned int which)
    {
        unsigned int ret = 0u;
        unsigned int i, j ;
        if(which >= m_row || which >= m_col)
            return 0u;
        switch(what)
        {
        case COLS:
            ret = which * m_col ;
            i = which ;
            j = 0 ;
            m_regions.erase(ret + m_regions.begin(), ret + m_regions.begin() + m_col);
            m_regions.insert(ret + m_regions.begin(), Coordinates{pair{i, j}, pair{i+1, j+m_col}});
        break;
        }
        m_id = m_regions.size();
        return ret ;
    }

    void FlexBox::add(unsigned int region_id, Component* component)
    {
        START;
        ASSERT(region_id > m_id, "Invalid Region");
        LOG("Adding to region : #" << region_id << " regions : " << m_boxes.size());
        m_boxes[region_id].push_back(component);
        Component::add(component);
        END;
    }

    void FlexBox::pack()
    {
        START ;
        for(auto i = 0u; i < m_regions.size(); ++i)
        {
            float totalw = static_cast<float>(m_regions[i].m_endy - m_regions[i].m_starty) * m_width ,
                  totalh = static_cast<float>(m_regions[i].m_endx - m_regions[i].m_startx) * m_height ,
                  starty = static_cast<float>(m_regions[i].m_startx) * m_height ,
                  startx = static_cast<float>(m_regions[i].m_starty) * m_width ;
#ifdef UX_LAYOUT_DEBUG
            LOG("Startx : " << startx << " Starty : " << starty);
            LOG("Width : " << totalh << " Height : " << totalh);
#endif
            if(m_boxes[i].size() > 0)
            {
                (*m_boxes[i][0]).m_style.m_position = Vec2f{startx + m_x, starty + m_y};
                switch((*m_boxes[i][0]).m_style.m_shape.m_type)
                {
                    case RECTANGLE:
                        (*m_boxes[i][0]).m_style.m_shape.m_rect.m_height = totalh ;
                        (*m_boxes[i][0]).m_style.m_shape.m_rect.m_width = totalw ;
                    break;

                    default: break ;
                }
                (*m_boxes[i][0]).imbue_properties();
            }
        }
        END ;
    }

    void FlexBox::draw(Window_Impl* window)
    {
        //START;
        for(auto c : m_children)
            c->draw(window);
        //END;
    }

    void FlexBox::handleEvents(Event const& event)
    {
#ifdef EVENT_DEBUG
        START;
#endif
        float ex, ey ;
        auto i = 0u ;
        switch(event.type)
        {
            case Event::MouseMoved:
                ex = event.mouseMove.x, ey = event.mouseMove.y ;
            break ;

            case Event::MouseButtonReleased:
            case Event::MouseButtonPressed:
                ex = event.mouseButton.x, ey = event.mouseButton.y ;
            break ;
        }
        for(i = 0u; i < m_regions.size(); ++i)
        {
            float w = static_cast<float>(m_regions[i].m_endy - m_regions[i].m_starty) * m_width ,
                  h = static_cast<float>(m_regions[i].m_endx - m_regions[i].m_startx) * m_height ,
                  starty = static_cast<float>(m_regions[i].m_startx) * m_height ,
                  startx = static_cast<float>(m_regions[i].m_starty) * m_width ;

            if(GlobalDrawingStates::IsRectWithin(ex, ey, startx + m_x, starty + m_y, w, h))
            {
                m_current_region = i ;
                m_boxes[m_current_region][0]->handleEvents(event);
                if(m_current_region != m_prev_region &&
                   event.type == Event::MouseMoved &&
                   m_prev_region < m_id)
                    m_boxes[m_prev_region][0]->stealFocus();
                break ;
            }
        }
        if(i >= m_regions.size() &&
           event.type == Event::MouseMoved &&
           m_prev_region < m_id)
        {
            m_current_region = i ;
            m_boxes[m_prev_region][0]->stealFocus();
        }
        m_prev_region = m_current_region ;
#ifdef EVENT_DEBUG
        END ;
#endif
    }
}
