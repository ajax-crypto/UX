#ifndef __UX_UI_ELEMENT_
#define __UX_UI_ELEMENT_

#include "style.hpp"

namespace ux
{
	class AnimCount ;
	class Window ;

	class LookAndFeel
	{
    public:

        enum { WaitCursor, TextCursor, ArrowCursor, HandCursor };

		LookAndFeel() :
		    shape_impl{nullptr}, border_top{nullptr},
		    border_bottom{nullptr}, border_left{nullptr},
		    border_right{nullptr} {}
		LookAndFeel(const std::string&, int, int, int, int);
		virtual ~LookAndFeel() {  }

		void setShape(Shapes s) { shape_type = s; }
		void imbue_properties();
		void apply_current_changes();
		void setText(const std::string&);

		StyleData  style;

		virtual void update(int, int) = 0 ;
		virtual void draw(Window_Impl*) = 0 ;

		static bool LoadFonts();

	protected:

		int cursor ;
		Shapes shape_type ;
		StyleData  prev_style ;
		std::map<unsigned, std::vector<AnimCount*>> animations ;
		std::map<unsigned int, StyleData> state_styles ;

		Shape *shape_impl ;
		Shape *border_top,*border_bottom ,*border_left, *border_right ;
		Text   text_impl ;
		RenderTexture texture ;
		static Font Regular ;
		static Font Bold ;

	};
}

#endif
