#ifndef __UX_BUTTON_
#define __UX_BUTTON_

#include "component.hpp"
#include "animator.h"
#include "log.hpp"

namespace ux
{

	class BasicElement : public Component
	{

	public:
		BasicElement(const std::string&, int, int, int, int, bool = true);
        
		BasicElement(const std::string& str, const Vec2i& pos,
                                       const Vec2i& dim,
                                       bool = true):   
            BasicElement{str, pos.x, pos.y, dim.x, dim.y} 
        {}
        
		BasicElement() :
		    Component{"", 0, 0, 0, 0}
        { START; END; }

		void handleEvents(Event const&);
		void draw(Window_Impl*);
		void update(int, int);
	};

	using Button = BasicElement ;
	using Label = BasicElement ;

	class ToggleButton : public BasicElement
	{
		void addAnimations();

	protected:

		bool  m_toggle ;
		Color m_toggle_color, m_normal_color;

	public:
		ToggleButton(const std::string&, int, int, int, int,
                     const Color&, const Color&);
		ToggleButton() ;

		void handleEvents(Event const&);
		bool isSelected() const { return m_toggle; }
		void toggleState(bool) ;

		void setNormalColor(const Color&);
		void setToggleColor(const Color& c) { m_toggle_color = c; }
	};

}

#endif
