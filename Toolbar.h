#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Option.h"

class Option;
class Utility;

class Toolbar
{
private:
	Utility *_utility;
	bool _active = false;
	bool _visible = true;
	sf::Texture _bgTexture;
	sf::Sprite _bgSprite;
	std::string _activeOptionSet;
	std::string _primaryOptionSet;
	std::map <std::string, std::vector<Option*>> _optionSets;
	sf::Vector2f _position;
	sf::Keyboard::Key _shortCut;
	Option* _activeOption;
	void ClickOption(Option* selected);
public:
	void Update(sf::Vector2f camPos);
	void Draw(sf::RenderWindow &Window);
	void ShowToolbar(std::string optionSet);
	void HideToolbar();
	void SetInvisible() { _visible = false; };
	void AddOptionSet(std::string name, std::vector<Option*> option);
	bool CheckShortCutKeys();
	bool CheckButtonClick(sf::Vector2f mousePos);
	std::vector<Option*> GetActiveOptionSet();

	Toolbar(sf::Vector2f pos, sf::Vector2i size, std::string imageFile, Utility* utility);
	Toolbar(sf::Vector2f pos, sf::Vector2i size, std::string imageFile, sf::Keyboard::Key shortCut, std::string primary, Utility* utility);
	Toolbar();
	~Toolbar();
};

#endif