#include "Unit.h"

void Unit::Update()
{
	float _distance;

	if (_target != this && _target != nullptr)
	{
		if (_state != ATTACK)
			_state = MOVE;

		if (GetMagnitude(_target->GetPosition() - _position) < _attackRange && _target->GetPlayerNumber() != _playerNumber)
			_state = ATTACK;
		if (!_destination.empty())
			_destination.pop_back();
		_destination.push_back(_target->GetPosition());

	}

	switch (_state)
	{
	case IDLE:
		_animationFrame = 0;
		break;
	case MOVE:
		_distance = 0;

		if (++_animationFrame >= (_texture.getSize().y / 32))
			_animationFrame = 0;
		_animationCounter = 0;

		if(!_destination.empty())
		  _distance = GetMagnitude(_destination.back() - _position);

		if (_distance > _stopDistance)
		{
			_destination.back() += _neighbourInfluence;
			_velocity = Seek(_destination.back());

			_forward = Normalise(_velocity);
			_rotation = atan2(_forward.y, _forward.x) * 180 / 3.14159;

			_position += _velocity;

			if (_distance < _slowingDistance && _destination.size() > 1)
			{
				_destination.pop_back();
			}
		}
		else
		{
			if (_destination.size() > 1)
				_destination.pop_back();
			else
				_state = IDLE;
		}

		_neighbourInfluence = sf::Vector2f(0, 0);
		break;
	case ATTACK:
		if (GetMagnitude(_target->GetPosition() - _position) > _attackRange)
			_state = MOVE;
		break;
	default:
		break;
	}

	_sprite.setPosition(_position);
	_sprite.setScale(1, 1);

	sf::IntRect Rect = sf::IntRect(0, _animationFrame * 32, 16, 32);

	//ewwwwww....
	if (_rotation < -168.75)
	{
		_sprite.setScale(-1, 1);
		Rect.left = 48;
	}
	else if (_rotation < -146.25)
	{
		_sprite.setScale(-1, 1);
		Rect.left = 32;
	}
	else if (_rotation < -123.75)
	{
		_sprite.setScale(-1, 1);
		Rect.left = 16;
	}
	else if (_rotation < -101.25)
	{
		Rect.left = 0;
	}
	else if (_rotation < -78.75)
	{
		Rect.left = 16;
	}
	else if (_rotation < -56.25)
	{
		Rect.left = 32;
	}
	else if (_rotation < -33.75)
	{
		Rect.left = 48;
	}
	else if (_rotation < -11.25)
	{
		Rect.left = 64;
	}
	else if (_rotation < 11.25)
	{
		Rect.left = 64;
	}
	else if (_rotation < 33.75)
	{
		Rect.left = 80;
	}
	else if (_rotation < 56.25)
	{
		Rect.left = 96;
	}
	else if (_rotation < 78.75)
	{
		Rect.left = 112;
	}
	else if (_rotation < 101.25)
	{
		Rect.left = 128;
	}
	else if (_rotation < 123.75)
	{
		_sprite.setScale(-1, 1);
		Rect.left = 112;
	}
	else if (_rotation < 146.25)
	{
		_sprite.setScale(-1, 1);
		Rect.left = 96;
	}
	else if (_rotation < 168.75)
	{
		_sprite.setScale(-1, 1);
		Rect.left = 80;
	}
	else if (_rotation < 180)
	{
		_sprite.setScale(-1, 1);
		Rect.left = 64;
	}
	//end of ewww....

	_sprite.setTextureRect(Rect);
}

float Unit::GetMagnitude(sf::Vector2f v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

sf::Vector2f Unit::Normalise(sf::Vector2f v)
{
	float length = GetMagnitude(v);
	if (length != 0)
		return sf::Vector2f(v.x / length, v.y / length);
	else
		return v;
}

sf::Vector2f Unit::Truncate(sf::Vector2f v, float max)
{
	if (GetMagnitude(v) > max)
	{
		v = Normalise(v);

		return sf::Vector2f(v.x * max, v.y * max);
	}

	return v;
}

sf::Vector2f Unit::Seek(sf::Vector2f v)
{
	float _distance = GetMagnitude(v - _position);

	//-----Seeking with Arrival-----//
	float _rampedSpeed = _moveSpeed * (_distance / _slowingDistance);
	float _clippedSpeed = _moveSpeed < _rampedSpeed ? _moveSpeed : _rampedSpeed;

	// Normalise the desired velocity vector then scale it by the maximum speed.
	_desiredVelocity = Normalise(v - _position);
	_desiredVelocity = sf::Vector2f(_desiredVelocity.x * _clippedSpeed, _desiredVelocity.y * _clippedSpeed);

	// Calculate how much to steer (again, normalising and scaling).
	_steerForce = Truncate(_desiredVelocity - _velocity, _steerSpeed);

	// Generate the new velocity.
	_newVelocity = Normalise(_velocity + _steerForce);
	_newVelocity = sf::Vector2f(_newVelocity.x * _clippedSpeed, _newVelocity.y * _clippedSpeed);

	// Update the current velocity.
	return _newVelocity;
}

void Unit::Separation(std::vector<Unit> units)
{
	float separationDist = 50.0f;
	sf::Vector2f influence(0, 0);
	int count = 0;

	for (int i = 0; i < units.size(); i++)
	{
		float distance = GetMagnitude(units[i].GetPosition() - _position);

		if (distance > 0 && distance < separationDist)
		{
			sf::Vector2f diff(0, 0);
			diff = _position - units[i].GetPosition();
			diff = Normalise(diff);
			diff = sf::Vector2f(diff.x / distance, diff.y / distance);
			influence += diff;

			count++;
		}
	}

	if (count > 0)
		influence = sf::Vector2f(influence.x / count, influence.y / count);
	if (GetMagnitude(influence) > 0)
	{
		influence = Normalise(influence);
		influence = sf::Vector2f(influence.x * _moveSpeed, influence.y * _moveSpeed);
		influence -= _velocity;
		influence = Truncate(influence, _steerSpeed);

		_neighbourInfluence += influence;
	}
}

void Unit::Alignment(std::vector<Unit> units)
{
	sf::Vector2f sum(0, 0);

	int count = 0;
	for (int i = 0; i < units.size(); i++)
	{
		float distance = GetMagnitude(units[i].GetPosition() - _position);

		if (distance > 0 && distance < _neighbourDistance)
		{
			sum += units[i].GetVelocity();
			count++;
		}
	}

	if (count > 0)
	{
		sum = sf::Vector2f(sum.x / count, sum.y / count);
		sum = Normalise(sum);
		sum = sf::Vector2f(sum.x * _moveSpeed, sum.y * _moveSpeed);

		sf::Vector2f influence = sum - _velocity;
		influence = Truncate(influence, _steerSpeed);

		_neighbourInfluence += influence;
	}
}

void Unit::Cohesion(std::vector<Unit> units)
{
	sf::Vector2f sum(0, 0);

	int count = 0;
	for (int i = 0; i < units.size(); i++)
	{
		float distance = GetMagnitude(units[i].GetPosition() - _position);

		if (distance > 0 && distance < _neighbourDistance)
		{
			sum += units[i].GetPosition();
			count++;
		}
	}

	if (count > 0)
	{
		sum = sf::Vector2f(sum.x / count, sum.y / count);

		Seek(sum);
	}
}

void Unit::Move(Grid grid, sf::Vector2f dest, bool queue)
{
	_state = MOVE;
	_target = this;

	_destination = AStar::aStar(Utility::IsoWorldToGrid(GetPosition(), grid.GetTileSize()), Utility::IsoWorldToGrid(dest, grid.GetTileSize()), grid);
}

void Unit::Target(Unit * o)
{
	_target = o;
}

Unit::Unit()
{
}

Unit::Unit(Unit *u)
{
}

Unit::Unit(std::string TextureLocation, sf::Vector2f Size)
{
	sf::IntRect Rect = sf::IntRect(0, 0, Size.x, Size.y);

	_origin = sf::Vector2f(8, 28);
	_position = sf::Vector2f(0, 0);

	_texture.loadFromFile(TextureLocation);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(Rect);
	_sprite.setOrigin(_origin);
	_placed = false;
	_target = nullptr;
}

void Unit::PlacementUpdate(Tile* t)
{
	if(_highlightTile != NULL)
		_highlightTile->SetColour(sf::Color::White);

	if (t != NULL)
	{
		_highlightTile = t;
		_sprite.setPosition(t->GetPosition());
		_position = t->GetPosition();
		if (t == NULL || t->GetOccupiedStatus())
		{
			t->SetColour(sf::Color::Red);
			_validLocation = false;
		}
		else
		{
			t->SetColour(sf::Color::Green);
			_validLocation = true;
		}
	}
}

void Unit::CancelPlacement()
{
	_highlightTile->SetColour(sf::Color::White);
}

void Unit::PlaceUnit()
{
	if (_validLocation)
	{
		_placed = true;
		_sprite.setColor(sf::Color::White);
		_highlightTile->SetColour(sf::Color::White);
	}
}

Unit::~Unit()
{
}
