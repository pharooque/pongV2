#include "bat.hpp"

Bat::Bat(sf::Vector2f startPosition, const sf::Texture& texture)
    : m_moveUp(false), m_moveDown(false), m_Speed(1000.0f)
{
    sprite.setTexture (texture);
    sprite.setPosition(startPosition);
}

sf::FloatRect Bat::getPosition() const
{
    return sprite.getGlobalBounds();
}

// Getter function for rendering bat
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

// Time and motion update
void Bat::updateTime(sf::Time deltaClock)
{
    float batTop = sprite.getPosition().y;
    float batBottom = batTop + sprite.getLocalBounds().height;
    
    if (m_moveUp)
    {
        sprite.move(0, -m_Speed * deltaClock.asSeconds());

        if (batTop < 0)
        {
            sprite.setPosition(sprite.getPosition().x, 0);
            m_moveUp = false;
        } 
    }
    
    if (m_moveDown)
    {
        sprite.move(0, m_Speed * deltaClock.asSeconds());

        if (batBottom > 1300)
        {
            sprite.setPosition(sprite.getPosition().x, 1300 - sprite.getGlobalBounds().height);
            m_moveDown = false;
        }
    } 
}