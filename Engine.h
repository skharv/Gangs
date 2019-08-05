#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML\Graphics.hpp>

class Engine
{
private:
	sf::RenderWindow *_window;

	bool Init();
	void MainLoop();
	void ProcessInput();
	void RenderFrame();
	void Update();
public:
	Engine();
	~Engine();

	void Go();
};

#endif