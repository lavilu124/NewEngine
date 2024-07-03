#include "LightSystem.h"
#include <cmath>

#define MINDIFF 2.25e-308
#define PI  3.14159f
#define POINT_COUNT  30
#define MAX_DISTANCE  255.f


namespace Light {
    void LightSource::Update() {}
    sf::Drawable* LightSource::GetLight() {
        line = sf::RectangleShape(sf::Vector2f(150, 5));
        line.rotate(45);
        return &line;
    }

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


    SircleLight::SircleLight(float diameter) {
        m_light = sf::CircleShape(diameter / 2);
        m_light.setPointCount(diameter / 4);
        m_light.setOrigin(diameter / 2, diameter / 2);

        m_gradientImage.create(diameter, diameter);

        for (unsigned y = 0; y < diameter; ++y) {
            for (unsigned x = 0; x < diameter; ++x) {
                float distance = sqroot((x - (diameter / 2)) * (x - (diameter / 2)) + (y - (diameter / 2)) * (y - (diameter / 2)));
                float intensity = std::max(0.f, 1.f - distance / (diameter / 2));
                sf::Uint8 alpha = static_cast<sf::Uint8>(MAX_DISTANCE * intensity);
                m_gradientImage.setPixel(x, y, sf::Color(255, 255, 255, alpha));
            }
        }


        m_gradientTexture.loadFromImage(m_gradientImage);
        m_light.setTexture(&m_gradientTexture);
    }

    void SircleLight::Update() {
        m_light.setPosition(position);
        m_light.setRotation(rotation);
        m_light.setScale(scale);
    }

    sf::Drawable* SircleLight::GetLight() {
        return &m_light;
    }

    sf::ConvexShape createSector(float radius, float startAngle, float endAngle) {

        sf::ConvexShape sector;
        sector.setPointCount(POINT_COUNT + 2);

        sector.setPoint(0, sf::Vector2f(0, 0));

        for (int i = 1; i <= POINT_COUNT + 1; ++i) {
            float angle = startAngle + (endAngle - startAngle) * (i - 1) / POINT_COUNT;
            float x = radius * std::cos(angle * PI / 180);
            float y = radius * std::sin(angle * PI / 180);
            sector.setPoint(i, sf::Vector2f(x, y));
        }

        return sector;
    }

    DirectionalLight::DirectionalLight(float size, float angle) {
        m_light = createSector(size / 2, 45.f, angle + 45.f);

        m_gradientImage.create(size, size);

        for (unsigned y = 0; y < size; ++y) {
            for (unsigned x = 0; x < size; ++x) {
                float distance = std::sqrt((x - (size / 2)) * (x - (size / 2)) + (y - m_light.getPosition().y) * (y - m_light.getPosition().y));
                float intensity = std::max(0.f, 1.f - distance / (size / 2.f));
                sf::Uint8 alpha = static_cast<sf::Uint8>(255 * intensity);
                m_gradientImage.setPixel(x, y, sf::Color(255, 255, 255, alpha));
            }
        }

        m_gradientTexture.loadFromImage(m_gradientImage);
        m_light.setTexture(&m_gradientTexture);
    }

    void DirectionalLight::Update() {
        m_light.setPosition(position);
        m_light.setRotation(rotation);
        m_light.setScale(scale);
    }

    sf::Drawable* DirectionalLight::GetLight() {
        return &m_light;
    }

    LightSystem::LightSystem(sf::Vector2f windowSize, sf::Color darkness) : m_darkness(darkness) {
        m_lightTexture.create(windowSize.x, windowSize.y);
    }

    LightSystem::LightSystem(float width, float height, sf::Color darkness) : m_darkness(darkness) {
        m_lightTexture.create(width, height);
    }

    void LightSystem::update() {
        m_lightTexture.clear(m_darkness);

		for (int i = 0; i < lights.size(); i++) {
			lights[i]->Update();
			m_lightTexture.draw(*lights[i]->GetLight(), sf::BlendAdd);
		}

        m_lightTexture.display();
    }

    void LightSystem::draw(sf::RenderWindow& window) {
        sf::Sprite lightSprite(m_lightTexture.getTexture());
        lightSprite.setOrigin(lightSprite.getLocalBounds().width / 2.0f, lightSprite.getLocalBounds().height / 2.0f);
        lightSprite.setPosition(window.getView().getCenter());

        window.draw(lightSprite, sf::BlendMultiply);
    }

}