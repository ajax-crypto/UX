#ifndef __UX_RADIOBUTTON_
#define __UX_RADIOBUTTON_

#include "component.hpp"

namespace ux
{
	template <typename UIType>
	class Radio : public Component<UIType>
	{
		typedef typename UIType::Color Color ;
		typedef typename UIType::Window WindowType ;
		typedef typename UIType::Event EventType ;
		typedef typename UIType::CircleShape Shape ;

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

		static ColorPalette<UIType> DefaultColors ;

		Shape container, dot ;
		bool  checked ;

	public:
		Radio(int, int, int);

		void handleEvents(const EventType&);
		void draw(WindowType*);
		void update(int, int);

		bool isChecked() const { return checked; }
		void check() { checked = true; }

	};

	template <typename UIType>
	ColorPalette<UIType> Radio<UIType>::DefaultColors =
		ColorPalette<UIType>{ .base = PropertyStates<Color>{ Color(220, 220, 220), Color(255, 255, 255), Color(255, 255, 255) },
		                      .overlay = PropertyStates<Color>{ Color(40, 40, 40), Color(20, 20, 20), Color(0, 0, 0) } };

	template <typename UIType>
	Radio<UIType>::Radio(int x, int y, int r)
	: Component<UIType>("", x, y, 2 * r, 2 * r), checked{false}
	{
		container.setRadius(r);
		container.setFillColor(DefaultColors.base.inactive);
		container.setPosition(x, y);
		dot.setRadius(r - 4);
		dot.setPosition(x + 4, y + 4);
		dot.setFillColor(DefaultColors.overlay.inactive);

		auto fadeout = [&](bool running) mutable {
		    bool finished = false ;
		    auto base = DefaultColors.base.inactive ;
		    if(running)
            {
                typename UIType::Color color = container.getFillColor();
                if(color.r > base.r &&
                   color.g > base.g &&
                   color.b > base.b)
                {
                    color.r -= 1 ;
                    color.g -= 1 ;
                    color.b -= 1 ;
                }
                finished = color.r <= base.r ;
                container.setFillColor(color);
                GlobalDrawingStates::Redraw = true ;
            }
            return finished ;
		};

		auto fadein = [&](bool running) mutable {
		    bool finished = false ;
		    auto base = DefaultColors.base.active ;
		    if(running)
            {
                typename UIType::Color color = container.getFillColor();
                if(color.r < base.r && color.g < base.g && color.b < base.b)
                {
                    color.r += 1 ;
                    color.g += 1 ;
                    color.b += 1 ;
                }
                finished = color.r >= base.r ;
                container.setFillColor(color);
                GlobalDrawingStates::Redraw = true ;
            }
            return finished ;
		};

		this->animations.push_back(Animation(fadein));
		this->animations.push_back(Animation(fadeout));
	}

	template <typename UIType>
	void Radio<UIType>::update(int x, int y)
	{
		this->setPosition(x, y);
		container.setPosition(x, y);
		dot.setPosition(x + 4, y + 4);
	}

	template <typename UIType>
	void Radio<UIType>::draw(WindowType* w)
	{
		w->draw(container);
		if(checked)
			w->draw(dot);
	}

	template <typename UIType>
	void Radio<UIType>::handleEvents(const EventType& event)
	{
		int actx, acty ;
		switch(event.type)
		{
			case EventType::MouseMoved:
				actx = event.mouseMove.x;
				acty = event.mouseMove.y ;
				//bool prev = focused ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height);
				if(focused)
				{
					//container.setFillColor(DefaultColors.base.active);
					this->animations[0].start();
                    this->animations[1].stop();
					dot.setFillColor(DefaultColors.overlay.active);
					cursor = this->HandCursor ;
				}
				else
				{
					//container.setFillColor(DefaultColors.base.inactive);
					this->animations[1].start();
					this->animations[0].stop();
					dot.setFillColor(DefaultColors.overlay.inactive);
					cursor = this->ArrowCursor ;
				}
				GlobalDrawingStates::Redraw = true ;
			break;

			case EventType::MouseButtonPressed:
				if(focused)
				{
					container.setFillColor(DefaultColors.base.clicked);
					dot.setFillColor(DefaultColors.overlay.clicked);
					GlobalDrawingStates::Redraw = true ;
				}
			break;

			case EventType::MouseButtonReleased:
				if(focused)
				{
					checked = !checked ;
					container.setFillColor(DefaultColors.base.active);
					dot.setFillColor(DefaultColors.overlay.active);
					GlobalDrawingStates::Redraw = true ;
					for(auto& f : callbacks[UXEvents::CheckedStateChange])
						f(event);
				}
			break;
		}
		if(focused)
			for(auto& f : callbacks[event.type])
				f(event);
	}
}

#endif
