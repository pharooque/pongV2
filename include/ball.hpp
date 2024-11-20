#pragma once
#include<SFML/Graphics.hpp>
#include<random>

class Ball
{
private:
    sf::Sprite sprite;
    sf::Vector2f startPosition;
    float ballSpeed;
    float directionX;
    float directionY;
    std::mt19937 gen;
public:
    Ball(const sf::Texture& texture);
    
    sf::FloatRect getPosition() const;
    const sf::Sprite& getSprite() const;

    void reboundVerticalSides();
    void reboundHorizontalSides();
    void updateTime(sf::Time deltaClock);
    void resetBall();
};
