#pragma once
#include "SFML/Graphics.hpp"

class LightSystem {
public:
    LightSystem(float size, sf::Vector2f windowSize, sf::Color darkness);
    LightSystem(float size, float width, float height, sf::Color darkness);
    void update();
    void draw(sf::RenderWindow& window);

    sf::Vector2f position;
    sf::Color m_darkness;

private:
    sf::RenderTexture m_lightTexture;
    sf::Texture m_gradientTexture;
    sf::Image m_gradientImage;
    sf::CircleShape m_light;
};

