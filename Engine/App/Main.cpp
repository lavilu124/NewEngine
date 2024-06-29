#include "..//Engine/Engine.h"
#include <iostream>

#define WindowWidth 960
#define WindowHeight 540
#define MAX_FPS 144

void InputFunc(sf::RenderWindow& window);
void Display(sf::RenderWindow& window);

int main() {
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "new game", sf::Style::Default);
	window.setFramerateLimit(MAX_FPS);

	Camera mainCam(WindowWidth, WindowHeight);
	mainCam.SetCam(window);

	SystemManager::StartUp();

	SystemManager::Start();

	while (window.isOpen()) {
		InputFunc(window);

		SystemManager::Update();

		mainCam.Update();

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
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
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


