#pragma once
#include "../Engine/Engine.h"

#define WindowWidth 960
#define WindowHeight 540
#define MAX_FPS 144


class App
{
public:
	App(sf::RenderWindow& window, LightSystem& lightSystem, Camera& cam);

	void InputFunc(sf::RenderWindow& window);


	void Run();


private:
	sf::RenderWindow* m_window;
	LightSystem* m_mainLightSystem;
	Camera* m_mainCam;
};

