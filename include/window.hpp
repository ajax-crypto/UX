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
		int m_dcalls = 1 ;
		bool m_closed ;

        TargetWindow* m_target ;
		RectangleShape m_shape ;
		unsigned int m_last_event ;

	public:
		Window(int, int);

		void handleEvents(const Event&);
		bool isClosed() const { return m_closed; }
		void draw(Window_Impl*);
		void setRenderTarget(Window_Impl* t) { m_target = dynamic_cast<TargetWindow*>(t); }
		void update(int, int) {}

		Color m_background_color ;

		friend class Animator ;
	};
}

#endif
