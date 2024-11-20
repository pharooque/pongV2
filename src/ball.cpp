#include "ball.hpp"

Ball::Ball(const sf::Texture& texture)
    : ballSpeed(1000), gen(42), startPosition(1100.0f, 650.0f)
{
    sprite.setTexture (texture);
    sprite.setPosition(startPosition);

    std::uniform_int_distribution<> directionDist(0, 1);
    directionX = directionDist(gen) == 0 ? -0.5f : 0.5f;
    directionY = directionDist(gen) == 0 ? -0.5f : 0.5f;
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

void Ball::verticalOffset(float offset)
{
    // Normalize the offset to avoid extreme values (e.g., divide by paddle height)
    float normal = offset / 158; // 158.0f is half the paddle height

    // Ensure the directionY stays within reasonable bounds
    if (directionY > 1.0f) directionY = 1.0f;
    else if (directionY < -1.0f) directionY = -1.0f;
}

void Ball::updateTime(sf::Time deltaClock)
{
    sprite.move(directionX * ballSpeed * deltaClock.asSeconds(), directionY * ballSpeed * deltaClock.asSeconds());
}

void Ball::resetBall()
{
    sprite.setPosition(startPosition);

    std::uniform_int_distribution<> directionDist(0, 1);
    directionX = directionDist(gen) == 0 ? -0.5f : 0.5f;
    directionY = directionDist(gen) == 0 ? -0.5f : 0.5f;
}