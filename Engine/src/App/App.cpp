#include "App.h"

App::App(sf::RenderWindow& window, LightSystem& lightSystem, Camera& cam){
	m_window = &window;
	m_mainCam = &cam;
	m_mainLightSystem = &lightSystem;

	m_mainCam->SetCam(window);

	window.setFramerateLimit(MAX_FPS);

	SystemManager::StartUp();

	SystemManager::Start();
}

void App::InputFunc(sf::RenderWindow& window) {
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

void App::Run() {
	sf::CircleShape shape(50);

	shape.setFillColor(sf::Color(100, 250, 50));

	while (m_window->isOpen()) {
		InputFunc(*m_window);

		SystemManager::Update();

		m_mainCam->Update();

		sf::Vector2i mousePixelPos = sf::Mouse::getPosition(*m_window);
		m_mainLightSystem->position = m_window->mapPixelToCoords(mousePixelPos);

		m_mainLightSystem->update();

		m_window->clear();

		SystemManager::Render(*m_window);

		m_window->draw(shape);

		m_mainLightSystem->draw(*m_window);

		m_window->display();
	}
}