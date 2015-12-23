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

	struct logger {
		static bool logging  ;
	};

}

#define STREAM std::cout
#define LOG(X) if(logger::logging) { STREAM << "\n" << __FILE__ << "::[" << __LINE__ << "]\t" << X << std::endl; }
#define START if(logger::logging) { STREAM << "Starting... " << __PRETTY_FUNCTION__ << "\n\n"; }
#define END if(logger::logging) { STREAM << "Ending...  " << __PRETTY_FUNCTION__ << "\n\n"; }
#define ASSERT(cond, print) do { if(!(cond)) LOG(print); } while(0)
#define PAUSE do { std::cin.ignore(); } while(0)

#endif
