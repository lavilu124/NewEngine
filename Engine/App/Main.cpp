#include "..//Engine/Engine.h"

#define WindowWidth 960
#define WindowHeight 540

int main() {
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "new game", sf::Style::Default);

	sf::Clock clock;
	sf::Time deltaTimeT;

	float deltaTime = 0;
	

	const sf::Vector2f test = sf::Vector2f(WindowWidth, WindowHeight);
	Camera camera(test);
	camera.SetCam(window);
	camera.position = sf::Vector2f(0, 0);


	FileManager::SetPaths();
	FileManager::LoadInput();

	sf::Sprite sprite(FileManager::sprites["run0.png"]);
	sprite.setPosition(0, 0);

	SystemManager::Start();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == 22) {
				//camera.pov++; 
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == 19) {
				//camera.pov--;
			}
			SystemManager::RunInput(event);
		}

		SystemManager::Update(deltaTime);

		deltaTimeT = clock.restart();
		deltaTime = deltaTimeT.asSeconds();

		window.clear();
		
		SystemManager::Render(window);
		window.draw(sprite);

		window.display();
	}

	return 0;
}
