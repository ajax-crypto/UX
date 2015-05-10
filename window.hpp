#ifndef __UX_WINDOW_
#define __UX_WINDOW_

#include "component.hpp"
#include "button.hpp"

#include <vector>

namespace ux
{
	template <typename UIType>
	class Window : public Component<UIType>
	{

		int dcalls = 1 ;

		typedef typename UIType::Color Color ;
		typedef typename UIType::Window WindowType ;
		typedef typename UIType::Event EventType ;
		typedef typename UIType::RectangleShape Shape ;

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

		using Component<UIType>::children ;
		using Component<UIType>::parent ;

		static const ColorPalette<UIType> DefaultColors ;
		static const ColorPalette<UIType> DefaultTitlebarColors ;
		static const ColorPalette<UIType> DefaultCloseButtonColors ;

		Shape  titlebar ;
		Button<UIType> close ;
		ColorPalette<UIType> titlebar_palette ;
		int titlebar_width, titlebar_height ;
		bool closed, has_titlebar ;

		typename UIType::TargetWindow* target ;

	public:
		Window(int, int);

		void handleEvents(const EventType&);
		bool isClosed() const { return closed; }
		void draw(WindowType*);
		void add(Component<UIType>* c) { if(!has_titlebar) c->update(c->x, c->y + titlebar_height); Component<UIType>::add(c); }
		void setRenderTarget(WindowType* t, bool tb, const std::string& str)
		{ text.setString(str); target = dynamic_cast<typename UIType::TargetWindow*>(t); has_titlebar = tb; text.setString(str); if(!tb) add(&close); }

		struct TitlePosition
		{
			int x, y ;
		} LEFT, RIGHT, CENTER ;

		void update(int, int) {}

		friend class Animator ;

	};

	template <typename UIType> const
	ColorPalette<UIType> Window<UIType>::DefaultColors =
		ColorPalette<UIType>{ .base = PropertyStates<Color>{ Color(200, 200, 200), Color(200, 200, 200), Color(200, 200, 200) },
		                      .overlay = PropertyStates<Color>{ Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0) } };

	template <typename UIType> const
	ColorPalette<UIType> Window<UIType>::DefaultTitlebarColors =
		ColorPalette<UIType>{ .base = PropertyStates<Color>{ Color(200, 200, 255), Color(160, 160, 255), Color(160, 160, 255) } };

	template <typename UIType> const
	ColorPalette<UIType> Window<UIType>::DefaultCloseButtonColors =
		ColorPalette<UIType>{ .base = PropertyStates<Color>{ Color(255, 150, 150), Color(255, 100, 100), Color(255, 50, 50) },
		                      .overlay = PropertyStates<Color>{ Color(255, 150, 150), Color(255, 100, 100), Color(255, 50, 50) } };

	template <typename UIType>
	Window<UIType>::Window(int w, int h) :
	Component<UIType>("", 0, 0, w, h)
	{
		titlebar_width = w ;
		titlebar_height = (h/10) + 3 ;
		int char_size = titlebar_height - 10;
		LEFT.x = x + 5 ;
		LEFT.y = y + 5;
		CENTER.x = width / 2 ;
		CENTER.y = y + 2 ;
		//RIGHT.x = x + width - 5 - (t.length() * char_size) ;
		outline.inactive = outline.active = outline.clicked = 0 ;
		shape.setOutlineThickness(outline.inactive);
		text.setPosition(LEFT.x, LEFT.y);
		text.setCharacterSize(char_size) ;
		titlebar.setPosition(x, y);
		titlebar.setSize(titlebar_width, titlebar_height);
		titlebar_palette.base = DefaultTitlebarColors.base ;
		titlebar.setFillColor(titlebar_palette.base.active);
		close.setPosition(x + width - (width / 10), y - titlebar_height);
		close.setSize((width / 10), (height/10) + 3);
		close.makeButtonFilled(DefaultCloseButtonColors.base, DefaultCloseButtonColors.overlay);
		close.addEventListener(EventType::MouseButtonReleased, [&](EventType const& e) mutable { closed = true; });
		this->setColorPalette(DefaultColors);
		this->setActiveColor();
		closed = false ;
	}

	template <typename UIType>
	void Window<UIType>::draw(WindowType* w)
	{
		Cursor c(cursor);
		c.set(w->getSystemHandle());
		w->draw(shape);
		if(!has_titlebar)
		{
			w->draw(titlebar);
			w->draw(text);
		}
		for(auto c : children)
			c->draw(w);
        GlobalDrawingStates::Redraw = false;
        Animator::Animate(this);
		std::cout << "\nDrawing calls #" << dcalls++ ;
	}

	template <typename UIType>
	void Window<UIType>::handleEvents(const EventType& event)
	{
		int actx, acty ;
		switch(event.type)
		{
			case EventType::LostFocus:
				this->setInactiveColor();
				titlebar.setFillColor(titlebar_palette.base.inactive);
				focused = false ;
			break;

			case EventType::GainedFocus:
				this->setActiveColor();
				titlebar.setFillColor(titlebar_palette.base.active);
			break;

			case EventType::MouseLeft:
				focused = false ;
			break ;

			case EventType::MouseButtonPressed:
				actx = event.mouseButton.x ;
				acty = event.mouseButton.y ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, 0, 0, titlebar_width, titlebar_height);
			break;

			case EventType::MouseButtonReleased:
				focused = false ;
			break;

			case EventType::MouseMoved:
				if(focused)
					target->setPosition(event.mouseMove.x, event.mouseMove.y);
			break;

			case EventType::Closed:
				closed = true;
			break;

			case EventType::Resized:
				GlobalDrawingStates::Redraw = false ;
				shape.setSize(event.size.width, event.size.height);
			break ;
		}

		for(auto c : children)
		{
			c->handleEvents(event);
		}
	}
}

#endif
