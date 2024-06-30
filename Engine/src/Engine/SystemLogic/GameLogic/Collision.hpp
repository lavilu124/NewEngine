#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

namespace Collision {
    enum collisionLayer {
        COLLIDER,
        CUSTOMLAYERR_ONE,
        CUSTOMLAYERR_TWO,
        CUSTOMLAYERR_THREE,
        CUSTOMLAYERR_FOUR,
        CUSTOMLAYERR_FIVE,

        TRIGGER,
        IGNORE,
        CUSTOMLAYERR_SIX,
        CUSTOMLAYERR_SEVEN,
        CUSTOMLAYERR_EIGHT,
        CUSTOMLAYERR_NINE,
        CUSTOMLAYERR_TEN,
        ALL
    };

    
    bool PixelPerfectCollision(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);
    
   
    bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename);
    
    
    bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
    
    
    bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

    std::array<int, 4> GetcollisonPosition();
}

#endif	/* COLLISION_H */
