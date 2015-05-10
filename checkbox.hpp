#ifndef __UX_CHECK_BOX_
#define __UX_CHECK_BOX_

#include "component.hpp"

namespace ux
{
	template <typename UIType>
	class Checkbox : public Component<UIType>
	{

    protected:
		typedef typename UIType::Color Color ;
		typedef typename UIType::Window WindowType ;
		typedef typename UIType::Event EventType ;

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

		bool checked ;
		typename UIType::RectangleShape slider ;
		PropertyStates<int>    slider_outline ;

		static const ColorPalette<UIType> DefaultColors ;
		static const PropertyStates<int>  DefaultSliderOutline ;

	public:
		Checkbox(int, int, int, int) ;

		void handleEvents(EventType const&);
		void draw(WindowType*);
		void update(int, int);
		bool isChecked() const { return checked; }
	};

	template <typename UIType> const
	ColorPalette<UIType> Checkbox<UIType>::DefaultColors =
		ColorPalette<UIType>{ .base = PropertyStates<Color>{ Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0) },
							  .overlay = PropertyStates<Color>{ Color(150, 150, 150), Color(20, 20, 20), Color(20, 20, 20) },
		                      .outline = PropertyStates<Color>{ Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255) } };

	template <typename UIType> const
	PropertyStates<int> Checkbox<UIType>::DefaultSliderOutline = { 2, 2, 2 };

	template <typename UIType>
	Checkbox<UIType>::Checkbox(int x, int y, int w, int h)
	: Component<UIType>("", x, y, w, h), checked{false}
	{
		this->setOutlineThickness(DefaultSliderOutline);
		this->setColorPalette(DefaultColors);
		this->init();
		slider.setFillColor(palette.overlay.inactive);
		slider.setSize((w / 3), h + 4);
		slider.setPosition(x, y - 2);
	}

	template <typename UIType>
	void Checkbox<UIType>::draw(WindowType* w)
	{
		w->draw(shape);
		w->draw(slider);
	}

	template <typename UIType>
	void Checkbox<UIType>::update(int _x, int _y)
	{
		x = _x ;
		y = _y ;
		shape.setPosition(_x, _y);
		slider.setPosition(_x, _y - 2);
	}

	template <typename UIType>
	void Checkbox<UIType>::handleEvents(EventType const& event)
	{
		int actx, acty ;
		switch(event.type)
		{
			case EventType::MouseMoved:
				actx = event.mouseMove.x ;
				acty = event.mouseMove.y ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height) ;
			break;

			case EventType::MouseButtonReleased:
				if(focused)
				{
					auto tocheck = event.mouseButton.x ;
					auto pchecked = checked ;
					if(checked && (tocheck < (x + width/2)))
					{
						slider.setPosition(x, y - 2);
						slider.setFillColor(palette.overlay.inactive);
						this->setInactiveColor();
						checked = false ;
					}
					else
					if(!checked && (tocheck >= (x + width/2)))
					{
						slider.setPosition(x + width - slider.getSize().x, y - 2);
						slider.setFillColor(palette.overlay.active);
						this->setActiveColor();
						checked = true ;
					}
					if(pchecked != checked)
						for(auto& f : callbacks[UXEvents::CheckedStateChange])
							f(event);
					GlobalDrawingStates::Redraw = true ;
				}
			break;
		}
		if(focused)
			for(auto& f : callbacks[event.type])
				f(event);
	}

}

#endif
