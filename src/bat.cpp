#include "bat.hpp"

Bat::Bat(sf::Vector2f startPosition, sf::Texture texture)
{
    sprite.setTexture (texture);
    sprite.setPosition(startPosition);
}

sf::FloatRect Bat::getPosition()
{
    return sprite.getGlobalBounds();
}

void Bat::moveUp()
{
    m_moveUp = true;
}

void Bat::moveDown()
{
    m_moveDown = true;
}

void Bat::stop()
{
    m_moveUp = false;
    m_moveDown = false;
}

void Bat::updateTime(sf::Time deltaClock, float batSpeed)
{
    if (m_moveUp)
    {
        sprite.move(0, -batSpeed * deltaClock.asSeconds());
    }
    
    if (m_moveDown)
    {
        sprite.move(0, batSpeed * deltaClock.asSeconds());
    }
    
}