#pragma once
#include "../Engine/Engine.h"

class App
{
public:
	App(float windowWidth, float windowHeight, float maxFPS);

	void InputFunc(sf::RenderWindow& window);


	void Run();


private:

	sf::RenderWindow m_window;
	Camera* m_camera;
	LightSystem m_lightSystem;
};

