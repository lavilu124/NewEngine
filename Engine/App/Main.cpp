#include "..//Engine/Engine.h"

#define WindowWidth 960
#define WindowHeight 540
#define MAX_FPS 144

void InputFunc(sf::RenderWindow& window);
void Display(sf::RenderWindow& window);

int main() {
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "new game", sf::Style::Default);
	window.setFramerateLimit(MAX_FPS);

	Camera MainCam(WindowWidth, WindowHeight);
	MainCam.SetCam(window);

	SystemManager::StartUp();

	/*GameObject Object1 = GameObject(FileManager::sprites["run0.png"]);
	Object1.SetPosition(sf::Vector2f(960 / 2, 540 / 2));

	GameObject Object2 = GameObject(FileManager::sprites["axe.png"]);*/

	SystemManager::Start();

	while (window.isOpen()) {
		InputFunc(window);

		SystemManager::Update();

		MainCam.Update();

		Display(window);
	}

	return 0;
}

void InputFunc(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		SystemManager::RunInput(event);
	}
}

void Display(sf::RenderWindow& window) {
	window.clear();

	SystemManager::Render(window);

	window.display();
}


