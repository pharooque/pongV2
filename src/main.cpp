#include"bat.hpp"
#include<SFML/Graphics.hpp>
#include<array>

const int SCREEN_HEIGHT = 1300;
const int SCREEN_WIDTH = 2200;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong", sf::Style::Fullscreen);

    // Setup textures
    std::array<sf::Texture, 2> textures;
    const char* textureFiles[]{"../assets/sprites/background.png", /*"../assets/sprites/ball.png",*/ "../assets/sprites/bat.png"/*,
                               "../assets/sprites/border.png", "../assets/sprites/goal.png", "../assets/sprites/wall,png"*/};

    for (int i = 0; i < textures.size(); ++i)
    {
        if (!textures[i].loadFromFile(textureFiles[i]))
        {
            /* Handle error*/
            return -1;
        }
    }

    // Setup sprites
    sf::Sprite background(textures[0]);
    Bat bat(sf::Vector2f(SCREEN_WIDTH - 2100, 492), textures[1]);

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

        window.clear();
        window.draw(background);
        window.draw(bat.getSprite());
        
        window.display();
    }
    
    

    return 0;
}
