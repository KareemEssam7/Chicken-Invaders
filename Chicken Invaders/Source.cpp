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
    double HP[8][5], speed = 4;
};

//Bullet Struct
struct bulletstruct {
    int heldWeapon = 1;
    float bulletSpeed = 10;
    int currentBullet = 0;
    float bulletCoolDownvar = 10;
    float bulletCoolDown = 0;
};



// Intialized Variables
double PlayerMovement = 9, PlayerSpeed = 12; 
double ChickenDir = 0,ChickenPositionX=0,ChickenPositionY=0;
int ChickenMovement=0,x=0;
int borderadjust = 0;
bool checkchickenanimation = true; 
ChickenStruct chicken;
bulletstruct bullet;
Time deltatime;



// Creating Game Window
RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders");

// adding textures
Texture Background;
Texture PlayerSkin;
Texture ChickenSkin;
Texture bulletImage;

// adding border
RectangleShape rectangle1(Vector2f(60, 1080));
RectangleShape rectangle2(Vector2f(60, 1080));



// Ingame Sprites
Sprite _GameBackground;
Sprite Player;
Sprite Chicken[8][6];
Sprite Bullets[40];

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
    Player.setScale(1.5, 1.5);

    // Border Image
    rectangle1.setPosition(0, 0);
    rectangle1.setFillColor(Color::Transparent);
    rectangle2.setPosition(1855, 0);
    rectangle2.setFillColor(Color::Transparent);

    // chicken image
    ChickenSkin.loadFromFile("RedChicken.png");

    //bullet image
    bulletImage.loadFromFile("Bullet1Image.png");

    //setting chicken textures and positions
    for ( int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            Chicken[i][j].setTexture(ChickenSkin);
            Chicken[i][j].setScale(2.75, 2.75);
            Chicken[i][j].setPosition(120 + (ChickenPositionX * 170), 50 +(ChickenPositionY * 100));
            ChickenPositionX++;
        }
        ChickenPositionX = 0;
        ChickenPositionY++;
    }

    //setting bullet textures
    for (int i = 0; i < 40; i++) {
        Bullets[i].setTexture(bulletImage);
        Bullets[i].setScale(2,2);
        Bullets[i].setPosition(-100, -100);
    }
}
// function for player movement
void PlayerMove()
{
    bool right = false;
    // Kareem Essam and Mohamed Wael
    // Creating Movement For Right Direction
    if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && Player.getPosition().x <= 1800)
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
    else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && Player.getPosition().x >= 15)
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

//shooting function
void PlayerShooting(){

    //Shooting
    if ((Keyboard::isKeyPressed(Keyboard::Space)) && bullet.bulletCoolDown == 0 || (Mouse::isButtonPressed(Mouse::Left)) && bullet.bulletCoolDown == 0)
    {
        bullet.bulletCoolDown = bullet.bulletCoolDownvar;
        Bullets[bullet.currentBullet].setPosition(Player.getPosition().x + 29 , Player.getPosition().y - 45);
        
        if (bullet.currentBullet == 39) {
            bullet.currentBullet = 0;
        }
        bullet.currentBullet++;
    }

    if (bullet.bulletCoolDown > 0) {
        bullet.bulletCoolDown--;
    }
    
    //bullet moving
    for (int i = 0; i < 40; i++) {
        Bullets[i].move(0, -bullet.bulletSpeed);
    }
}




// function for chicken movement
void ChickenMove()
{   
    // mohamed wael and kareem essam
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            Chicken[i][j].setTextureRect(IntRect(ChickenMovement * 46.9, 0, 46.9, 38));
            if (Chicken[i][j].getGlobalBounds().intersects(rectangle2.getGlobalBounds()))
            {
                ChickenDir = 0;
            }
            else if (Chicken[0][5].getGlobalBounds().intersects(rectangle1.getGlobalBounds()))
            {
                ChickenDir = 1;
            }
            if (ChickenDir == 0)
                Chicken[i][j].move(-chicken.speed, 0);
            else if (ChickenDir == 1)
                Chicken[i][j].move(chicken.speed, 0);
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
        window.draw(rectangle1);
        window.draw(rectangle2);
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                window.draw(Chicken[i][j]);
            }
        }
        PlayerShooting();
        for (int i = 0; i < 40; i++) {
            window.draw(Bullets[i]);
        }
        
        // show window
        window.display();
    }
    return 0;
}