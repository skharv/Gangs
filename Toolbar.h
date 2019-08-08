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
	std::map <std::string, std::vector<Option*>> _optionSets;
public:
	void Update();
	void Draw(sf::RenderWindow &Window);
	void ShowToolbar(std::string optionSet);
	void HideToolbar();
	void AddOptionSet(std::string name, std::vector<Option*> option);
	//something something visibility?
	std::vector<Option*> GetActiveOptionSet() { return _optionSets[_activeOptionSet]; }

	Toolbar(sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile);
	Toolbar();
	~Toolbar();
};

#endif