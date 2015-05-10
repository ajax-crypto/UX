#ifndef __UX_TEXTBOX_
#define __UX_TEXTBOX_

#include "component.hpp"
#include "scrollable.hpp"
#include "scrollbar.hpp"

#include <algorithm>

void pl(const std::vector<int>& v)
{
	for(int c : v)
		std::cout << c << " ";
}

namespace ux
{
	template <typename UIType>
	class Textbox :
	public Component<UIType>,
	public Scrollable
	{

	protected:
		typedef typename UIType::Color Color ;
		typedef typename UIType::Window WindowType ;
		typedef typename UIType::Event EventType ;

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

		static ColorPalette<UIType> DefaultColors ;

		typename UIType::RectangleShape ibeam ;
		std::string                     contents  ;
		std::vector<int>                strides ;
		int                             stride;
		Ranged<int>                     ibeam_ptr ;

		typename UIType::RenderTexture bview ;
		typename UIType::Texture       texture ;

		void updateLength();

	public:
		Textbox(int, int, int, int);

		void coarseMove(int);
		void smoothMove(int);
		void generateTexture();
		void handleEvents(const EventType&);
		void draw(WindowType*);
		void update(int _x, int _y) { this->setPosition(_x, _y); ibeam.setPosition(_x + 2, _y + 2); }

	};

	template <typename UIType>
	ColorPalette<UIType> Textbox<UIType>::DefaultColors =
		ColorPalette<UIType>{ .base = PropertyStates<Color>{ Color(240, 240, 240), Color(255, 255, 255), Color(255, 255, 255) },
		                      .overlay = PropertyStates<Color>{ Color(20, 20, 20), Color(0, 0, 0), Color(0, 0, 0) } };


	template <typename UIType>
	Textbox<UIType>::Textbox(int x, int y, int w, int h) :
	Component<UIType>("", x, y, w, h)
	{
		total_width = 0 ;
		ibeam_ptr = Ranged<int>(1, 0, 0);
		strides.push_back(0);
		strides.push_back(0);
		text.setCharacterSize(static_cast<int>(0.75 * h));
		text.setPosition(x + 2, y + 1);
		text.setColor(DefaultColors.overlay.inactive);
		ibeam.setPosition(x + 2, y + 2);
		ibeam.setSize(1, h - 4);
		ibeam.setFillColor(Color(0, 0, 0));
		bview.create(w, h);
		setXLimits(0, w);
		incrementX(w);
		setX(0);
		this->setColorPalette(DefaultColors);
		this->setOutlineThickness(PropertyStates<int>(0, 0, 0));
		this->setInactiveColor();
	}

	template <typename UIType>
	void Textbox<UIType>::generateTexture()
	{
		typename UIType::Text text = this->getText();
		bview.clear(palette.base.active);
		text.setPosition(2, 1);
		bview.draw(text);
		bview.display();
		texture = bview.getTexture();
	}

	template <typename UIType>
	void Textbox<UIType>::updateLength()
	{
		total_width = std::accumulate(strides.begin(),
									  strides.end(),
									  0);
		if(total_width > width)
		{
			//auto fit = width / strides[strides.size() - 2] ;
			//auto tw = (ibeam_ptr - fit) * strides[strides.size() - 2] + width ;
			setXLimits(0, total_width);
			bview.create(total_width, height);
		}
		else
		{
			setXLimits(0, width);
			bview.create(width, height);
		}
	}

	template <typename UIType>
	void Textbox<UIType>::coarseMove(int step)
	{
		moveX(step * strides[strides.size() - 2]);
	}

	template <typename UIType>
	void Textbox<UIType>::smoothMove(int amount)
	{
		moveX(-amount);
	}

	template <typename UIType>
	void Textbox<UIType>::draw(WindowType* w)
	{
		Cursor c(cursor);
		c.set(w->getSystemHandle());
		generateTexture();
		typename UIType::Sprite drawable(texture);
		drawable.setTextureRect(typename UIType::IRect(view.startx, 0, view.incrx, height));
		drawable.setPosition(x, y);
		w->draw(shape);
		w->draw(drawable);
		if(focused)
			w->draw(ibeam);
	}

	template <typename UIType>
	void Textbox<UIType>::handleEvents(const EventType& event)
	{
		int actx, acty ;
		switch(event.type)
		{
			case EventType::MouseButtonReleased:
				actx = event.mouseButton.x ;
				acty = event.mouseButton.y ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height);
				if(focused)
				{
					this->setActiveColor();
					cursor = this->TextCursor ;
				}
				else
				{
					cursor = this->ArrowCursor ;
					this->setInactiveColor();
				}
			break;

			case EventType::TextEntered:
				if(focused)
				{
					// Backspace is handled separately to delete characters
					char txt = (char)event.text.unicode ;
					if(txt == '\b')
					{
						if(ibeam_ptr > 0)
						{
							std::string val = text.getString() ;
							val = val.erase(ibeam_ptr-1, 1);
							text.setString(val);
							auto px = ibeam.getPosition().x, py = ibeam.getPosition().y;
							auto w = std::accumulate(strides.begin(),
							                         strides.begin() + ibeam_ptr,
							                         0);
							px = (w > width) ? x + width + 2 : px - strides[ibeam_ptr] ;
							px = (px < x) ? x : px ;
							ibeam.setPosition(px, py);
							strides.pop_back();
							strides.pop_back();
							strides.push_back(0);
							ibeam_ptr.setHigh(strides.size() - 1);
						}
						--ibeam_ptr ;
					}
					else
					if(txt != '\n' && txt != '\r')
					{
						auto pmetrics = text.getGlobalBounds() ;
						std::string val = text.getString();
						val.insert(ibeam_ptr, 1, txt);
						text.setString(val);
						auto metrics = text.getGlobalBounds();
						auto px = metrics.width - pmetrics.width ;
						strides.pop_back();
						strides.push_back(px);
						strides.push_back(0);
						ibeam_ptr.setHigh(strides.size() - 1);
						++ibeam_ptr ;
						auto cx = ibeam.getPosition().x + strides[ibeam_ptr] ;
						px = (cx > (x + width - 2)) ? x + width - 4 : cx ;
						ibeam.setPosition(px, ibeam.getPosition().y);
					}
					updateLength();
					auto metrics = text.getGlobalBounds();
					if(metrics.width >= (width - 5))
						coarseMove(1);
					else
						setX(0);
					GlobalDrawingStates::Redraw = true ;
				}
			break;

			case EventType::KeyPressed:
				if(focused)
				{
					int dir = event.key.code ;
					if(dir == UIType::Keyboard::Left)
					{
						coarseMove(-1);
						auto metrics = ibeam.getPosition();
						ibeam.setPosition(metrics.x - strides[--ibeam_ptr], metrics.y);
					}
					else
					if(dir == UIType::Keyboard::Right)
					{
						coarseMove(1);
						auto metrics = ibeam.getPosition();
						ibeam.setPosition(metrics.x + strides[++ibeam_ptr], metrics.y);
					}
					GlobalDrawingStates::Redraw = true ;
				}
			break;
		}

		if(focused)
			for(auto& f : callbacks[event.type])
				f(event);

	}

	template <typename UIType>
	class Passwordbox : public Textbox<UIType>
	{

	protected:
		typedef typename UIType::Window WindowType ;
		typedef typename UIType::Event EventType ;

		using UIElement<UIType>::shape ;
		using UIElement<UIType>::text ;
		using UIElement<UIType>::width ;
		using UIElement<UIType>::height ;
		using UIElement<UIType>::x ;
		using UIElement<UIType>::y ;
		using UIElement<UIType>::cursor ;

		using EventHandler<UIType>::focused ;
		using EventHandler<UIType>::callbacks ;

		typename UIType::Text mask ;

	public:
		Passwordbox(int, int, int, int);

		void handleEvents(const EventType&);
		void draw(WindowType*);
		void update(int, int);
	};

	template <typename UIType>
	Passwordbox<UIType>::Passwordbox(int x, int y, int w, int h)
	: Textbox<UIType>(x, y, w, h)
	{
		mask.setFont(FontStore<typename UIType::Font>::Regular);
		mask.setCharacterSize(static_cast<int>(0.75 * h));
		mask.setPosition(x + 2, y + 1);
		mask.setColor(Textbox<UIType>::DefaultColors.overlay.inactive);
	}

	template <typename UIType>
	void Passwordbox<UIType>::handleEvents(const EventType& event)
	{
		int actx, acty ;
		switch(event.type)
		{
			case EventType::MouseButtonReleased:
				actx = event.mouseButton.x ;
				acty = event.mouseButton.y ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height);
				if(focused)
				{
					this->setActiveColor();
					cursor = this->TextCursor ;
				}
				else
				{
					cursor = this->ArrowCursor ;
					this->setInactiveColor();
				}
			break;

			case EventType::TextEntered:
				if(focused)
				{
					// Backspace is handled separately to delete characters
					if((char)event.text.unicode == '\b')
					{
						std::string val = text.getString(), m = mask.getString();
						val = val.substr(0, val.size() - 1);
						m = m.substr(0, m.size() - 1);
						text.setString(val);
						mask.setString(m);
					}
					else
					if((char)event.text.unicode != '\n' && (char)event.text.unicode != '\r')
					{
						text.setString(text.getString() + (char)event.text.unicode);
						mask.setString(std::string(mask.getString()) + (char)63);
					}
					GlobalDrawingStates::Redraw = true ;
				}
			break;
		}
	}

	template <typename UIType>
	void Passwordbox<UIType>::draw(WindowType* w)
	{
		Cursor c(cursor);
		c.set(w->getSystemHandle());
		w->draw(shape);
		w->draw(mask);
	}

	template <typename UIType>
	void Passwordbox<UIType>::update(int _x, int _y)
	{
		Textbox<UIType>::update(_x, _y);
		mask.setPosition(_x, _y);
	}

};

#endif
