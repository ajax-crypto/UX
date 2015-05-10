#ifndef __UX_SFML_
#define __UX_SFML_

#include <SFML\Graphics.hpp>
#include "textbox.hpp"
#include "button.hpp"
#include "label.hpp"
#include "list.hpp"
#include "checkbox.hpp"
#include "radio.hpp"
#include "slider.hpp"
#include "window.hpp"
#include "uxapp.hpp"

namespace sux
{
	class UXRectangle : public sf::RectangleShape
	{
	public:
		UXRectangle() = default ;

		void setSize(float w, float h) { sf::RectangleShape::setSize(sf::Vector2f(w, h)); }
	};

	class UXRenderWindow : public sf::RenderWindow
	{

	public:
		using sf::RenderWindow::RenderWindow ;

		void setPosition(int w, int h) { sf::RenderWindow::setPosition(sf::Vector2i(w, h)); }
		void setSize(int w, int h) { sf::RenderWindow::setPosition(sf::Vector2i(w, h)); }
	};

	struct SFMLType
	{
		typedef sf::Color         Color ;
		typedef sf::Event         Event ;
		typedef sf::RenderTarget  RenderTarget ;
		typedef sf::RenderTexture RenderTexture ;
		typedef sf::Texture       Texture ;
		typedef sf::Image         Image ;
		typedef sf::View          View ;
		typedef sf::VideoMode     Screen ;
		typedef sf::RenderWindow  Window ;
		typedef sf::Font          Font ;
		typedef sf::Glyph         Glyph ;
		typedef sf::Text          Text ;
		typedef sf::Sprite        Sprite ;
		typedef sf::Keyboard      Keyboard ;
		typedef sf::CircleShape   CircleShape ;
		typedef sf::Shape         Shape ;

		typedef sf::Vector2f      Vec2f ;
		typedef sf::Vector2i      Vec2i ;
		typedef sf::Vector2u      Vec2u ;
		typedef sf::FloatRect     FRect ;
		typedef sf::IntRect       IRect ;

		typedef UXRenderWindow    TargetWindow ;
		typedef UXRectangle       RectangleShape ;
	};

	typedef ux::Button<SFMLType>                         SButton ;
	typedef ux::Textbox<SFMLType>                        STextbox ;
	typedef ux::Label<SFMLType>                          SLabel ;
	typedef ux::List<SFMLType>                           SList ;
	typedef ux::Checkbox<SFMLType>                       SCheckbox ;
	typedef ux::Radio<SFMLType>                          SRadio;
	typedef ux::Slider<SFMLType>                         SSlider;
	typedef ux::Window<SFMLType>                         SWindow ;
	typedef ux::Passwordbox<SFMLType>                    SPasswordBox ;
	typedef ux::PropertyStates<typename SFMLType::Color> ColorProperty ;
	typedef ux::PropertyStates<int>                      OutlineProperty ;

	typedef SFMLType::Color Color ;
	typedef SFMLType::Event Event ;
	typedef ux::UXEvents UXEvents ;

	class SUXApp : public ux::UXApplication<SFMLType>
	{

	public:
		SUXApp(const std::string&, int, int, bool);

		int run();
	};

	SUXApp::SUXApp(const std::string& str, int w, int h, bool title = true)
	: ux::UXApplication<SFMLType>()
	{
		sf::ContextSettings settings ;
		settings.antialiasingLevel = 8;
		setTitlebar(title, str);
		if(title)
			target = new UXRenderWindow(sf::VideoMode(w, h), str, sf::Style::Default, settings);
		else
			target = new UXRenderWindow(sf::VideoMode(w, h), "", sf::Style::None, settings);
		view.setCenter(typename SFMLType::Vec2f(w/2, h/2));
		view.setSize(typename SFMLType::Vec2f(w, h));
		view.setViewport(typename SFMLType::FRect(0.0f, 0.0f, 1.0f, 1.0f));
		target->setView(this->view);
		ux::LoadFonts<SFMLType>();
	}

	int SUXApp::run()
	{
		return ux::UXApplication<SFMLType>::run();
	}

}

#endif
