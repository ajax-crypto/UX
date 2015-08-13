#ifndef __UX_WINDOW_
#define __UX_WINDOW_

#include "component.hpp"
#include <vector>

namespace ux
{

	struct Animator
    {
        static bool Animate();
        static unsigned int global_delta ;
    };

	class Window : public Component
	{
		int dcalls = 1 ;
		bool closed ;

        TargetWindow* target ;
		RectangleShape shape ;
		unsigned int last_event ;

	public:
		Window(int, int);

		void handleEvents(const Event&);
		bool isClosed() const { return closed; }
		void draw(Window_Impl*);
		void setRenderTarget(Window_Impl* t) { target = dynamic_cast<TargetWindow*>(t); }
		void update(int, int) {}

		Color background_color ;

		friend class Animator ;
	};
}

#endif
