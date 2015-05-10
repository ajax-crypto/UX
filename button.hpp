#ifndef __UX_BUTTON_
#define __UX_BUTTON_

#include "component.hpp"

namespace ux
{

	template <typename UIType>
	class Button :
	public Component<UIType>
	{

		typedef typename UIType::Color Color ;
		typedef typename UIType::Window WindowType ;
		typedef typename UIType::Event EventType ;

	protected:
		using UIElement<UIType>::shape ;
		using UIElement<UIType>::text ;
		using UIElement<UIType>::width ;
		using UIElement<UIType>::height ;
		using UIElement<UIType>::x ;
		using UIElement<UIType>::y ;
		using UIElement<UIType>::cursor ;
		using UIElement<UIType>::palette ;
		using UIElement<UIType>::outline ;

		using EventHandler<UIType>::focused ;
		using EventHandler<UIType>::callbacks ;
		using EventHandler<UIType>::id ;

		bool filled ;

	public:
		Button(const std::string&, int, int, int, int);
		Button(const std::string& str, const typename UIType::Vec2i& pos,
                                       const typename UIType::Vec2i& dim):
		    Button(str, pos.x, pos.y, dim.x, dim.y) {}
		Button() : Component<UIType>("", 0, 0, 0, 0) {}

		void handleEvents(EventType const&);
		void draw(WindowType*);
		void update(int, int);

		void makeButtonFilled(const PropertyStates<Color>&, const PropertyStates<Color>&);

	};

	template <typename UIType>
	Button<UIType>::Button(const std::string& t, int x, int y, int w, int h) :
	Component<UIType>(t, x, y, w, h)
	{
		filled = false ;
		shape.setOutlineThickness(outline.inactive);
		auto metrics = text.getGlobalBounds();
		text.setPosition(x + metrics.width/2, y);
		this->setInactiveColor();

		auto fadeout = [&](bool running) mutable {
		    bool finished = false ;
		    if(running)
            {
                typename UIType::Color color = shape.getFillColor();
                if((int)color.r > 39)
                   color.r -= 1 ;
                finished = (int)color.r == 39 ;
                shape.setFillColor(color);
                GlobalDrawingStates::Redraw = true ;
                std::cout << "\n[button] fadeout animation has finished ? " << std::boolalpha << finished ;
            }
            return finished ;
		};

		auto fadein = [&](bool running) mutable {
		    bool finished = false ;
		    if(running)
            {
                typename UIType::Color color = shape.getFillColor();
                if((int)color.g < 100)
                    color.g += 1 ;
                finished = (int)color.g == 100 ;
                shape.setFillColor(color);
                GlobalDrawingStates::Redraw = true ;
                std::cout << "\n[button] R = " << (int)color.r << " has finished ? " << std::boolalpha << finished;
            }
            return finished ;
		};

		this->animations.push_back(Animation(fadein));
		this->animations.push_back(Animation(fadeout));
	}

	template <typename UIType>
	void Button<UIType>::draw(WindowType* w)
	{
		Cursor c(cursor);
		c.set(w->getSystemHandle());
		w->draw(shape);
		w->draw(text);
	}

	template <typename UIType>
	void Button<UIType>::update(int _x, int _y)
	{
		x = _x ;
		y = _y ;
		shape.setPosition(x, y);
		auto metrics = text.getGlobalBounds();
		text.setPosition(x + metrics.width/2, y);
		GlobalDrawingStates::Redraw = true ;
	}

	template <typename UIType>
	void Button<UIType>::handleEvents(EventType const& event)
	{
		int actx, acty ;

		switch(event.type)
		{
			case EventType::MouseMoved:
				actx = event.mouseMove.x;
				acty = event.mouseMove.y ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height);
				if(focused)
				{
					//this->setActiveColor();
                    this->animations[1].start();
                    this->animations[0].stop();
					cursor = this->HandCursor ;
				}
				else
				{
					//this->setInactiveColor();
					this->animations[0].start();
					this->animations[1].stop();
					cursor = this->ArrowCursor ;
				}
			break;

			case EventType::MouseButtonPressed:
				if(focused)
					this->setClickedColor();
			break;

			case EventType::MouseButtonReleased:
				if(focused)
					this->setActiveColor();
			break;
		}

		if(focused)
			for(auto& f : callbacks[event.type])
				f(event);

	}

	template <typename UIType>
	void Button<UIType>::makeButtonFilled(const PropertyStates<Color>& b,
	                                      const PropertyStates<Color>& o)
	{
		filled = true ;
		palette.base = b;
		palette.overlay = o;
		outline.inactive = outline.active = outline.clicked = 0 ;
		this->state = this->Invalid ;
		this->setInactiveColor();
	}

	template <typename UIType>
	class ToggleButton :
	public Button<UIType>
	{

		typedef typename UIType::Event EventType ;

	protected:
		using UIElement<UIType>::shape ;
		using UIElement<UIType>::text ;
		using UIElement<UIType>::width ;
		using UIElement<UIType>::height ;
		using UIElement<UIType>::x ;
		using UIElement<UIType>::y ;
		using UIElement<UIType>::cursor ;
		using UIElement<UIType>::palette ;
		using UIElement<UIType>::outline ;

		using EventHandler<UIType>::focused ;
		using EventHandler<UIType>::callbacks ;
		using EventHandler<UIType>::id ;

		bool toggle ;

	public:
		ToggleButton(const std::string& name, int x, int y, int w, int h)
		: Button<UIType>(name, x, y, w, h), toggle{false} {}
		ToggleButton() : Button<UIType>("", 0, 0, 0, 0) {}

		void handleEvents(EventType const&);
		bool isSelected() const { return toggle; }
		void toggleState(bool) ;

	};

	template <typename UIType>
	void ToggleButton<UIType>::toggleState(bool state)
	{
		toggle = state ;
		if(toggle)
			this->setClickedColor();
		else
			this->setInactiveColor();
	}

	template <typename UIType>
	void ToggleButton<UIType>::handleEvents(EventType const& event)
	{
		int actx, acty ;
		switch(event.type)
		{
			case EventType::MouseMoved:
				actx = event.mouseMove.x;
				acty = event.mouseMove.y ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height);
				if(focused && !toggle)
				{
					this->setActiveColor();
					cursor = this->HandCursor ;
				}
				else
				if(!focused && !toggle)
				{
					this->setInactiveColor();
					cursor = this->ArrowCursor ;
				}
			break;

			case EventType::MouseButtonPressed:
				if(focused)
					this->setClickedColor();
			break;

			case EventType::MouseButtonReleased:
				if(!focused && toggle)
				{
					this->setActiveColor();
					toggle = false ;
				}
				else
				if(focused && !toggle)
				{
					this->setClickedColor();
					toggle = true ;
				}
			break;
		}

		if(focused)
			for(auto& f : callbacks[event.type])
				f(event);
	}
}

#endif
