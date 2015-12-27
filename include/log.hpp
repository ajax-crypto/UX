#ifndef __UX_LOG_
#define __UX_LOG_

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

namespace ux
{

    std::ostream& operator<<(std::ostream&, const sf::Color&);
	std::ostream& operator<<(std::ostream&, const sf::Vector2f&);

	struct Logger
	{
        static bool text ;
        static bool preamble ;
        static bool style ;
        static bool layout ;
        static bool events ;

		static std::string tabs ;
	};

}

#define __UX_DEBUG 1

#ifdef __UX_DEBUG

#define STREAM std::cout

#define LOG(X) if(Logger::text) { \
    STREAM << Logger::tabs << "[" << __LINE__ << "]:  " << X << std::endl; \
}

#define LAYOUT_LOG(X) if(Logger::layout) { \
    STREAM << Logger::tabs << "[" << __LINE__ << "]:  " << X << std::endl; \
}

#define START if(Logger::preamble) { \
    STREAM << Logger::tabs << "--------------------------------------------------------\n"; \
    STREAM << Logger::tabs << "Starting... " << __PRETTY_FUNCTION__ << "\n";\
    STREAM << Logger::tabs << "--------------------------------------------------------\n"; \
    Logger::tabs += "  "; \
}

#define END if(Logger::preamble) { \
    Logger::tabs = Logger::tabs.substr(0, Logger::tabs.size()-2); \
    STREAM << Logger::tabs << "--------------------------------------------------------\n"; \
    STREAM << Logger::tabs << "Ending...  " << __PRETTY_FUNCTION__ << "\n"; \
    STREAM << Logger::tabs << "--------------------------------------------------------\n"; \
}

#define LOGSTYLE if(Logger::style) { \
    LOG("*********************Styles**********************"); \
    LOG("style.content = "  << m_style.m_content); \
    LOG("style.shape = "  << m_style.m_shape); \
    LOG("style.padding = "  << m_style.m_padding); \
    LOG("style.border = "  << m_style.m_border); \
    LOG("style.margin = "  << m_style.m_margin); \
}

#define EVENT_START if(Logger::events) { \
    STREAM << Logger::tabs << "--------------------------------------------------------\n"; \
    STREAM << Logger::tabs << "Starting... " << __PRETTY_FUNCTION__ << "\n";\
    STREAM << Logger::tabs << "--------------------------------------------------------\n"; \
    Logger::tabs += "  "; \
}

#define EVENT_END if(Logger::events) { \
    Logger::tabs = Logger::tabs.substr(0, Logger::tabs.size()-2); \
    STREAM << Logger::tabs << "--------------------------------------------------------\n"; \
    STREAM << Logger::tabs << "Ending...  " << __PRETTY_FUNCTION__ << "\n"; \
    STREAM << Logger::tabs << "--------------------------------------------------------\n"; \
}

#define ASSERT(cond, print) do { if(!(cond)) LOG(print); } while(0)

#define PAUSE do { std::cin.ignore(); } while(0)

#else

#define STREAM
#define LOG(X)
#define START
#define END
#define LOGSTYLE
#define EVENT_START
#define EVENT_END
#define ASSERT
#define PAUSE

#endif

#endif
