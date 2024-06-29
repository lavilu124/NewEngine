#include "App.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "new game", sf::Style::Default);
	Camera mainCam(WindowWidth, WindowHeight);
	LightSystem mainLightSystem(400, WindowWidth, WindowHeight, sf::Color(20, 20, 20, 150));
	App app(window, mainLightSystem, mainCam);

	app.Run();


	return 0;
}




