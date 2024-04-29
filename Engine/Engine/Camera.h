#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(const sf::Vector2f WinodwSize);

	void Follow(sf::Sprite SpriteToFollow);
	void Unfollow();

	void SetCam(sf::RenderWindow& win);
	
	void Update();
	~Camera();

public:
	float pov;
	sf::Vector2f position;
	float rotation;

private:
	sf::View m_view;
	sf::Sprite* m_spriteToFollow;

	sf::Vector2f m_zoom;
};

