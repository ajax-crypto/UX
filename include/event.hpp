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
        unsigned int event_type ;
        unsigned int handler_id ;
        unsigned int component_id ;

    public:
        EventID(unsigned int x, unsigned int y, unsigned int z) :
            event_type{x}, handler_id{y}, component_id{z}
        {}

        bool operator==(const EventID& cmp) const
        {
            return (event_type == cmp.event_type) &&
                   (handler_id == cmp.handler_id) &&
                   (component_id == cmp.component_id);
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
		std::map<unsigned int, std::vector<HandlerType>> callbacks;
		bool focused ;
		unsigned int id ;

	public:
		EventHandler();
		EventID addEventListener(int event, const HandlerType&);
		bool    removeEventListener(const EventID&);

		bool isFocused() const { return focused; }
		virtual void stealFocus() = 0 ;
		virtual void handleEvents(Event const&) = 0 ;
	};

}

#endif
