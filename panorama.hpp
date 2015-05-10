#ifndef __UX_PANORAMA_
#define __UX_PANORAMA_

#include "component.hpp"

#include <vector>

namespace ux
{
	template <typename UIType>
	class Panorama : public Component<UIType>
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
		
		unsigned int current ;
		std::vector<std::string> panel_headers ;
		
		static PropertyStates<int>  DefaultOutline ;
		static ColorPalette<UIType> DefaultPalette ;
		
	public:
		Panorama() : Component<UIType>(), current{0}, outline{DefaultOutline} {}
		Panorama(int, int, int, int);
		
		void addPanels(const std::string& title, Panel<UIType>* c) { panel_headers.add(title); Component<UIType>::add(c); }
		
		void draw(WindowType*);
		void handleEvents(const EventType&);
		void update(int, int);
	};
	
	template <typename UIType>
	PropertyStates<int> Panorama<UIType>::DefaultOutline = PropertyStates<int>{ 10, 10, 10 } ;
	
	template <typename UIType>
	ColorPalette<UIType> Panorama<UIType>::DefaultOutline = Palette<Color>{ 
		.base = { Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0) },
		.overlay = { Color(60, 60, 60), Color(40, 40, 40), Color(20, 20, 20) },
        .outline = { Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0) }	};
	
	template <typename UIType>
	Panorama<UIType>::Panorama(int x, int y, int w, int h)
	: Component<UIType>("", x, y, w, h), current{0}, outline{DefaultOutline}
	{
		text.setCharacterSize(40);
	}
	
	template <typename UIType>
	void Panorama<UIType>::draw(WindowType* w)
	{
		w->draw(shape);
		children[current]->draw(w);
		w->draw(text);
	}
	
	template <typename UIType>
	void Panorama<UIType>::update(int _x, int _y)
	{
		x = _x; y = _y ;
		for(auto& p : children)
			p->update(_x, _y);
	}
	
	template <typename UIType>
	void Panorama<UIType>::handleEvents(const EventType& event)
	{
		switch(event.type)
		{
			case EventType::MouseButtonReleased:
				if(focused)
				{	
					text.setString(panel_headers[current]);
					
				}
			break;
		}
	}	
}

#endif