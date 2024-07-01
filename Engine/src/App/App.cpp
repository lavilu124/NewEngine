#include "App.h"

App::App(float windowWidth, float windowHeight, float maxFPS) : m_lightSystem(400.f, windowWidth, windowHeight, sf::Color(50, 50, 50, 150)),
	m_window(sf::VideoMode(windowWidth, windowHeight), "new game", sf::Style::Default){


	m_window.setFramerateLimit(maxFPS);

	SystemManager::StartUp(m_window);
	
	SystemManager::LoadScene("Scene1");

	m_camera = &SystemManager::GetCamera();
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

	while (m_window.isOpen()) {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				m_window.close();
			}

			SystemManager::RunInput(event);
		}

		SystemManager::Update();

		m_camera->Update();

		m_lightSystem.position = sf::Vector2f(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);

		m_lightSystem.update();

		m_window.clear();

		SystemManager::Render(m_window);

		m_window.draw(shape);

		m_lightSystem.draw(m_window);

		m_window.display();
	}

	SystemManager::ClearSystem();
}