#ifndef LAYOUT_HPP_INCLUDED
#define LAYOUT_HPP_INCLUDED

#include <vector>
#include <deque>
#include <map>
#include <tuple>

#include "component.hpp"

namespace ux
{
    class Window;

    typedef std::tuple<unsigned, unsigned> pair ;

    struct Coordinates
    {
        unsigned int m_startx, m_endx ;
        unsigned int m_starty, m_endy ;

        Coordinates(const pair& start, const pair& end)
            : m_startx{std::get<0>(start)}, m_starty{std::get<1>(start)},
              m_endx{std::get<0>(end)}, m_endy{std::get<1>(end)}
        {}
    };

    class FlexBox : public Component
    {
    protected:
        std::vector<std::vector<Component*>> m_boxes ;
        std::deque<Coordinates> m_regions ;
        unsigned int m_row, m_col, m_id ;
        unsigned int m_prev_region, m_current_region;
        bool m_custom_region ;

    public:
        FlexBox(unsigned int, unsigned int, float, float, float, float);

        void draw(Window_Impl*);
        void handleEvents(Event const&);
        void add(unsigned int, Component*);
        void update(int, int) {}

        unsigned int createRegion(const pair&, const pair&);
        unsigned int merge(unsigned int, unsigned int);
        void pack();

        float m_x, m_y ;
        float m_height, m_width ;

        enum { ROWS, COLS  };
    };

}

#endif // LAYOUT_HPP_INCLUDED
