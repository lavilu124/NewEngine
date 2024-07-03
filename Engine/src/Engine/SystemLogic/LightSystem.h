#pragma once
#include "SFML/Graphics.hpp"

namespace Light {
     

    class LightSource {
    public:
        virtual void Update();
        virtual sf::Drawable* GetLight();

        sf::Vector2f position;
        sf::Vector2f scale = sf::Vector2f(1,1);
        float rotation;
    protected:
        sf::Texture m_gradientTexture;
        sf::Image m_gradientImage;
    private:
        sf::RectangleShape line;
    };

    class SircleLight : public LightSource {
    public:
		SircleLight(float diameter);

		void Update() override;

        sf::Drawable* GetLight() override;

    private:
		sf::CircleShape m_light;
    };

    class DirectionalLight : public LightSource {
    public:
        DirectionalLight(float size, float angle);

        void Update() override;

        sf::Drawable* GetLight() override;

    private:
        sf::ConvexShape m_light;
    };

    class LightSystem {
    public:
        LightSystem(sf::Vector2f windowSize, sf::Color darkness);
        LightSystem(float width, float height, sf::Color darkness);
        void update();
        void draw(sf::RenderWindow& window);

        sf::Color m_darkness;

        std::vector<LightSource*> lights;

    private:
        sf::RenderTexture m_lightTexture;
    };
}

