#ifndef __UX_CREATOR_
#define __UX_CREATOR_

#include "button.hpp"
#include "checkbox.hpp"
#include "radio.hpp"
#include "label.hpp"
#include "slider.hpp"
#include "textbox.hpp"
#include "list.hpp"
#include "window.hpp"
#include "uxapp.hpp"

#include <map>

namespace ux
{
    enum
    {
        BUTTON,
        TOGGLE_BUTTON,
        CHECKBOX,
        RADIO_BUTTON,
        SLIDER,
        TEXTBOX,
        PASSWORDBOX,
        LISTBOX
    };

    template <typename UIType>
    class Application
    {
        UXApplication<UIType> application ;
        Window<UIType>        window ;
        std::vector<Component<UIType>*> components ;

    public:
        Application() { add(&window); }
        Application& hasTitlebar(bool has_titlebar) { application.setTitlebar(has_titlebar, ""); return *this; }
        Application& setTitle(const std::string& title) { application.setTitlebar(true, title); return *this; }

        Component<UIType>* operator[](unsigned int index)
        { return components[index]; }

        unsigned int createElement(unsigned int);
    };

    template <typename UIType>
    unsigned int Application<UIType>::createElement(unsigned int type)
    {
        switch(type)
        {
            case BUTTON:
                components.push_back(new Button<UIType>());
            break;

            case TOGGLE_BUTTON:
                components.push_back(new ToggleButton<UIType>());
            break;

            case TEXTBOX:
                components.push_back(new Textbox<UIType>());
            break;

            case PASSWORDBOX:
                components.push_back(new Passwordbox<UIType>());
            break;

            case CHECKBOX:
                components.push_back(new Checkbox<UIType>());
            break;

            case RADIO_BUTTON:
                components.push_back(new Radio<UIType>());
            break;

            case LISTBOX:
                components.push_back(new List<UIType>());
            break;

            case SLIDER:
                components.push_back(new Slider<UIType>());
            break;
        }
        return components.back().getId();
    }


}

#endif // __UX_CREATOR_
