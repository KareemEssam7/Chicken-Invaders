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
;
//Bullet Struct
struct bulletstruct {
    int heldWeapon = 1;
    float bulletSpeed = 10;
    int currentBullet = 0;
    float bulletCoolDownvar = 10;
    float bulletCoolDown = 0;
};



// Intialized Variables
int cnt = 0;      //counter for score
int health = 100;
double PlayerMovement = 9, PlayerSpeed = 12; 
double ChickenDir = 0,ChickenPositionX=0,ChickenPositionY=0,rectdir=0;
int ChickenMovement=0,x=0;
int borderadjust = 0;
bool checkchickenanimation = true; 
ChickenStruct chicken;
bulletstruct bullet;
Time deltatime;



// Creating Game Window
RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders",Style::Fullscreen);

// adding textures
Texture Background;
Texture PlayerSkin;
Texture ChickenSkin;
Texture bulletImage; 
Texture healhbar;

// adding border
RectangleShape rectangle1(Vector2f(60, 1080));
RectangleShape rectangle2(Vector2f(60, 1080));
RectangleShape rectangle3(Vector2f(1300, 200));
//adding texts
Text hp;
Text score;

//fonts
Font font1;






// Ingame Sprites
Sprite _GameBackground;
Sprite Player;
Sprite Chicken[8][6];
Sprite Bullets[40];
Sprite healh_bar;


//increasing score
void scorecalc() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 6; j++) {
            for (int z = 0; z < 8; z++) {

                if (Bullets[i].getGlobalBounds().intersects(Chicken[j][z].getGlobalBounds())) {
                    cnt += 1;
                    score.setString("score : " + to_string(cnt));
                    Bullets[i].setScale(0, 0);
                    Chicken[j][z].setScale(0,0);
                }

            }


        }


    }
}

//void playerdamage() {
//    for (int i = 0; i < 6; i++) {
//        for (int j = 0; j < 8; j++) {
//        
//            if (Player.getGlobalBounds().intersects(Chicken[i][j].getGlobalBounds())) {
//                health -= 5;
//                hp.setString("health = " + to_string(health));
//            }
//        
//        }
//       }
//}








// Loading Ingame Files
void IngameImages()
{   //Fonts
    font1.loadFromFile("LATINWD.ttf");


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
    rectangle3.setOrigin(1300/2, 200);
    rectangle3.setPosition(770,400);
    rectangle3.setFillColor(Color::Transparent);

    // chicken image
    ChickenSkin.loadFromFile("RedChicken.png");
   
     
    //bullet image
    bulletImage.loadFromFile("Bullet1Image.png");

    //setting health and score bar
    healhbar.loadFromFile("Button1.png");
    healh_bar.setTexture(healhbar);
    healh_bar.setPosition(0, window.getSize().y - 150);
    healh_bar.setScale(1.3, 1.3);

    //health
    hp.setFont(font1);
    hp.setCharacterSize(20);
    hp.setOrigin(0, 0);
    hp.setPosition(30, window.getSize().y - 120);
    hp.setString("health : " + to_string(health));
    //score
    score.setFont(font1);
    score.setCharacterSize(20);
    score.setOrigin(0, 0);
    score.setPosition(30, window.getSize().y - 90);
    score.setString("score = " + to_string(cnt));

    //setting chicken textures and positions
    for ( int j = 0; j <6 ; j++)
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
            if (rectangle3.getGlobalBounds().intersects(rectangle2.getGlobalBounds()))
            {
                rectdir = 0;
                ChickenDir = 0;
            }
            else if (rectangle3.getGlobalBounds().intersects(rectangle1.getGlobalBounds()))
            {
                rectdir = 1;
                ChickenDir = 1;
            }
            if (ChickenDir == 0)
                Chicken[i][j].move(-chicken.speed, 0);
            else if (ChickenDir == 1)
                Chicken[i][j].move(chicken.speed, 0);
       }
  
        
    }
    if (rectdir == 0)
        rectangle3.move(-chicken.speed, 0);
    else if (rectdir == 1)
        rectangle3.move(chicken.speed, 0);

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
        window.draw(healh_bar);
        window.draw(hp);
        scorecalc();
        window.draw(score);
        window.draw(rectangle3);
        // show window
        window.display();
    }
    return 0;
}