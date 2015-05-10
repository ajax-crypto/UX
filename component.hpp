#ifndef __UX_COMPONENT_
#define __UX_COMPONENT_

#include "event.hpp"
#include "uielement.hpp"
#include "ranged.hpp"

namespace ux
{
	template <typename UIType>
	class Component :
	public UIElement<UIType>,
	public EventHandler<UIType>
	{
	protected:
		Component(const std::string& str, int x, int y, int w, int h) :
		UIElement<UIType>(str, x, y, w, h),
		EventHandler<UIType>(),
		parent{nullptr}, enabled{true}
		{

		}

		template <typename> friend class Window ;

		bool enabled ;
		Component<UIType>* parent ;
		std::vector<Component<UIType>*> children ;

	public:
		void add(Component<UIType>* c) { c->parent = this; children.push_back(c); }
		void setFocus() { this->focused = true; this->setActiveColor(); }
		void removeFocus() { this->focused = false; this->setInactiveColor(); }
		void enable() { enabled = true; }
		void disable() { enabled = false; }
		bool isEnabled() const { return enabled; }
		unsigned int getId() const { return EventHandler<UIType>::id; }

		bool operator==(const Component<UIType>& c)
		{
		    return EventHandler<UIType>::id == c.id ;
		}
	};
}

#endif
