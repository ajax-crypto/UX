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
		    m_shape_impl{nullptr}, m_border_top{nullptr},
		    m_border_bottom{nullptr}, m_border_left{nullptr},
		    m_border_right{nullptr} {}
		LookAndFeel(const std::string&, int, int, int, int);
		virtual ~LookAndFeel() {  }

		void setShape(Shapes s) { m_shape_type = s; }
		void apply_current_changes();
		void setText(const std::string&);
		void update(const StyleData& parent);
		bool updatableChange() const ;

        StyleData  m_style;

		virtual void update(int, int) = 0 ;
		virtual void draw(Window_Impl*) = 0 ;

		static bool LoadFonts();

	protected:

		Shapes     m_shape_type ;
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
