#ifndef __UX_APP_
#define __UX_APP_

#include "component.hpp"
#include "window.hpp"

#include <thread>
#include <chrono>

namespace ux
{

	class UXApplication
	{
		bool            titlebar ;
		std::string     app_title ;

	protected:
		Window *window ;
		Window_Impl* target ;
		View    view ;

	public:
		UXApplication() : titlebar{false} {}
		virtual ~UXApplication() {}

		bool hasTitlebar() const { return titlebar; }
		std::string getAppTitle() const { return app_title; }
		void setTitlebar(bool t, const std::string& str) { titlebar = t; app_title = str; }

		void draw();
		void add(Window* w) { window = w; }
		int run();
	};

}

#endif
