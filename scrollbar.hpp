#ifndef __UX_SCROLL_BAR_
#define __UX_SCROLL_BAR_

#include "component.hpp"
#include "scrollable.hpp"

namespace ux
{

	template <typename UIType>
	class Scrollbar : public Component<UIType>
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

		using Component<UIType>::enabled ;

		static const ColorPalette<UIType> DefaultColors ;
		static const int                  DefaultWidth ;
		static const int                  DefaultHeight ;

		typename UIType::RectangleShape scroll ;
		bool vertical, mouse_down ;
		int  movedy, movedx ;

		void generateTexture();

	public:
		Scrollbar(int, int, int, int, bool);
		Scrollbar() : Component<UIType>("", 0, 0, 0, 0) {}

		void handleEvents(const EventType&);
		void draw(WindowType*);
		void update(int _x, int _y) { this->setPosition(_x, _y); scroll.setPosition(_x, _y); }
		void updateLength();

		template <typename> friend class List ;

	};

	template <typename UIType> const
	ColorPalette<UIType> Scrollbar<UIType>::DefaultColors =
		ColorPalette<UIType>{ .base = PropertyStates<Color>{ Color(255, 255, 255), Color(230, 230, 230), Color(230, 230, 230) },
		                      .overlay = PropertyStates<Color>{ Color(255, 255, 255), Color(100, 100, 100), Color(70, 70, 100) } };

	template <typename UIType> const
	int Scrollbar<UIType>::DefaultWidth = 10 ;

	template <typename UIType> const
	int Scrollbar<UIType>::DefaultHeight = 10 ;

	template <typename UIType>
	Scrollbar<UIType>::Scrollbar(int x, int y, int w, int h, bool v = true)
	: Component<UIType>("", x, y, w, h)
	{
		if(v)
		{
			shape.setSize(DefaultWidth, h);
			scroll.setSize(DefaultWidth, h);
		}
		else
		{
			shape.setSize(w, DefaultHeight);
			scroll.setSize(w, DefaultHeight);
		}
		scroll.setPosition(x, y);
		scroll.setFillColor(DefaultColors.overlay.inactive);
		this->setColorPalette(DefaultColors);
		outline.active = outline.inactive = outline.clicked = 0 ;
		vertical = v ;
		mouse_down = false ;
	}

	template <typename UIType>
	void Scrollbar<UIType>::updateLength()
	{
		if(vertical)
		{
			int parenth = (dynamic_cast<Scrollable*>(this->parent))->getTotalHeight();
			scroll.setSize(scroll.getSize().x, height * height / parenth);
		}
		else
		{
			int parentw = (dynamic_cast<Scrollable*>(this->parent))->getTotalWidth();
			scroll.setSize(width * width / parentw, scroll.getSize().y);
		}
	}

	template <typename UIType>
	void Scrollbar<UIType>::draw(WindowType* w)
	{
		if(enabled)
		{
			Scrollable *scrollable = dynamic_cast<Scrollable*>(this->parent) ;
			if(vertical)
			{
				int scroll_move = scrollable->getStartY(),
					parenth     = scrollable->getTotalHeight();
				scroll.setPosition(x, y + (scroll_move * scroll_move / parenth));
			}
			else
			{
				int scroll_move = scrollable->getStartX(),
					parentw     = scrollable->getTotalWidth();
				scroll.setPosition(x + (scroll_move * scroll_move / parentw), y);
			}
			Cursor c(cursor);
			c.set(w->getSystemHandle());
			w->draw(shape);
			w->draw(scroll);
		}
	}

	template <typename UIType>
	void Scrollbar<UIType>::handleEvents(const EventType& event)
	{
		if(enabled)
		{
			int actx, acty, w = scroll.getSize().x ;
			switch(event.type)
			{
				case EventType::MouseMoved:
					actx = event.mouseMove.x;
					acty = event.mouseMove.y ;
					focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height);
					if(focused || mouse_down)
					{
						this->setActiveColor();
						cursor = this->HandCursor ;
						scroll.setFillColor(DefaultColors.overlay.active);
						if(mouse_down)
						{
							Scrollable *scrollable = dynamic_cast<Scrollable*>(this->parent) ;
							if(vertical)
                            {
                                auto direction = (movedy - acty) < 0 ? -1 : 1 ;
                                scrollable->smoothMove(direction * scrollable->getTotalHeight() /
                                                       scrollable->getVisibleHeight());
                            }
							else
                            {
                                auto direction = (movedx - actx) < 0 ? -1 : 1 ;
                                scrollable->smoothMove(direction * scrollable->getTotalWidth() /
                                                       scrollable->getVisibleWidth());
                            }
						}
					}
					else
					{
						this->setInactiveColor();
						cursor = this->ArrowCursor ;
						scroll.setFillColor(DefaultColors.overlay.inactive);
					}
				break;

				case EventType::MouseButtonPressed:
					mouse_down = focused ;
					movedy = event.mouseButton.y;
					movedx = event.mouseButton.x;
				break;

				case EventType::MouseButtonReleased:
					mouse_down = false ;
				break;

			}
		}
	}
}

#endif
