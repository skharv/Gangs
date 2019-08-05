#include "pch.h"
#include "Engine.h"

#include <iostream>

bool Engine::Init()
{
	_window = new sf::RenderWindow(sf::VideoMode(1200, 768), "Gangs");
	_window->setVerticalSyncEnabled(true);

	_camera = new Camera(sf::Vector2f(1200, 768));
	_cameraDirection = new sf::Vector2f(0, 0);

	_rect = new sf::RectangleShape(sf::Vector2f(100, 100));
	_rect->setOrigin(_rect->getSize().x / 2, _rect->getSize().y / 2);
	_rect->setFillColor(sf::Color::White);

	if (!_window)
		return false;

	return true;
}

void Engine::MainLoop()
{
	while (_window->isOpen())
	{
		ProcessInput();

		Update();

		RenderFrame();
	}
}

void Engine::ProcessInput()
{
	sf::Event evt;

	while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window->close();

		if (evt.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				_cameraDirection = new sf::Vector2f(0, 1);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				_cameraDirection = new sf::Vector2f(0, -1);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				_cameraDirection = new sf::Vector2f(-1, 0);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_cameraDirection = new sf::Vector2f(1, 0);
		}
		else
			_cameraDirection = new sf::Vector2f(0, 0);
	}
}

void Engine::Update()
{
	_camera->ApplyVector(*_cameraDirection);
	_camera->Update(*_window);
}

void Engine::RenderFrame()
{
	_window->clear(sf::Color().Black);
	_window->draw(*_rect);
	_window->display();
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}
