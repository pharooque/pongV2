#include "ball.hpp"

Ball::Ball(const sf::Texture& texture)
    : ballSpeed(300), gen(42), startPosition(1100.0f, 650.0f)
{
    sprite.setTexture (texture);
    sprite.setPosition(startPosition);

    std::uniform_int_distribution<> directionDist(0, 1);
    directionX = directionDist(gen) == 0 ? -1.0f : 1.0f;
    directionY = directionDist(gen) == 0 ? -1.0f : 1.0f;
}

sf::FloatRect Ball::getPosition() const
{
    return sprite.getGlobalBounds();
}

const sf::Sprite& Ball::getSprite() const
{
    return sprite;
}

void Ball::reboundVerticalSides()
{
    directionY = -directionY;
}

void Ball::reboundHorizontalSides()
{
    directionX = -directionX;
}

void Ball::updateTime(sf::Time deltaClock)
{
    sprite.move(directionX * ballSpeed * deltaClock.asSeconds(), directionY * ballSpeed * deltaClock.asSeconds());
}

void Ball::resetBall()
{
    sprite.setPosition(startPosition);

    std::uniform_int_distribution<> directionDist(0, 1);
    directionX = directionDist(gen) == 0 ? -1.0f : 1.0f;
    directionY = directionDist(gen) == 0 ? -1.0f : 1.0f;
}