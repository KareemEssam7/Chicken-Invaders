#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <algorithm>
#include<ctime>
using namespace std;
using namespace sf;

// Chicken Struct
struct ChickenStruct
{
    double HP, speed;
};

// Intialized Variables
double PlayerMovement = 9, PlayerSpeed = 12; 
double ChickenDir = 0,ChickenPositionX=0,ChickenPositionY=0;
int ChickenMovement=0;
bool checkchickenanimation = true;
ChickenStruct chicken;


 
// Creating Game Window
RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders");
// adding textures
Texture Background;
Texture PlayerSkin;
Texture ChickenSkin;



// Ingame Sprites
Sprite _GameBackground;
Sprite Player;
Sprite Chicken[9][4];

// Loading Ingame Files
void IngameImages()
{
    // background
    Background.loadFromFile("IngameBackground.jpg");
    _GameBackground.setTexture(Background);
    _GameBackground.setScale(1.875f, 1.05f);
    // player image
    PlayerSkin.loadFromFile("Playerr.png");
    Player.setTexture(PlayerSkin);
    Player.setTextureRect(IntRect(PlayerMovement * 60, 0, 60, 42));
    Player.setPosition(960, 850);
    // chicken image
    ChickenSkin.loadFromFile("RedChicken.png");
    for ( int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            Chicken[i][j].setTexture(ChickenSkin);
            Chicken[i][j].setScale(2.75, 2.75);
            Chicken[i][j].setPosition(120 + (ChickenPositionX * 190), 100 +(ChickenPositionY * 125));
            ChickenPositionX++;
        }
        ChickenPositionX = 0;
        ChickenPositionY++;
    }
}
// function for player movement
void PlayerMove()
{
    bool right = false;
    // Kareem Essam and Mohamed Wael
    // Creating Movement For Right Direction
    if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && Player.getPosition().x <= 1746)
    {
        // changing ship to be facing to the right
        Player.setTextureRect(IntRect(PlayerMovement * 60, 0, 60, 42));
        Player.move(PlayerSpeed, 0);
        if (PlayerMovement < 18)
        {
            PlayerMovement ++;
        }

    }
    //Creating Movement For Left Direction
    else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && Player.getPosition().x >= -48)
    {

        Player.setTextureRect(IntRect(PlayerMovement * 60, 0, 60, 42));
        // changing ship to be facing to the left
        Player.move(-PlayerSpeed, 0);
        if (PlayerMovement >0) 
        {
            PlayerMovement--;
        }
    }
    else
    {
        
        if (PlayerMovement > 9 )
        {
            PlayerMovement--;
            Player.setTextureRect(IntRect(PlayerMovement * 60, 0, 60, 42));
        }
        else if (PlayerMovement < 9)
        {
            PlayerMovement++;
            Player.setTextureRect(IntRect(PlayerMovement * 60, 0, 60, 42));
            
        }

    }
}
// function for chicken movement
void ChickenMove()
{   
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            Chicken[i][j].setTextureRect(IntRect(ChickenMovement * 47, 0, 45, 38));  
        }
    }
    if (ChickenMovement == 9)
        checkchickenanimation = false;
    else if (ChickenMovement == 0)
        checkchickenanimation = true;
    if (checkchickenanimation == false)
        ChickenMovement--;
    else
        ChickenMovement++;
    
}
int main()
{
    // add functions
    IngameImages();
    // main game loop
    while (window.isOpen())
    {
        // set framelimit
        window.setFramerateLimit(30);
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
        ChickenMove();
        //clear window
        window.clear();
        //draw window
        window.draw(_GameBackground);
        window.draw(Player);
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 9; i++)
            {
                window.draw(Chicken[i][j]);
            }
        }
        // show window
        window.display();
    }
    return 0;
}