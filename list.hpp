#ifndef __UX_LIST_
#define __UX_LIST_

#include "component.hpp"
#include "scrollbar.hpp"
#include "scrollable.hpp"
#include <algorithm>

namespace ux
{
	template <typename UIType>
	class List : public Component<UIType>, public Scrollable
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

		static ColorPalette<UIType> DefaultColors ;
		static int DefaultItemHeight ;
		static int DefaultHeight ;

		Scrollbar<UIType> scrollbar ;
		typename UIType::RenderTexture bview ;
		typename UIType::Texture       list_texture ;

		std::vector<ToggleButton<UIType>> items ;
		int item_height, item_width ;
		unsigned int item_selected ;
		int smooth_move_step, visible ;
		bool dropdown, expanded, smooth_move ;

		void updatePosition(int, int) ;
		void move(int) ;
		void performDropDown();
		void generateTexture();

	public:
		List(int, int, int);

		void addItem(const std::string&);
		void setListItemDimension(int w, int h) { item_width = w; item_height = h; }
		unsigned int getSelectedItemIndex() const { return item_selected; }
		void setDropDown(bool);
		void coarseMove(int);
		void smoothMove(int);

		void handleEvents(const EventType&);
		void draw(WindowType*);
		void update(int _x, int _y) { this->setPosition(_x, _y); updatePosition(_x, _y); }

	};

	template <typename UIType>
	ColorPalette<UIType> List<UIType>::DefaultColors =
		ColorPalette<UIType>{ .base = PropertyStates<Color>{ Color(240, 240, 240), Color(255, 255, 255), Color(255, 255, 255) },
		                     .overlay = PropertyStates<Color>{ Color(20, 20, 20), Color(0, 0, 0), Color(0, 0, 0) } };

	template <typename UIType>
	int List<UIType>::DefaultItemHeight = 20 ;

	template <typename UIType>
	int List<UIType>::DefaultHeight = 80 ;

	template <typename UIType>
	List<UIType>::List(int x, int y, int w) :
	Component<UIType>("", x, y, w, DefaultHeight)
	{
		item_width = w ;
		item_height = DefaultItemHeight ;
		item_selected = -1 ;
		total_height = 0 ;
		visible = 4 ;
		smooth_move_step = 2 ;
		dropdown = false ;
		expanded = true ;
		scrollbar = Scrollbar<UIType>(x + width, y, w, height);
		scrollbar.disable();
		scrollbar.add(this);
		setYLimits(0, item_height * visible);
		incrementY(item_height * visible);
		setY(0);
		this->setColorPalette(DefaultColors);
		this->setOutlineThickness(PropertyStates<int>(0, 0, 0));
		this->setInactiveColor();
		this->add(&scrollbar);
	}

	template <typename UIType>
	void List<UIType>::addItem(const std::string& item)
	{
		int ty = y + (item_height * items.size());
		items.push_back(ToggleButton<UIType>(item, x, ty, item_width, item_height));
		items[items.size() - 1].makeButtonFilled(PropertyStates<Color>{ Color(255, 255, 255), Color(255, 255, 255), Color(100, 100, 200) },
		                                         PropertyStates<Color>{ Color(40, 40, 40), Color(40, 40, 40), Color(40, 40, 40) });
		total_height += item_height ;
		setYLimits(0, total_height);
		scrollbar.updateLength();
		bview.create(width, total_height);
	}

	template <typename UIType>
	void List<UIType>::updatePosition(int _x, int _y)
	{
		for(auto i = 0; i < items.size(); ++i)
			items[i].setPosition(_x, _y + (i * item_height));
		scrollbar.update(scrollbar.getX(), _y);
	}

	template <typename UIType>
	void List<UIType>::move(int step)
	{
		for(auto i = 0; i < items.size(); ++i)
			items[i].setPosition(x, y + (i * item_height) + (step));
		GlobalDrawingStates::Redraw = true ;
	}

	template <typename UIType>
	void List<UIType>::coarseMove(int step)
	{
		moveY(-step * item_height);
		move(-view.starty);
		smooth_move = false ;
	}

	template <typename UIType>
	void List<UIType>::smoothMove(int amount)
	{
		moveY(-amount * smooth_move_step);
		move(-view.starty);
		smooth_move = true ;
	}

	template <typename UIType>
	void List<UIType>::setDropDown(bool dd)
	{
		dropdown = dd ;
		expanded = !dd ;
		performDropDown();
	}

	template <typename UIType>
	void List<UIType>::performDropDown()
	{
		if(!expanded)
		{
			height = item_height ;
			visible = 1 ;
		}
		else
		{
			height = DefaultHeight ;
			visible = 4 ;
		}

		incrementY(visible * item_height);

		// Expand list and if selected index is b/w end and no of items visible
		// then start the expanded view from total_items - visible index .
		if((view.starty + (visible * item_height)) >= total_height && expanded)
		{
			int start = items.size() - visible ;
			setY(start * item_height);
			move(-view.starty);
		}
		shape.setSize(shape.getSize().x, height);
		GlobalDrawingStates::Redraw = true ;
		scrollbar.enable();
	}

	template <typename UIType>
	void List<UIType>::generateTexture()
	{
		typename UIType::RectangleShape shape ;
		typename UIType::Text text ;
		int viewposx = 0;
		int viewposy = 0 ;
		bview.clear(palette.base.active);
		for(auto& item : items)
		{
			shape = item.getShape() ;
			text = item.getText();
			text.setPosition(viewposx, viewposy);
			shape.setPosition(viewposx, viewposy);
			bview.draw(shape);
			bview.draw(text);
			viewposy += item_height ;
		}
		bview.display();
		list_texture = bview.getTexture();
	}

	template <typename UIType>
	void List<UIType>::draw(WindowType* w)
	{
		Cursor c(cursor);
		c.set(w->getSystemHandle());
		w->draw(shape);

		// If expanded, draw from selected item to end
		if(expanded)
		{
			generateTexture();
			typename UIType::Sprite drawable(list_texture);
			drawable.setTextureRect(typename UIType::IRect(0, view.starty, width, view.incry));
			drawable.setPosition(x, y);
			w->draw(drawable);
			scrollbar.draw(w);
		}

		// If not, then draw only selected item
		else
		if(!expanded && dropdown)
		{
			auto index = (item_selected < items.size()) ? item_selected : 0 ;
			setY(index * item_height);
			move(-view.starty);
			items[index].draw(w);
		}
	}

	template <typename UIType>
	void List<UIType>::handleEvents(const EventType& event)
	{
		int actx, acty ;
		auto select_item = [&](unsigned int index)
		{
			for(auto i =0; i < items.size(); ++i)
				if(i == index)
					items[i].toggleState(true);
				else
					items[i].toggleState(false);
		};

		// Handle all events
		switch(event.type)
		{
			case EventType::MouseButtonReleased:
				actx = event.mouseButton.x ;
				acty = event.mouseButton.y ;
				focused = GlobalDrawingStates::IsWithin(actx, acty, x, y, width, height);
				if(dropdown)
					expanded = focused ;
			break;

			case EventType::MouseWheelMoved:
				if(focused)
					smoothMove(event.mouseWheel.delta);
			break;

			case EventType::KeyPressed:
				if(focused || expanded)
				{
					int dir = event.key.code ;
					if(dir == UIType::Keyboard::Down)
					{
						coarseMove(-1);
						item_selected += 1 ;
						if(item_selected == items.size())
							item_selected = items.size() - 1 ;
						select_item(item_selected);
					}
					else
					if(dir == UIType::Keyboard::Up)
					{
						coarseMove(1);
						if(item_selected > 0)
							item_selected -= 1 ;
						select_item(item_selected);
					}
					std::cout << "\nSelected : " << item_selected ;
				}
			break;
		}

		// Make scrollbar handle the events
		scrollbar.handleEvents(event);

		// Let items handle event and determine selected item
		for(auto i = 0; i < items.size(); ++i)
		{
			if(focused)
				items[i].handleEvents(event);
			if(items[i].isSelected())
				item_selected = i ;
		}

		if(item_selected < items.size() && focused)
			for(auto& f : callbacks[UXEvents::ListItemSelected])
				f(event);

		// If clicked, expand list if it is in dropdown mode
		if(event.type == EventType::MouseButtonReleased && dropdown)
			performDropDown();

		// Dispatch registered event handlers
		if(focused)
			for(auto& f : callbacks[event.type])
				f(event);
	}
}

#endif
