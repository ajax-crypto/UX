#ifndef __UX_LOG_
#define __UX_LOG_

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

namespace ux
{

    std::ostream& operator<<(std::ostream& stream, const sf::Color& c);
	std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& v);
	void log(std::string str);

	//std::ofstream log_file{"log.txt"};

#ifdef RT
    #define STREAM std::cout
#else
    #define STREAM log_file
#endif

#ifdef UX_DEBUG
    #define LOG(X) do { STREAM << "\n" << __FILE__ << "::[" << __LINE__ << "]\t" << X << std::endl; } while(0)
#else
    #define LOG(X) ;
#endif

#ifdef FUNC_INFO
    #define START do { STREAM << "Starting... " << __PRETTY_FUNCTION__ << "\n\n"; } while(0)
#else
    #define START ;
#endif

#ifdef FUNC_INFO
    #define END do { STREAM << "Ending...  " << __PRETTY_FUNCTION__ << "\n\n"; } while(0)
#else
    #define END ;
#endif

#ifdef UX_DEBUG
    #define ASSERT(cond, print) do { if(!(cond)) LOG(print); } while(0)
#else
    #define ASSERT ;
#endif

#ifdef UX_DEBUG
   #define PAUSE do { std::cin.ignore(); } while(0)
#else
    #define PAUSE ;
#endif

}

#endif
