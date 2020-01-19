#ifndef _MOUSE_H
#define _MOUSE_H

#include <SFML/Graphics.hpp>
#include "Building.h"
#include "Option.h"
#include "Utility.h"
#include "ToolbarUtility.h"
#include "Camera.h"
#include <iostream>
#include "Grid.h"
#include "Unit.h"

class Option;
class ToolbarUtility;

class Mouse
{
private:
	Utility *_utility;
	Grid* _grid;
	Camera* _camera;
	std::map <std::string, Building*>* _buildingPatterns;
	std::map <std::string, Unit*>* _unitPatterns;
	ToolbarUtility *_toolbarUtility;
	//sf::Sprite _pointerSprite;
	sf::Vector2f _position;
	std::string _mouseState;
	bool _mousePressed;
	sf::Vector2f _mouseStart;
	sf::RectangleShape _mouseSelect;
	sf::ConvexShape _tileSelect;
	Building* _activeBuilding;
	Unit* _activeUnit;

	std::vector<Building*> _selectedBuildings;
	std::vector<Unit*> _selectedUnits;

	bool _mouseMovePressed;
	sf::Vector2f _mouseMoveStart;
	void Build(std::string s);
	void Create(std::string s);
	void Zone(std::string s, std::vector<Tile*> t);
	void SetTileIndex(std::string s, std::vector<Tile*> t);
	int GetTileCode(std::string s);
	int GetSocialClassCode(std::string s);
	void EditModeMouse(bool mouseIsPoint, sf::Vector2f mousePos, sf::RectangleShape shape);
	void GameModeMouse(bool mouseIsPoint, sf::Vector2f mousePos, sf::RectangleShape shape);
	std::string GetKeyString(std::string s);
public:
	void Update(sf::RenderWindow* Window);
	void DrawOver(sf::RenderWindow &Window);
	void DrawUnder(sf::RenderWindow &Window);
	void SetBuildingPatterns(std::map<std::string, Building*>* b);
	void SetUnitPatterns(std::map<std::string, Unit*>* u);
	void MouseMoveDown(sf::RenderWindow& Window);
	void MouseMoveUp();
	void ClearMouse();
	void MouseUp();
	void SetPosition(sf::Vector2f Position) { _position = Position; };
	void Click(sf::RenderWindow& Window);
	void RightClick(sf::RenderWindow& Window);
	void MouseDown(sf::RenderWindow& Window);
	void SetMouseState(std::string state);
	void MoveUnits(sf::Vector2f pos);

	Mouse(Utility* utility, ToolbarUtility* toolbarUtil, Grid* grid, Camera* camera);
	Mouse();
	~Mouse();
};

#endif