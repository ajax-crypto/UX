#ifndef __UX_SFML_
#define __UX_SFML_

#include "basic_element.hpp"
#include "window.hpp"
#include "layout.hpp"
#include "uxapp.hpp"

namespace sux
{
    typedef ux::Button                        SButton ;
    typedef ux::ToggleButton                  SToggleButton;
    typedef ux::Window                        SWindow ;
    typedef ux::FlexBox                       SBox ;
    typedef ux::Label                         SLabel ;

    typedef ux::Color Color ;
    typedef ux::Event Event ;
    typedef ux::UXEvents UXEvents ;

    class SUXApp : public ux::UXApplication
    {

    public:
        SUXApp(const std::string&, int, int, bool);

        int run();
    };

    SUXApp::SUXApp(const std::string& str, int w, int h, bool title = true)
    : ux::UXApplication()
    {
        sf::ContextSettings settings ;
        settings.antialiasingLevel = 8;
        setTitlebar(title, str);
        if(title)
            target = new ux::UXRenderWindow(sf::VideoMode(w, h), str, sf::Style::Default, settings);
        else
            target = new ux::UXRenderWindow(sf::VideoMode(w, h), "", sf::Style::None, settings);
        view.setCenter(ux::Vec2f(w/2, h/2));
        view.setSize(ux::Vec2f(w, h));
        view.setViewport(ux::FRect(0.0f, 0.0f, 1.0f, 1.0f));
        target->setView(this->view);
    }

    int SUXApp::run()
    {
        return ux::UXApplication::run();
    }

}

#endif
