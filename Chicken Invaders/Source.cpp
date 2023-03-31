#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <algorithm>
#include<ctime>
using namespace std;
using namespace sf;
// Intialized Variables
double PlayerMovement = 0, PlayerDir = 0;
double PlayerSpeed = 10, PlayerRight = 0, PlayerLeft = 0;
// Creating Game Window
RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders");
// adding textures
Texture Background;
Texture PlayerSkin;



// Ingame Sprites
Sprite _GameBackground;
Sprite Player;

// Loading Ingame Files
void IngameImages()
{
    // background
    Background.loadFromFile("IngameBackground.jpg");
    _GameBackground.setTexture(Background);
    _GameBackground.setScale(1.875f, 1.05f);
    // player image
    PlayerSkin.loadFromFile("Player.png");
    Player.setTexture(PlayerSkin);
    Player.setTextureRect(IntRect(PlayerMovement*160.625, PlayerDir*82.5, 160.625, 82.5));
    Player.setPosition(900, 750);
}
// function for player movement
void PlayerMove()
{
    // Kareem
    // Creating Movement For Right Direction
    if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && Player.getPosition().x <= 1746)
    {
        // changing ship to be facing to the right
        PlayerDir = 1;
        Player.move(PlayerSpeed, 0);
        Player.setTextureRect(IntRect(PlayerMovement * 160.625, PlayerDir * 82.5, 160.625, 82.5));
        if (PlayerMovement < 7)
        {
            PlayerMovement += 1;
        }

    }
    //Creating Movement For Left Direction
    else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && Player.getPosition().x >= -48)
    {
        PlayerDir = 0;
        // changing ship to be facing to the left
        Player.move(-PlayerSpeed, 0);
        Player.setTextureRect(IntRect(PlayerMovement * 160.625, PlayerDir * 82.5, 160.625, 82.5));
        if (PlayerMovement < 7) 
        {
            PlayerMovement++;
        }
    }
    else
    {
        
        if (PlayerMovement > 0)
        {
            Player.setTextureRect(IntRect(PlayerMovement * 160.625, PlayerDir * 82.5, 160.625, 82.5));
            PlayerMovement--;
        }
        else if (PlayerMovement == 0 && PlayerDir == 1)
        {
            Player.move(20, 0);
            PlayerDir = 0;
        }

    }
}
int main()
{
    // add functions
    IngameImages();
    // main game loop
    while (window.isOpen())
    {
        // set framelimit
        window.setFramerateLimit(40);
        //Event
        Event event;
        while (window.pollEvent(event))
        {
            // close window
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        PlayerMove();
        //clear window
        window.clear();
        //draw window
        window.draw(_GameBackground);
        window.draw(Player);
        // show window
        window.display();
    }
    return 0;
}