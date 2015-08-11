#include "../include/layout.hpp"

namespace ux
{
    FlexBox::FlexBox(unsigned int r, unsigned int c, float _x, float _y, float w, float h)
    :   row{r}, col{c}, x{_x}, y{_y}, width{w/c}, height{h/r}, id{0}, custom_region{false},
        Component{"", x, y, w, h}, current_region{0u}, prev_region{0u}
    {
        START;
        for(auto i = 0u; i < row; ++i)
            for(auto j = 0u; j < col; ++j)
                regions.push_back(Coordinates{pair{i, j}, pair{i+1, j+1}});
        boxes = std::vector<std::vector<Component*>>{ row * col, std::vector<Component*>{}};
        id = row * col ;
        LOG("Regions : " << regions.size());
        END;
    }

    unsigned int FlexBox::createRegion(const pair& start, const pair& end)
    {
        START ;
        if(!custom_region)
        {
            regions.clear();
            boxes.clear();
            id = 0u ;
        }
        custom_region = true ;
        if(std::get<0>(start) >= 0u && std::get<1>(start) >= 0u &&
           std::get<0>(end) < row && std::get<1>(end) < col)
        {
            ASSERT(std::get<0>(start) < std::get<0>(end), "Invalid Region");
            ASSERT(std::get<1>(start) < std::get<1>(end), "Invalid Region");
            regions.push_back(Coordinates{start, end});
            ++id ;
        }
        END ;
        return id;
    }

    unsigned int FlexBox::merge(unsigned int what, unsigned int which)
    {
        unsigned int ret = 0u;
        unsigned int i, j ;
        if(which >= row || which >= col)
            return 0u;
        switch(what)
        {
        case COLS:
            ret = which * col ;
            i = which ;
            j = 0 ;
            regions.erase(ret + regions.begin(), ret + regions.begin() + col);
            regions.insert(ret + regions.begin(), Coordinates{pair{i, j}, pair{i+1, j+col}});
        break;
        }
        id = regions.size();
        return ret ;
    }

    void FlexBox::add(unsigned int region_id, Component* component)
    {
        START;
        ASSERT(region_id > id, "Invalid Region");
        LOG("Adding to region : #" << region_id << " regions : " << boxes.size());
        boxes[region_id].push_back(component);
        Component::add(component);
        END;
    }

    void FlexBox::pack()
    {
        START ;
        for(auto i = 0u; i < regions.size(); ++i)
        {
            float totalw = static_cast<float>(regions[i].endy - regions[i].starty) * width ,
                  totalh = static_cast<float>(regions[i].endx - regions[i].startx) * height ,
                  starty = static_cast<float>(regions[i].startx) * height ,
                  startx = static_cast<float>(regions[i].starty) * width ;
#ifdef UX_LAYOUT_DEBUG
            LOG("Startx : " << startx << " Starty : " << starty);
            LOG("Width : " << totalh << " Height : " << totalh);
#endif
            if(boxes[i].size() > 0)
            {
                (*boxes[i][0]).style.position = Vec2f{startx + x, starty + y};
                switch((*boxes[i][0]).style.shape.type)
                {
                    case RECTANGLE:
                        (*boxes[i][0]).style.shape.rect.height = totalh ;
                        (*boxes[i][0]).style.shape.rect.width = totalw ;
                    break;

                    default: break ;
                }
                (*boxes[i][0]).imbue_properties();
            }
        }
        END ;
    }

    void FlexBox::draw(Window_Impl* window)
    {
        //START;
        for(auto c : children)
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
        for(i = 0u; i < regions.size(); ++i)
        {
            float w = static_cast<float>(regions[i].endy - regions[i].starty) * width ,
                  h = static_cast<float>(regions[i].endx - regions[i].startx) * height ,
                  starty = static_cast<float>(regions[i].startx) * height ,
                  startx = static_cast<float>(regions[i].starty) * width ;

            if(GlobalDrawingStates::IsRectWithin(ex, ey, startx + x, starty + y, w, h))
            {
                current_region = i ;
                boxes[current_region][0]->handleEvents(event);
                if(current_region != prev_region &&
                   event.type == Event::MouseMoved &&
                   prev_region < id)
                    boxes[prev_region][0]->stealFocus();
                break ;
            }
        }
        if(i >= regions.size() &&
           event.type == Event::MouseMoved &&
           prev_region < id)
        {
            current_region = i ;
            boxes[prev_region][0]->stealFocus();
        }
        prev_region = current_region ;
#ifdef EVENT_DEBUG
        END ;
#endif
    }
}
