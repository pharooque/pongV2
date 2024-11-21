#pragma once
#include<SFML/Graphics.hpp>

class Bat
{
private:
    sf::Sprite sprite;
    float aiBatDelay;
    float m_Speed;
    bool m_moveUp;
    bool m_moveDown;
public:
    Bat(sf::Vector2f startPosition, const sf::Texture& texture);
    
    sf::FloatRect getPosition() const;
    const sf::Sprite& getSprite() const;

    float getAiBatDelay() const; // Getter function
    void increaseDifficulty();
    void moveUp();
    void moveDown();
    void stop();

    void updateTime(sf::Time deltaClock);
};
