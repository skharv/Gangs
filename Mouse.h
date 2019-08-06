#ifndef _MOUSE_H
#define _MOUSE_H

#include <SFML/Graphics.hpp>

class Mouse
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;

	sf::Vector2f _position;
public:
	void Update(sf::Vector2f Position);
	void Draw(sf::RenderWindow &Window);

	void SetPosition(sf::Vector2f Position) { _position = Position; };

	Mouse(std::string FilePath);
	Mouse();
	~Mouse();
};

#endif