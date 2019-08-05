#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML\Graphics.hpp>

#include "Camera.h"

class Engine
{
private:
	sf::RenderWindow *_window;
	
	Camera *_camera;
	sf::Vector2f *_cameraDirection;

	sf::RectangleShape *_rect;

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