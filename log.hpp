#ifndef __UX_LOG_
#define __UX_LOG_

#include <iostream>

namespace ux
{
	std::ostream& operator<<(std::ostream& stream, const sf::Color& c)
	{
		stream << "( " << (int)c.r << " " << (int)c.g << " " << (int)c.b << " )" ;
		return stream ;
	}
	
	void log(std::string str) { std::cout << "\n" << str ; }
}

#endif