#ifndef __UX_SLIDER_
#define __UX_SLIDER_

#include "checkbox.hpp"

namespace ux
{
    template <typename UIType>
    class Slider : public Checkbox<UIType>
    {

        typedef typename UIType::Event EventType ;
        typedef typename UIType::Window WindowType ;

        using UIElement<UIType>::shape ;
		using UIElement<UIType>::width ;
		using UIElement<UIType>::height ;
		using UIElement<UIType>::x ;
		using UIElement<UIType>::y ;
		using UIElement<UIType>::cursor ;
		using UIElement<UIType>::text ;
		using UIElement<UIType>::palette ;
		using UIElement<UIType>::outline ;

		using EventHandler<UIType>::focused ;
		using EventHandler<UIType>::callbacks ;
		using EventHandler<UIType>::id ;

		using Checkbox<UIType>::slider ;

		typename UIType::RectangleShape filled ;
		bool          clicked ;
		float         value, high, low ;

		void          updateSlide(int, int);

    public:
        Slider(int, int, int, int, float, float);

        void handleEvents(const EventType&);
        void draw(WindowType*);
        void update(int _x, int _y) { Checkbox<UIType>::update(_x, _y); filled.setPosition(_x, _y); }

        float getValue() const { return value; }
    };

    template <typename UIType>
    Slider<UIType>::Slider(int x, int y, int w, int h, float a, float b)
    : Checkbox<UIType>(x, y, w, h),
    low{a}, high{b}, value{low}, clicked{false}
    {
        filled.setFillColor(this->DefaultColors.overlay.inactive);
        filled.setSize(0, h);
        filled.setPosition(x, y);
        slider.setSize(w/10, h + 4);
        slider.setPosition(x - (w/20), y - 2);
    }

    template <typename UIType>
    void Slider<UIType>::draw(WindowType* w)
    {
        w->draw(shape);
        w->draw(filled);
        if(focused || clicked)
            w->draw(slider);
    }

    template <typename UIType>
    void Slider<UIType>::updateSlide(int actx, int acty)
    {
        auto _x = (actx < x) ? x : actx ;
        _x = (_x > (x + width)) ? x + width : _x ;
        auto tofill = (actx - x) > 0 ? actx - x : 0 ;
        tofill = (tofill > width) ? width : tofill ;
        filled.setSize(tofill, height);
        slider.setPosition(_x - (slider.getSize().x/2), y - 2);
    }

    template <typename UIType>
    void Slider<UIType>::handleEvents(const EventType& event)
    {
        int actx, acty, prev_val ;
        switch(event.type)
        {
            case EventType::MouseMoved:
				actx = event.mouseMove.x ;
				acty = event.mouseMove.y ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height);
				if(clicked || focused)
                {
                    this->setActiveColor();
                    cursor = this->HandCursor ;
                    if(clicked)
                    {
                        prev_val = value ;
                        value = ((high - low)/width * (actx - x));
                        if(actx > (x + width))
                            value = high ;
                        else if(actx < x)
                            value = low ;
                        updateSlide(actx, acty);
                        if(value != prev_val)
                            for(auto& f : callbacks[UXEvents::SliderValueChanged])
                                f(event);
                    }
                }
                else
                {
                    this->setInactiveColor();
                }
			break;

			case EventType::MouseButtonPressed:
                actx = event.mouseButton.x ;
				acty = event.mouseButton.y ;
				{
				auto m1 = slider.getPosition();
				auto m2 = slider.getSize();
				clicked = GlobalDrawingStates::IsWithin(actx, acty, m1.x, m1.y, m2.x, m2.y);
				}
                this->setClickedColor();
            break;

            case EventType::MouseButtonReleased:
                prev_val = value ;
                if(focused && !clicked)
                {
                    actx = event.mouseButton.x ;
                    acty = event.mouseButton.y ;
                    updateSlide(actx, acty);
                    value = ((high - low)/width * (actx - x));
                    if(value != prev_val)
                        for(auto& f : callbacks[UXEvents::SliderValueChanged])
                            f(event);
                }
                this->setInactiveColor();
                clicked = false ;
            break;
        }

        if(focused)
            for(auto& f : callbacks[event.type])
                f(event);
    }
}

#endif // __UX_SLIDER_
