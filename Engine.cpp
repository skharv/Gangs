#include "Engine.h"

bool Engine::Init()
{
	_window = new sf::RenderWindow(sf::VideoMode(1200, 768), "Gangs");
	_window->setVerticalSyncEnabled(true);

	_camera = new Camera(sf::Vector2f(1200, 768));
	_camera->SetMoveSpeed(20);

	_grid = new Grid(sf::Vector2f(100, 100));

	_mouse = new Mouse("images/gridsection.png");

	_utility = new Utility();
	_utility->setGridSize(_grid->GetSize());

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_camera->AddToMoveDirection(0, 1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			_camera->AddToMoveDirection(0, -1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_camera->AddToMoveDirection(-1, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_camera->AddToMoveDirection(1, 0);
	}
}

void Engine::Update()
{
	_camera->Update(*_window);
	sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
	mousePos = _utility->WorldToGrid(mousePos);
	mousePos = _utility->GridToWorld(mousePos);
	_mouse->Update(mousePos);
}

void Engine::RenderFrame()
{
	_window->clear(sf::Color().Black);
	_grid->Draw(*_window);
	_mouse->Draw(*_window);
	_window->display();
}

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}
