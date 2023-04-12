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
struct bulletstruct
{
    int heldWeapon = 1;
    float bulletSpeed = 10;
    int currentBullet = 0;
    float bulletCoolDownvar = 10;
    float bulletCoolDown = 0;
};

//Meteor Struct
struct meteorstruct {
    double meteorspeed = 5;
    int meteorhp = 10;
    int meteorcount = 40;
};







// Intialized Variables
long long cnt = 0;  //counter for score
int health = 100;
double PlayerMovement = 9, PlayerSpeed = 12;
double ChickenDir = 0, ChickenPositionX = 0, ChickenPositionY = 0,rectdir;
int ChickenMovement = 0 ;
int timer[8][5];
int eggtimer = 0;
int x = 0, y = 0;
int yolkcnt = 0;
int yolkvar = 10;
int borderadjust = 0;
bool checkchickenanimation = true, check = true;
ChickenStruct chicken;
bulletstruct bullet;
meteorstruct meteors;
int chickenpx[8][6] = {}, chickenpy[8][6] = {};
int foodcnt = 0;
int tmp, meteortimer[40], meteorhp[40], meteorx = 0;
int xmeteor=0, ymeteor=0;

Time deltatime;



// Creating Game Window
RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders",Style::Fullscreen);

// adding textures
Texture Background;
Texture PlayerSkin;
Texture ChickenSkin;
Texture bulletImage;
Texture healthbar;
Texture eggTex;
Texture eggbreak;
Texture Chickenlegs;
Texture meteortex;

// adding border
RectangleShape rectangle1(Vector2f(60, 1080));
RectangleShape rectangle2(Vector2f(60, 1080));
RectangleShape rectangle3(Vector2f(1300, 200));

//adding texts
Text hp;
Text score;
Text foodscore;

//adding font
Font font1;


// Ingame Sprites
Sprite _GameBackground;
Sprite Player;
Sprite Chicken[8][6];
Sprite Bullets[40];
Sprite health_bar;
Sprite Eggs[8][5];
Sprite eggyolk;
Sprite chicken_legs[8][6];
Sprite meteor[40];



// Loading Ingame Files
void IngameImages()
{
    //fonts
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
    rectangle3.setOrigin(1300 / 2, 200);
    rectangle3.setPosition(770, 400);
    rectangle3.setFillColor(Color::Transparent);

    // chicken image
    ChickenSkin.loadFromFile("RedChicken.png");

    //Egg image
    eggTex.loadFromFile("egg.png");
    eggbreak.loadFromFile("eggBreak.png");


    // chicken leg
    Chickenlegs.loadFromFile("chicken leg.png");

    //bullet image
    bulletImage.loadFromFile("Bullet1Image.png");

    //setting health and score bar
    healthbar.loadFromFile("Button1.png");
    health_bar.setTexture(healthbar);
    health_bar.setPosition(0, window.getSize().y - 150);
    health_bar.setScale(1.3, 1.3);

    //health
    hp.setFont(font1);
    hp.setCharacterSize(20);
    hp.setOrigin(0, 0);
    hp.setPosition(30, window.getSize().y - 130);
    hp.setString("health : " + to_string(health));
    //score
    score.setFont(font1);
    score.setCharacterSize(20);
    score.setOrigin(0, 0);
    score.setPosition(30, window.getSize().y - 107);
    score.setString("score = " + to_string(cnt));

    //foodscore
    foodscore.setFont(font1);
    foodscore.setCharacterSize(21);
    foodscore.setOrigin(0, 0);
    foodscore.setPosition(30, window.getSize().y - 82);
    foodscore.setString("food = " + to_string(foodcnt));

    //meteor
    meteortex.loadFromFile("Stones.png");
    for (int i = 0; i < meteors.meteorcount; i++)
    {
        meteor[i].setTexture(meteortex);
    }

    //setting chicken textures and positions
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            Chicken[i][j].setTexture(ChickenSkin);
            Chicken[i][j].setScale(2.75, 2.75);
            Chicken[i][j].setPosition(120 + (ChickenPositionX * 170), 50 + (ChickenPositionY * 100));
            ChickenPositionX++;
        }
        ChickenPositionX = 0;
        ChickenPositionY++;
    }

    //setting bullet textures
    for (int i = 0; i < 40; i++)
    {
        Bullets[i].setTexture(bulletImage);
        Bullets[i].setScale(2, 2);
        Bullets[i].setPosition(-100, -100);
    }

    //Eggs textures
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            Eggs[i][j].setTexture(eggTex);
            Eggs[i][j].setPosition(10000, -10000);
            Eggs[i][j].setScale(0.13, 0.13);

            timer[i][j] = rand() % 501;

        }

    }
    //setting chicken legs
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            chicken_legs[i][j].setTexture(Chickenlegs);
            chicken_legs[i][j].setScale(0.05, 0.05);
            chicken_legs[i][j].setPosition(-100, -100);
        }
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
            PlayerMovement++;
        }

    }
    //Creating Movement For Left Direction
    else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && Player.getPosition().x >= 15)
    {

        Player.setTextureRect(IntRect(PlayerMovement * 60, 0, 60, 42));
        // changing ship to be facing to the left
        Player.move(-PlayerSpeed, 0);
        if (PlayerMovement > 0)
        {
            PlayerMovement--;
        }
    }
    else
    {
        if (PlayerMovement > 9)
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
void PlayerShooting() {

    //Shooting
    if ((Keyboard::isKeyPressed(Keyboard::Space)) && bullet.bulletCoolDown == 0 || (Mouse::isButtonPressed(Mouse::Left)) && bullet.bulletCoolDown == 0)
    {
        bullet.bulletCoolDown = bullet.bulletCoolDownvar;
        Bullets[bullet.currentBullet].setPosition(Player.getPosition().x + 29, Player.getPosition().y - 45);

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
    for (int j = 0; j < 5; j++)
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



// egg movement function
void eggmovement()
{  
    if (x == 0)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 8; i++)
            {

                timer[i][j] = rand() % 501;

            }

        }
        x++;
    }

    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 8; i++)
        {          

            if (timer[i][j] > 0)
            {
                timer[i][j]--;
            }
             
            if(timer[i][j]==0)
            { 
                Eggs[i][j].setScale(0.13, 0.13);
                Eggs[i][j].setPosition(Chicken[i][j].getPosition().x + 53.45, Chicken[i][j].getPosition().y + 75);
                timer[i][j]--;
            }
            if (timer[i][j]==-1)
            {
                Eggs[i][j].move(0, 9.8f);
            }
            if (Eggs[i][j].getPosition().y > Player.getPosition().y + 42)
            {
                timer[i][j] = rand() % 501;
                timer[i][j]--;
                Eggs[i][j].setScale(0, 0);              
            }

            //collision egg

            /*if (Eggs[i][j].getGlobalBounds().intersects(Player.getGlobalBounds()))
            {
                Player.setPosition(10000, 10000);
            }*/


        }
    }
    

}

//Food Movment Function
void FoodMovment() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            if (Chicken[i][j].getPosition().x > 3000 && Chicken[i][j].getPosition().y > 3000)
                chicken_legs[i][j].move(0, 10);

        }
    }
}

//meteor behavior
void meteormove() 
{
    // one time loop for initialization
    if (meteorx == 0) 
    {
        tmp = 100;
        for (int i = 0; i <= 20; i++) 
        {
            meteor[i].setPosition(-100 + tmp, -200);
            meteor[i].setTextureRect(IntRect(62.625 * xmeteor, 62.25 * ymeteor, 62.625f, 62.25f));
            int randscale = rand() % 2 + 1;
            meteorhp[i] = 1 * randscale;
            meteor[i].setScale(randscale, randscale);
            tmp += 100;
            meteortimer[i] = rand() % 400 + 100;
        }
        tmp = 100;
        for (int i = 21; i <= 39; i++)
        {
            meteor[i].setPosition(-200, 0 + tmp);
            meteor[i].setTextureRect(IntRect(62.625 * xmeteor, 62.25 * ymeteor, 62.625f, 62.25f));
            int randscale = rand() % 2 + 1;
            meteorhp[i] = 1 * randscale;
            meteor[i].setScale(randscale, randscale);
            tmp += 50;
            meteortimer[i] = rand() % 400 + 100;
        }
        meteorx++;
    }
    xmeteor++;
    meteorx++;
    // meteor animation loop
    for (int i = 0; i <= 39; i++)
    {
        meteor[i].setTextureRect(IntRect(62.625 * xmeteor, 62.25 * ymeteor, 62.625f, 62.25f));
        if (xmeteor == 7 && ymeteor < 8)
        {
            xmeteor = 0;
            ymeteor++;
            if (ymeteor == 7)
                ymeteor= 0;
        }
    }
    // meteor movement loop
    for (int i = 0; i <= 39; i++) {
        if (meteortimer[i] > 0) {
            meteortimer[i]--;
        }
        if (meteortimer[i] == 0) {
            meteor[i].move(meteors.meteorspeed, meteors.meteorspeed);
        }
        for (int i = 0; i < 40; i++)
        {
            for (int a = 0; a <= 39; a++)
            {
                if (Bullets[i].getGlobalBounds().intersects(meteor[a].getGlobalBounds()))
                {
                    if (meteorhp[a] > 0) 
                    {
                        meteorhp[a] -= 1;
                    }
                    else if (meteorhp[a] == 0)
                    {
                        meteor[a].setPosition(10000, 10000);
                        cnt += 700;
                        score.setString("score : " + to_string(cnt));
                    }
                    Bullets[i].setPosition(-2000, -2000);
                }
            }
        }
    }
    for (int i = 0; i < 40; i++) {
          if (Player.getGlobalBounds().intersects(meteor[i].getGlobalBounds())) {
              Player.setPosition(10000, 10000);
          }
    }

}

//increasing score
void scorecalc() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 8; j++) {
            for (int z = 0; z < 5; z++) {

                if (Bullets[i].getGlobalBounds().intersects(Chicken[j][z].getGlobalBounds())) {
                    cnt += 1000;
                    score.setString("score : " + to_string(cnt));
                    Bullets[i].setPosition(3000, 3000);
                    chicken_legs[j][z].setPosition(Chicken[j][z].getPosition().x, Chicken[j][z].getPosition().y);
                    Chicken[j][z].setPosition(4000, 4000);
                }

                if (chicken_legs[j][z].getGlobalBounds().intersects(Player.getGlobalBounds())) {
                    chicken_legs[j][z].setPosition(4000, -100);
                    foodcnt += 200;
                    foodscore.setString("food : " + to_string(foodcnt));
                }
            }
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
        PlayerShooting();
        eggmovement();
        FoodMovment();
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
                window.draw(chicken_legs[i][j]);
              window.draw(Chicken[i][j]);
            }
        }
      
        for (int i = 0; i < 40; i++) {
            window.draw(Bullets[i]);
        }

        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                window.draw(Eggs[i][j]);
            }
        }

        meteormove();
        scorecalc();
        for (int i = 0; i <= 39; i++) 
        {
            window.draw(meteor[i]);
        }

        window.draw(health_bar);
        window.draw(hp);
       
        window.draw(score);
        window.draw(foodscore);
        window.draw(rectangle3);
        //window.draw(meteor[1]);
        // show window
        window.display();
    }
    return 0;
}