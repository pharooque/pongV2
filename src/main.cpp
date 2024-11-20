#include"bat.hpp"
#include"ball.hpp"
#include<SFML/Graphics.hpp>
#include<sstream>   // Score board concatenation
#include<random>    // For random numbers
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

    Bat playerBat(sf::Vector2f(SCREEN_WIDTH - 2100, 492), textures[2]); // Player controlled paddle
    Bat aiBat(sf::Vector2f(SCREEN_WIDTH - 154, 492), textures[2]); // AI controlled paddle
    Ball ball(textures[1]);

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
    scoreBoard.setCharacterSize(100);
    scoreBoard.setFillColor(sf::Color::White);
    scoreBoard.setPosition(1030, 15);
    
    int playerScore = 0;
    int aiScore = 0;

    // Setup random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> batSpeedDist(800, 1000);
    float batSpeed = batSpeedDist(gen);


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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            playerBat.moveUp();
        }
        else {playerBat.stopUp();}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            playerBat.moveDown();
        }
        else {playerBat.stopDown();}

        // Update time and sprite movement
        sf::Time deltaClock = clock.restart();
        playerBat.updateTime(deltaClock, batSpeed);
        ball.updateTime(deltaClock);

        if (ball.getPosition().top <= 0 || ball.getPosition().top + ball.getPosition().height > SCREEN_HEIGHT)
        {
            ball.reboundVerticalSides();
        }

        if (ball.getPosition().intersects(playerBat.getPosition()))
        {
            ball.reboundHorizontalSides();
        }
        else if (ball.getPosition().intersects(aiBat.getPosition()))
        {
            ball.reboundHorizontalSides();
        }
        
        /*if (ball.getPosition().intersects(goals[0].getGlobalBounds()) || ball.getPosition().intersects(goals[1].getGlobalBounds()))
        {
            ball.resetBall();
        }*/
        
        if (ball.getPosition().left + ball.getPosition().width < goals[0].getGlobalBounds().left + goals[0].getGlobalBounds().width || 
            ball.getPosition().left > goals[1].getGlobalBounds().left + goals[1].getLocalBounds().width)
        {
            ball.resetBall();
        }

        // Prompt score display
        std::stringstream ss;
        ss << playerScore;
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