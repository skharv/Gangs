#ifndef _MOUSE_H
#define _MOUSE_H

#include <SFML/Graphics.hpp>
#include "Option.h"

class Mouse
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;

	sf::Vector2f _position;

	bool CheckButtonClick(std::vector <std::vector<Option*>>* activeOptions);
public:
	void Update(sf::Vector2f Position);
	void Draw(sf::RenderWindow &Window);

	void SetPosition(sf::Vector2f Position) { _position = Position; };
	void Click(std::string mouseState, std::vector <std::vector<Option*>>* activeOptions);

	Mouse(std::string FilePath);
	Mouse();
	~Mouse();
};

#endif