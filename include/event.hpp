#ifndef __UX_EVENT_
#define __UX_EVENT_

#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include "typedefs.hpp"

namespace ux
{

    struct UXEvents
	{
		enum {
			Closed = 0u,
            Resized,
			LostFocus,
			GainedFocus,
			InFocus,
			OutFocus,
			TextEntered,
			KeyPressed,
			KeyReleased,
			MouseWheelMoved,
			MouseButtonPressed,
			MouseButtonReleased,
			MouseMoved,
			MouseEntered,
			MouseLeft,
			JoystickButtonPressed,
			JoystickButtonReleased,
			JoystickMoved,
			JoystickConnected,
			JoystickDisconnected,
			Count,
			CheckedStateChange,
			ListItemSelected,
			SliderValueChanged,
			StateToggled,
			None
		};
	};

    class EventID
    {
        unsigned int m_event_type ;
        unsigned int m_handler_id ;
        unsigned int m_component_id ;

    public:
        EventID(unsigned int x, unsigned int y, unsigned int z) :
            m_event_type{x}, m_handler_id{y}, m_component_id{z}
        {}

        bool operator==(const EventID& cmp) const
        {
            return (m_event_type == cmp.m_event_type) &&
                   (m_handler_id == cmp.m_handler_id) &&
                   (m_component_id == cmp.m_component_id);
        }

        friend class EventHandler ;
    };

    class EventHandler
	{
		static unsigned int seed ;

        // The following lambda does not do anything.
        // When event listeners are removed, they are NOT erased.
        // Instead, they are replaced with this lambda.
        static HandlerType NO_EVENT_HANDLER ;

	protected:
		std::map<unsigned int, std::vector<HandlerType>> m_callbacks;
		bool m_focused ;
		unsigned int m_id ;

	public:
		EventHandler();
		EventID addEventListener(int event, const HandlerType&);
		bool    removeEventListener(const EventID&);

		bool isFocused() const { return m_focused; }
		virtual void stealFocus() = 0 ;
		virtual void handleEvents(Event const&) = 0 ;
	};

}

#endif
