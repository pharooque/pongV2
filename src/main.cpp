#include"bat.hpp"
#include<SFML/Graphics.hpp>
#include<sstream>
#include<random>
#include<array>

const int SCREEN_HEIGHT = 1300;
const int SCREEN_WIDTH = 2200;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong", sf::Style::Fullscreen);

    // Setup textures
    std::array<sf::Texture, 3> textures;
    const char* textureFiles[]{"../assets/sprites/background.png", /*"../assets/sprites/ball.png",*/ "../assets/sprites/bat.png",/*,
                               "../assets/sprites/border.png", "../assets/sprites/goal.png"*/ "../assets/sprites/wall.png"};

    for (int i = 0; i < textures.size(); ++i)
    {
        if (!textures[i].loadFromFile(textureFiles[i]))
        {
            /* Handle error*/
            return -1;
        }
    }

    // Setup sprites
    sf::Sprite background(textures[0]), wall(textures[2]);
    Bat playerBat(sf::Vector2f(SCREEN_WIDTH - 2100, 492), textures[1]);

    // Positioning wall, goal and borders
    wall.setPosition(1082.5f, .0f); 

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

    // Setuo random number generator
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

        // Handle input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerBat.moveUp();
        }
        else {playerBat.stopUp();}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            playerBat.moveDown();
        }
        else {playerBat.stopDown();}

        // Update time
        sf::Time deltaClock = clock.restart();
        playerBat.updateTime(deltaClock, batSpeed);

        // Prompt score display
        std::stringstream ss;
        ss << playerScore;
        scoreBoard.setString(ss.str());

        window.clear();
        window.draw(background);
        window.draw(scoreBoard);
        window.draw(wall);
        window.draw(playerBat.getSprite());
        
        window.display();
    }
    
    return 0;
}