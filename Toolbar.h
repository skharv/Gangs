#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Option.h"

class Option;

class Toolbar
{
private:
	bool _visible = false;
	sf::Texture _bgTexture;
	sf::Sprite _bgSprite;
	std::string _activeOptionSet;
	std::string _primaryOptionSet;
	std::map <std::string, std::vector<Option*>> _optionSets;
	sf::Vector2f _position;
	sf::Keyboard::Key _shortCut;
public:
	void Update(sf::Vector2f camPos);
	void Draw(sf::RenderWindow &Window);
	void ShowToolbar(std::string optionSet);
	void HideToolbar();
	void AddOptionSet(std::string name, std::vector<Option*> option);
	bool CheckShortCutKeys();
	std::vector<Option*> GetActiveOptionSet();

	Toolbar(sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile);
	Toolbar(sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile, sf::Keyboard::Key shortCut, std::string primary);
	Toolbar();
	~Toolbar();
};

#endif