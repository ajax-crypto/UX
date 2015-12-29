#ifndef __UX_UI_ELEMENT_
#define __UX_UI_ELEMENT_

#include "style.hpp"
#include "log.hpp"

namespace ux
{
	class AnimCount ;
	class Window ;

	class LookAndFeel
	{
    public:

        LookAndFeel() :
		    m_shape_impl{nullptr},
		    m_border_top{nullptr}, m_border_bottom{nullptr},
		    m_border_left{nullptr}, m_border_right{nullptr}
        {
            m_style.m_shape.m_type = RECTANGLE;
        }

		LookAndFeel(const std::string&, int, int, int, int);

		virtual ~LookAndFeel() {
            if(m_shape_impl != nullptr)
                delete m_shape_impl;
            if(m_border_bottom != nullptr)
                delete m_border_bottom;
            if(m_border_top != nullptr)
                delete m_border_top;
            if(m_border_left != nullptr)
                delete m_border_left;
            if(m_border_right != nullptr)
                delete m_border_right;
		}

		//void setShape(Shapes s) { m_shape_type = s; }
		void apply_current_changes();
		void setText();
		void setBorders();
		void update(const StyleData&);
        bool isDirty() const ;
		bool childrenNeedUpdate() const ;

        StyleData  m_style;

		virtual void update(int, int) = 0 ;
		virtual void draw(Window_Impl*) = 0 ;

		static bool LoadFonts();

	protected:

		StyleData  m_prev_style ;
		std::map<unsigned, std::vector<AnimCount*>> m_animations ;
		Shape *m_shape_impl ;
		Shape *m_border_top,*m_border_bottom ,*m_border_left, *m_border_right ;
		Text   m_text_impl ;
		RenderTexture m_texture ;

		static Font Regular ;
		static Font Bold ;
	};
}

#endif
