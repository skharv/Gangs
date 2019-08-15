#include "Camera.h"

void Camera::AddToMoveDirection(sf::Vector2f Direction)
{
	if (Direction.x >= 1)
		Direction.x = 1;
	else if (Direction.x <= -1)
		Direction.x = -1;
	else
		Direction.x = 0;

	if (Direction.y >= 1)
		Direction.y = 1;
	else if (Direction.y <= -1)
		Direction.y = -1;
	else
		Direction.y = 0;

	_moveDirection += Direction;
}

void Camera::AddToMoveDirection(float X, float Y)
{
	sf::Vector2f _direction = sf::Vector2f(X, Y);

	if (_direction.x >= 1)
		_direction.x = 1;
	else if (_direction.x <= -1)
		_direction.x = -1;
	else
		_direction.x = 0;

	if (_direction.y >= 1)
		_direction.y = 1;
	else if (_direction.y <= -1)
		_direction.y = -1;
	else
		_direction.y = 0;

	_moveDirection += _direction;
}

void Camera::Update(sf::RenderWindow &Window)
{
	_position += _moveDirection * _moveSpeed;

	_view.setCenter(sf::Vector2f(_position));
	_uiView.setCenter(sf::Vector2f(_position));

	_moveDirection = sf::Vector2f(0, 0);

	Window.setView(_view);
}

void Camera::setUIView(sf::RenderWindow &Window)
{
	Window.setView(_uiView);
}

void Camera::setGridView(sf::RenderWindow &Window)
{
	Window.setView(_view);
}

Camera::Camera(sf::Vector2f Size)
{
	_moveSpeed = 1;
	_size = Size;
	_position = sf::Vector2f(0, 0);
	_view.reset(sf::FloatRect(0, 0, _size.x, _size.y));
	_view.setCenter(sf::Vector2f(_position));
	_uiView.reset(sf::FloatRect(0, 0, _size.x, _size.y));
	_uiView.setCenter(sf::Vector2f(_position));
}

Camera::Camera()
{
}

Camera::~Camera()
{
}