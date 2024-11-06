#pragma once
#include<SFML/Graphics.hpp>

class Bat
{
private:
    sf::Sprite sprite;
    float mSpeed = 1000.0f;
    bool moveRight = false;
    bool moveLeft = false;
public:
    Bat(sf::Vector2f startPosition, sf::Texture texture);
    
    
};
