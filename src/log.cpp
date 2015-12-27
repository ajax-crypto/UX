#include "../include/log.hpp"

namespace ux
{
    bool Logger::text = true ;
    bool Logger::preamble = true;
    bool Logger::layout = false;
    bool Logger::style = false;
    bool Logger::events = false ;

    std::string Logger::tabs = "";

    std::ostream& operator<<(std::ostream& stream, const sf::Color& c)
	{
		stream << "( " << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ", " << (int)c.a << " )" ;
		return stream ;
	}

	std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& v)
	{
		stream << "( " << v.x << ", " << v.y << " )" ;
		return stream ;
	}

}
