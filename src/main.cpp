#include"bat.hpp"
#include"ball.hpp"
#include<SFML/Graphics.hpp>
#include<sstream>   // Score board concatenation
#include<array>

// Screen size constants
const int SCREEN_HEIGHT = 1300;
const int SCREEN_WIDTH = 2200;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong", sf::Style::Fullscreen);

    // Loading up textures at once at the start
    std::array<sf::Texture, 6> textures;
    const char* textureFiles[]{"../assets/sprites/background.png", "../assets/sprites/ball.png", "../assets/sprites/bat.png",
                               "../assets/sprites/border.png", "../assets/sprites/goal.png", "../assets/sprites/wall.png"};

    for (int i = 0; i < textures.size(); ++i)
    {
        if (!textures[i].loadFromFile(textureFiles[i]))
        {
            /* Handle error*/
            return -1;
        }
    }

    // Setup sprites
    sf::Sprite background(textures[0]), wall(textures[5]);
    std::array<sf::Sprite, 2> borders; for (auto& border : borders) {border.setTexture(textures[3]);}
    std::array<sf::Sprite, 2> goals; for(auto& goal : goals) {goal.setTexture(textures[4]);}

    Bat playerBat(sf::Vector2f(SCREEN_WIDTH - 2000, 492), textures[2]); // Player controlled paddle
    Bat aiBat(sf::Vector2f(SCREEN_WIDTH - 254, 492), textures[2]); // AI controlled paddle
    Ball ball(textures[1]); // Ball sprite

    // Positioning wall, goal and borders
    wall.setPosition(1082.5, 0);
    borders[0].setPosition(12, 0);
    borders[1].setPosition(12, SCREEN_HEIGHT - 12);
    goals[0].setPosition(0, 0);
    goals[1].setPosition(SCREEN_WIDTH - 36, 0);

    // Setup score board
    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/DS-DIGI.TTF"))
    {
        /* Handle error */
        return 1;
    }

    sf::Text scoreBoard;
    scoreBoard.setFont(font);
    scoreBoard.setCharacterSize(250);
    scoreBoard.setFillColor(sf::Color::White);
    scoreBoard.setPosition((SCREEN_WIDTH / 2) - 300, 15);
    
    int playerScore = 0;
    int aiScore = 0;
    float aiBatDelay = aiBat.getAiBatDelay(); // Reaction speed to make AI beatable

    // Time object
    sf::Clock clock;

    // Game loop 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            } 
        }

        // Handle player input
        playerBat.stop(); //Default stop

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            playerBat.moveUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            playerBat.moveDown();
        }

        if (playerScore - aiScore >= 3)
        {
            aiBat.increaseDifficulty();
        }
        
        // AI paddle Logic
        if (ball.getPosition().top + ball.getPosition().height > aiBat.getPosition().top + aiBat.getPosition().height * (1 + aiBatDelay))
        {
            aiBat.moveDown();
        }
        else if (ball.getPosition().top + ball.getPosition().height < aiBat.getPosition().top - aiBat.getPosition().height * aiBatDelay)
        {
            aiBat.moveUp();
        }
        else
        {
            aiBat.stop();
        }

        // Update time and positions
        sf::Time deltaClock = clock.restart();
        playerBat.updateTime(deltaClock);
        aiBat.updateTime(deltaClock);
        ball.updateTime(deltaClock);

        if (ball.getPosition().top <= 0 || ball.getPosition().top + ball.getPosition().height > SCREEN_HEIGHT)
        {
            ball.reboundVerticalSides();
        }

        if (ball.getPosition().intersects(playerBat.getPosition()))
        {
            ball.reboundHorizontalSides();

            // Calculate offset and adjust the ball's vertical direction
            float offset = (ball.getPosition().top + ball.getPosition().height / 2) - 
                           (playerBat.getPosition().top + playerBat.getPosition().height / 2);
            ball.verticalOffset(offset);
        }
        else if (ball.getPosition().intersects(aiBat.getPosition()))
        {
            ball.reboundHorizontalSides();

            float offset = (ball.getPosition().top + ball.getPosition().height / 2) - 
                           (aiBat.getPosition().top + aiBat.getPosition().height / 2);
            ball.verticalOffset(offset);
        }
        
        if (ball.getPosition().left < 0)
        {
            aiScore ++;
            ball.resetBall();
        }
        else if (ball.getPosition().left > SCREEN_WIDTH)
        {
            playerScore ++;
            ball.resetBall();
        }

        // Prompt score display
        std::stringstream ss;
        ss << playerScore << "      " << aiScore;
        scoreBoard.setString(ss.str());

        window.clear();
        window.draw(background);
        window.draw(scoreBoard);
        window.draw(wall);
        for (const auto& border : borders) {window.draw(border);}
        for (const auto& goal : goals) {window.draw(goal);}
        window.draw(playerBat.getSprite());
        window.draw(aiBat.getSprite());
        window.draw(ball.getSprite());
        
        window.display();
    }
    
    return 0;
}