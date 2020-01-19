#ifndef _UNIT_H
#define _UNIT_H

#include <SFML/Graphics.hpp>
#include <stack>
#include <iostream>
#include "Utility.h"
#include "AStar.h"
#include "Grid.h"
#include "Drawable.h"

#define DEFAULTFORWARD sf::Vector2f(0, -1)
#define ANIMFRAMES 3

enum States
{
	IDLE = 0,
	MOVE = 1,
	ATTACK = 2
};

class Unit : public Drawable
{
private:
	Unit					   *_target = this;
	Utility						_util;

	// Where it is and where it's going:
	sf::Vector2f				_origin;
	sf::Vector2f				_position;
	sf::Vector2f				_velocity;
	//std::stack<sf::Vector2f>	_destination;
	std::vector<sf::Vector2f>	_destination;
	sf::Vector2f				_newVelocity;
	sf::Vector2f				_desiredVelocity;
	sf::Vector2f				_steerForce;
	sf::Vector2f				_forward;
	sf::Vector2f				_neighbourInfluence;

	float 						_moveSpeed = 2.5;
	float 						_steerSpeed = 5;
	float						_rotation = 0;
	float						_attackRange = 300.0f;
	float						_slowingDistance = 25.0f;
	float						_neighbourDistance = 50.0f;
	float						_stopDistance = 1.0f;

	// Unit Stats:
	int							_playerNumber;
	States						_state = IDLE;
	float 						_currentHealth;
	float 						_healthTotal;
	float						_healthPoint;
	float 						_buildTime;

	// Private functions:
	float						GetMagnitude(sf::Vector2f v);
	sf::Vector2f				Normalise(sf::Vector2f v);
	sf::Vector2f				Truncate(sf::Vector2f v, float max);
	sf::Vector2f				Seek(sf::Vector2f v);

	Tile*						_highlightTile;
public:
	void Update();

	int GetPlayerNumber() { return _playerNumber; };
	float GetBuildTime() { return _buildTime; };
	float GetMoveSpeed() { return _moveSpeed; };
	float GetSteerSpeed() { return _steerSpeed; };
	sf::Vector2f GetPosition() { return _position; };
	sf::Vector2f GetVelocity() { return _velocity; };

	void SetPosition(int x, int y) { _position = sf::Vector2f(x, y); };
	void SetMoveSpeed(float val) { _moveSpeed = val; };
	void SetSteerSpeed(float val) { _steerSpeed = val; };

	void Separation(std::vector<Unit> units);
	void Alignment(std::vector<Unit> units);
	void Cohesion(std::vector<Unit> units);

	void Move(Grid grid, sf::Vector2f dest, bool queue);
	void Target(Unit *o);

	void PlaceUnit();
	void CancelPlacement();
	void PlacementUpdate(Tile* t);
	bool ValidPlacement() { return _validLocation; };

	sf::Sprite GetSprite() { return _sprite; };

	Unit();
	Unit(Unit * u);
	Unit(std::string TextureLocation, sf::Vector2f Size);
	~Unit();
};

#endif