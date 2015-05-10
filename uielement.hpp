#ifndef __UX_UI_ELEMENT_
#define __UX_UI_ELEMENT_

#include <string>
#include <iostream>
#include "cursor.hpp"
#include "animator.h"

namespace ux
{
	template <typename UIType> struct FontStore
	{
		typedef typename UIType::Font Font ;

		static Font Regular ;
		static Font Bold ;
	};

	template <typename UIType> typename FontStore<UIType>::Font FontStore<UIType>::Regular ;
	template <typename UIType> typename FontStore<UIType>::Font FontStore<UIType>::Bold ;

	struct GlobalDrawingStates
	{
		static bool Redraw ;

		static bool IsWithin(int, int, int, int, int, int);
	};

	bool GlobalDrawingStates::Redraw = true ;
	bool GlobalDrawingStates::IsWithin(int x, int y, int originx, int originy, int width, int height)
	{
		return (x > originx) && (y > originy) && (x < originx + width) && (y < originy + height) ;
	}

	template <typename UIType> bool LoadFonts(const std::string& name = "NotoSans")
	{
		bool success = false ;
		success = FontStore<typename UIType::Font>::Regular.loadFromFile(name + "-Regular.ttf");
		success = success && FontStore<typename UIType::Font>::Bold.loadFromFile(name + "-Bold.ttf");
		return success ;
	}

	template <typename Property> struct PropertyStates
	{
		Property inactive ;
		Property active ;
		Property clicked ;

		PropertyStates() = default ;
		PropertyStates(const PropertyStates<Property>& p) :
			inactive{p.inactive}, active{p.active}, clicked{p.clicked} {}
		PropertyStates(const Property& i, const Property& a, const Property& c) :
			inactive{i}, active{a}, clicked{c} {}
		PropertyStates& operator=(const PropertyStates&) = default ;
	};

	template <typename UIType> struct ColorPalette
	{

		typedef typename UIType::Color Color ;
		PropertyStates<Color> base ;
		PropertyStates<Color> overlay ;
		PropertyStates<Color> outline ;

		ColorPalette() = default ;
		~ColorPalette() = default ;
		ColorPalette(const ColorPalette<UIType>&) = default ;
		ColorPalette(ColorPalette<UIType>&&) = default ;
		ColorPalette& operator=(const ColorPalette<UIType>&) = default ;
	};

	template <typename UIType>
	class UIElement
	{

		typedef typename UIType::Color Color ;

	protected:
		typename UIType::RectangleShape shape ;
		typename UIType::Text text ;
		ColorPalette<UIType> palette ;
		PropertyStates<int> outline ;

		int height, width ;
		int x, y ;
		int cursor ;

		char state ;

		void setInactiveColor() ;
		void setActiveColor() ;
		void setClickedColor() ;

	public:
		UIElement(const std::string&, int, int, int, int);

		void setColorBase(const PropertyStates<Color>& c) { palette.base = c ; GlobalDrawingStates::Redraw = true ; }
		void setColorOverlay(const PropertyStates<Color>& c) { palette.overlay = c ; GlobalDrawingStates::Redraw = true ; }
		void setColorOutline(const PropertyStates<Color>& c) { palette.outline = c ; GlobalDrawingStates::Redraw = true ; }
		void setOutlineThickness(const PropertyStates<int>& o) { outline = o;  GlobalDrawingStates::Redraw = true ; }
		void setColorPalette(const ColorPalette<UIType>& p) { palette = p; GlobalDrawingStates::Redraw = true ; }
		void setPosition(int _x, int _y) { x = _x; y = _y; shape.setPosition(x, y); text.setPosition(x, y); }
		void setSize(int x, int y) { width = x; height = y; shape.setSize(x, y); }

		int getY() const { return y; }
		int getX() const { return x; }
		std::string getString() const { return text.getString(); }
		typename UIType::RectangleShape getShape() const { return shape; }
		typename UIType::Text getText() const { return text; }

		virtual void update(int, int) = 0 ;
		virtual void draw(typename UIType::Window*) = 0 ;

		void init() { setInactiveColor(); }
		enum { WaitCursor, TextCursor, ArrowCursor, HandCursor };
		enum { Invalid, Inactive, Active, Clicked };

		std::vector<Animation> animations ;
	};

	template <typename UIType>
	UIElement<UIType>::UIElement(const std::string& str, int _x, int _y, int w, int h)
	{
		int char_size = 0.75 * h ;
		height = h; width = w;
		x = _x; y = _y;
		state = Invalid ;
		outline.inactive = 2 ;
		outline.active = 3 ;
		outline.clicked = 4 ;
		palette.outline.active = palette.outline.inactive = palette.outline.clicked = Color(255, 255, 255) ;
		cursor = ArrowCursor ;
		shape.setPosition(x, y);
		shape.setSize(width, height);
		text.setString(str);
		text.setFont(FontStore<typename UIType::Font>::Regular);
		text.setCharacterSize(char_size);
		text.setPosition(x, y);
	}

	template <typename UIType>
	void UIElement<UIType>::setInactiveColor()
	{
		if(state != Inactive)
		{
			shape.setFillColor(palette.base.inactive);
			shape.setOutlineColor(palette.outline.inactive);
			shape.setOutlineThickness(outline.inactive);
			text.setColor(palette.overlay.inactive);
			GlobalDrawingStates::Redraw = true ;
			state = Inactive ;
		}
	}

	template <typename UIType>
	void UIElement<UIType>::setActiveColor()
	{
		if(state != Active)
		{
			shape.setFillColor(palette.base.active);
			shape.setOutlineColor(palette.outline.active);
			shape.setOutlineThickness(outline.active);
			text.setColor(palette.overlay.active);
			GlobalDrawingStates::Redraw = true ;
			state = Active;
		}
	}

	template <typename UIType>
	void UIElement<UIType>::setClickedColor()
	{
		if(state != Clicked)
		{
			shape.setFillColor(palette.base.clicked);
			shape.setOutlineColor(palette.outline.clicked);
			shape.setOutlineThickness(outline.clicked);
			text.setColor(palette.overlay.clicked);
			GlobalDrawingStates::Redraw = true ;
			state = Clicked ;
		}
	}

}

#endif
