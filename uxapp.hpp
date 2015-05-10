#ifndef __UX_APP_
#define __UX_APP_

#include "component.hpp"

#include <thread>
#include <chrono>

namespace ux
{

	template <typename UIType>
	class UXApplication
	{

		bool            titlebar ;
		std::string     app_title ;

	protected:
		Window<UIType> *window ;
		typename UIType::Window* target ;
		typename UIType::View    view ;

	public:
		UXApplication();
		~UXApplication() {}

		bool hasTitlebar() const { return titlebar; }
		std::string getAppTitle() const { return app_title; }
		void setTitlebar(bool t, const std::string& str) { titlebar = t; app_title = str; }

		void draw();
		void add(Window<UIType>* w) { w->setRenderTarget(target, titlebar, app_title); window = w; }
		int run();

	};

	template <typename UIType>
	UXApplication<UIType>::UXApplication()
	{
	}

	template <typename UIType>
	void UXApplication<UIType>::draw()
	{
		target->clear();
		window->draw(target);
		target->display();
	}

	template <typename UIType>
	int UXApplication<UIType>::run()
	{
		typename UIType::Event event ;
		while(1)
		{
			if(GlobalDrawingStates::Redraw)
				draw();
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(30));
			while(target->pollEvent(event))
			{
				if(event.type == UIType::Event::Resized)
				{
					auto w = event.size.width, h = event.size.height ;
					view.reset(typename UIType::FRect(0, 0, w, h));
					target->setView(view);
				}
				window->handleEvents(event);
			}
			if(window->isClosed())
			{
				target->close();
				break;
			}
		}
		return EXIT_SUCCESS ;
	}

}

#endif
