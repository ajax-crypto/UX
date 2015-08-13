#include "../include/log.hpp"

namespace ux
{
    bool logger::logging = true ;
    
    std::ostream& operator<<(std::ostream& stream, const sf::Color& c)
	{
		stream << "( " << (int)c.r << " " << (int)c.g << " " << (int)c.b << " )" ;
		return stream ;
	}

	std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& v)
	{
		stream << "( " << v.x << " " << v.y << " )" ;
		return stream ;
	}

	void log(std::string str) { std::cout << "\n" << str ; }
}
