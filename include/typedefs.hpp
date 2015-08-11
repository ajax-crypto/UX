#ifndef __UX__TYPEDEFS__
#define __UX__TYPEDEFS__

#include <SFML\Graphics.hpp>
#include "log.hpp"

namespace ux
{
    class UXRenderWindow : public sf::RenderWindow
	{

	public:
		using sf::RenderWindow::RenderWindow ;

		void setPosition(int w, int h) { sf::RenderWindow::setPosition(sf::Vector2i(w, h)); }
		void setSize(int w, int h) { sf::RenderWindow::setPosition(sf::Vector2i(w, h)); }
	};

    typedef sf::Color        Color ;
    typedef sf::Event          Event ;
    typedef sf::RenderTarget   RenderTarget ;
    typedef sf::RenderTexture  RenderTexture ;
    typedef sf::Texture        Texture ;
    typedef sf::Image          Image ;
    typedef sf::View           View ;
    typedef sf::VideoMode      Screen ;
    typedef sf::RenderWindow   Window_Impl ;
    typedef sf::Font           Font ;
    typedef sf::Glyph          Glyph ;
    typedef sf::Text           Text ;
    typedef sf::Sprite         Sprite ;
    typedef sf::Keyboard       Keyboard ;
    typedef sf::CircleShape    CircleShape ;
    typedef sf::RectangleShape RectangleShape ;
    typedef sf::Shape          Shape ;

    typedef sf::Vector2f       Vec2f ;
    typedef sf::Vector2i       Vec2i ;
    typedef sf::Vector2u       Vec2u ;
    typedef sf::FloatRect      FRect ;
    typedef sf::IntRect        IRect ;
    typedef sf::Uint8          Uint8 ;

    typedef UXRenderWindow     TargetWindow ;

    typedef std::function<bool(bool)> anim_func ;
    typedef std::function<void(Event const&)> HandlerType ;

}

#endif // __UX__TYPEDEFS__
