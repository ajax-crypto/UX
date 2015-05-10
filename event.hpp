#ifndef __UX_EVENT_
#define __UX_EVENT_

#include <vector>
#include <map>
#include <functional>
#include <iostream>

namespace ux
{

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

        template <typename> friend class EventHandler ;
    };

    template <typename UIType> class EventHandler
	{
		static unsigned int seed ;

		typedef typename UIType::Event EventType ;
        typedef std::function<void(EventType const&)> HandlerType ;

        // The following lambda does not o anything.
        // When event listeners are removed, they are NOT erased.
        // Instead, they are replaced with this lambda.
        static HandlerType NO_EVENT_HANDLER ;

	protected:
		std::map<int, std::vector<HandlerType>> callbacks;
		bool focused ;
		unsigned int id ;

	public:
		EventHandler();
		EventID addEventListener(int event, const HandlerType&);
		bool    removeEventListener(const EventID&);

		bool isFocused() const { return focused; }
		virtual void handleEvents(EventType const&) = 0 ;

	};

	template <typename E> unsigned int EventHandler<E>::seed = 0 ;
	template <typename E> typename EventHandler<E>::HandlerType
        EventHandler<E>::NO_EVENT_HANDLER = [](EventHandler<E>::EventType const&){};

	template <typename UIType>
	EventHandler<UIType>::EventHandler()
	{
		id = seed++ ;
		focused = false ;
	}

	template <typename UIType>
	EventID EventHandler<UIType>::addEventListener(int event, const HandlerType& f)
	{
	    callbacks[event].push_back(f);
	    return EventID(event, callbacks[event].size() - 1, id);
	}

    template <typename UIType>
	bool EventHandler<UIType>::removeEventListener(const EventID& eid)
	{
	    if(id == eid.component_id)
        {
            callbacks[eid.event_type][eid.handler_id] = NO_EVENT_HANDLER ;
            return true ;
        }
        return false ;
	}

	struct UXEvents
	{
		enum {
			Closed,
            Resized,
			LostFocus,
			GainedFocus,
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
			SliderValueChanged
		};
	};

}

#endif
