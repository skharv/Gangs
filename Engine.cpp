#include "pch.h"
#include "Engine.h"

#include <iostream>

bool Engine::Init()
{
	_window = new sf::RenderWindow(sf::VideoMode(1200, 768), "Gangs");

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
	}
}

void Engine::Update()
{
}

void Engine::RenderFrame()
{
	_window->clear(sf::Color().Black);
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
