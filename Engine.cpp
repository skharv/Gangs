#include "Engine.h"

bool Engine::Init()
{
	_window = new sf::RenderWindow(sf::VideoMode(1200, 768), "Gangs");
	_window->setVerticalSyncEnabled(true);

	_camera = new Camera(sf::Vector2f(1200, 768));
	_cameraDirection = new sf::Vector2f(0, 0);

	_grid = new Grid(sf::Vector2f(100, 100));

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
				_cameraDirection = new sf::Vector2f(0, 10);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				_cameraDirection = new sf::Vector2f(0, -10);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				_cameraDirection = new sf::Vector2f(-10, 0);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_cameraDirection = new sf::Vector2f(10, 0);
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
	_grid->Draw(*_window);
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
