#pragma once
#include<SFML/Graphics.hpp>

class Bat
{
private:
    sf::Sprite sprite;
    bool m_moveUp = false;
    bool m_moveDown = false;
public:
    Bat(sf::Vector2f startPosition, sf::Texture texture);
    
    sf::FloatRect getPosition();

    void moveUp();
    void moveDown();

    void stop();

    void updateTime(sf::Time deltaClock, float batSpeed);
};
