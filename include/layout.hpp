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
        unsigned int startx, endx ;
        unsigned int starty, endy ;

        Coordinates(const pair& start, const pair& end)
            : startx{std::get<0>(start)}, starty{std::get<1>(start)},
              endx{std::get<0>(end)}, endy{std::get<1>(end)}
        {}
    };

    class FlexBox : public Component
    {
    protected:
        std::vector<std::vector<Component*>> boxes ;
        std::deque<Coordinates> regions ;
        unsigned int row, col, id ;
        unsigned int prev_region, current_region;
        bool custom_region ;

    public:
        FlexBox(unsigned int, unsigned int, float, float, float, float);

        void draw(Window_Impl*);
        void handleEvents(Event const&);
        void add(unsigned int, Component*);
        void update(int, int) {}

        unsigned int createRegion(const pair&, const pair&);
        unsigned int merge(unsigned int, unsigned int);
        void pack();

        float x, y ;
        float height, width ;

        enum { ROWS, COLS  };
    };

}

#endif // LAYOUT_HPP_INCLUDED
