#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Objects/GameObject.h"

class Animation {
public:
    //constructor for animation
    Animation(std::vector <sf::Sprite> AnimationVector, float Speed = 1);


    //all the pictures of the animation in order
    std::vector <sf::Sprite> AnimationVector;

    //all the methods for running an animation
    void RunAnimation(float Dletatime, GameObject Object);
    sf::Sprite GetCurrentSprite();
    void ResetAnimation();

    //setter and getter for animation speed
    int GetSpeed();
    void SetSpeed(int Speed);

private:
    //all the variable to keep track of the animation
    float Speed;
    float Counter = 0;
    int Index = 0;
    sf::Sprite CurrentSprite;
};

