#include "bat.hpp"

Bat::Bat(sf::Vector2f startPosition, const sf::Texture& texture)
    : m_moveUp(false), m_moveDown(false)
{
    sprite.setTexture (texture);
    sprite.setPosition(startPosition);
}

sf::FloatRect Bat::getPosition() const
{
    return sprite.getGlobalBounds();
}

const sf::Sprite& Bat::getSprite() const
{
    return sprite;
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