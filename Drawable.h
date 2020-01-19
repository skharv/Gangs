#ifndef _DRAWABLE_H
#define _DRAWABLE_H

#include <SFML/Graphics.hpp>

class Drawable
{
protected:
	sf::Texture					_texture;
	sf::Sprite					_sprite;
	bool _validLocation;
	bool _placed;
public:
	sf::Vector2f GetPosition() { return _sprite.getPosition(); };

	void Draw(sf::RenderWindow &Window)
	{
		if (!_placed)
		{
			if (_validLocation)
				_sprite.setColor(sf::Color(255, 255, 255, 200));
			else
				_sprite.setColor(sf::Color(174, 25, 7, 200));
		}
		Window.draw(_sprite);
	};
	
	Drawable() {};

};

#endif