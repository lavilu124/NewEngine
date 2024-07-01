#include "LightSystem.h"

#define MINDIFF 2.25e-308

double sqroot(double square)
{
    double root = square / 3, last, diff = 1;
    if (square <= 0) return 0;
    do {
        last = root;
        root = (root + square / root) / 2;
        diff = root - last;
    } while (diff > MINDIFF || diff < -MINDIFF);
    return root;
}

LightSystem::LightSystem(float size, sf::Vector2f windowSize, sf::Color darkness) {
    m_lightTexture.create(windowSize.x, windowSize.y);

    m_light = sf::CircleShape(size / 2);
    m_light.setPointCount(size / 4);
    m_light.setOrigin(size / 2, size / 2);

    m_gradientImage.create(size, size);

    for (unsigned y = 0; y < size; ++y) {
        for (unsigned x = 0; x < size; ++x) {
            float distance = sqroot((x - (size / 2)) * (x - (size / 2)) + (y - (size / 2)) * (y - (size / 2)));
            float intensity = std::max(0.f, 1.f - distance / (size / 2));
            sf::Uint8 alpha = static_cast<sf::Uint8>(255 * intensity);
            m_gradientImage.setPixel(x, y, sf::Color(255, 255, 255, alpha));
        }
    }

    m_gradientTexture.loadFromImage(m_gradientImage);
    m_light.setTexture(&m_gradientTexture);
    m_darkness = darkness;
}

LightSystem::LightSystem(float size, float width, float height, sf::Color darkness) {
    m_lightTexture.create(width, height);

    m_light = sf::CircleShape(size / 2);
    m_light.setPointCount(size / 4);
    m_light.setOrigin(size / 2, size / 2);

    m_gradientImage.create(size, size);

    for (unsigned y = 0; y < size; ++y) {
        for (unsigned x = 0; x < size; ++x) {
            float distance = std::sqrt((x - (size / 2)) * (x - (size / 2)) + (y - (size / 2)) * (y - (size / 2)));
            float intensity = std::max(0.f, 1.f - distance / (size / 2));
            sf::Uint8 alpha = static_cast<sf::Uint8>(255 * intensity);
            m_gradientImage.setPixel(x, y, sf::Color(255, 255, 255, alpha));
        }
    }

    m_gradientTexture.loadFromImage(m_gradientImage);
    m_light.setTexture(&m_gradientTexture);
    m_darkness = darkness;

    
}

void LightSystem::update() {
    m_lightTexture.clear(m_darkness);

    m_light.setPosition(position.x, position.y);
    m_lightTexture.draw(m_light, sf::BlendAdd);

    m_lightTexture.display();
}

void LightSystem::draw(sf::RenderWindow& window) {
    sf::Sprite lightSprite(m_lightTexture.getTexture());
    lightSprite.setOrigin(lightSprite.getLocalBounds().width / 2.0f, lightSprite.getLocalBounds().height / 2.0f);
    lightSprite.setPosition(window.getView().getCenter());
    window.draw(lightSprite, sf::BlendMultiply);
}
