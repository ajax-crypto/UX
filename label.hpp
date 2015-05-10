#ifndef __UX_LABEL_
#define __UX_LABEL_

#include "component.hpp"

namespace ux
{
	template <typename UIType>
	class Label : public Component<UIType>
	{
	
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
		
		bool filled ;
	
	public:
		Label(const std::string&, int, int, int, int);
		Label() : Component<UIType>("", 0, 0, 0, 0) {}

		void handleEvents(EventType const&);
		void draw(WindowType*);
		void makeLabelFilled(const PropertyStates<Color>&, const PropertyStates<Color>&);
		void setString(const std::string& str) { text.setString(str); }
		void update(int _x, int _y) { this->setPosition(_x, _y); }
		
	};

	template <typename UIType> 
	Label<UIType>::Label(const std::string& t, int x, int y, int w, int h) :
	Component<UIType>(t, x, y, w, h)
	{
		filled = false ;
		this->setColorOverlay(PropertyStates<Color>{ Color(40, 40, 40), Color(40, 40, 40), Color(40, 40, 40) });
		this->setColorBase(PropertyStates<Color>{ Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0) });
		this->setOutlineThickness(PropertyStates<int>{ 0, 0, 0 });
		this->setInactiveColor();
	}
	
	template <typename UIType>
	void Label<UIType>::draw(WindowType* w)
	{
		Cursor c(cursor); 
		c.set(w->getSystemHandle()); 
		w->draw(shape);  
		w->draw(text);
		GlobalDrawingStates::Redraw = false;
	}
	
	template <typename UIType>
	void Label<UIType>::handleEvents(EventType const& event)
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
					this->setActiveColor();
					cursor = this->HandCursor ;
				}
				else 
				{
					this->setInactiveColor();
					cursor = this->ArrowCursor ;
				}
			break;
			
			case EventType::MouseButtonPressed:
				if(focused)
					this->setClickedColor();
			break;
		}
		
		if(focused)
			for(auto& f : callbacks[event.type])
				f(event) ;
	}
	
	template <typename UIType> 
	void Label<UIType>::makeLabelFilled(const PropertyStates<Color>& b,
	                                    const PropertyStates<Color>& o)
	{
		shape.setOutlineThickness(0);
		filled = true ;
		palette.base = b;
		palette.overlay = o;
		outline.inactive = outline.active = outline.clicked = 0 ;
		this->setInactiveColor();
	}
}

#endif