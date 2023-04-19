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
    float bulletCoolDownvar = 8;
    float bulletCoolDown = 0;
};

//Meteor Struct
struct meteorstruct {
    double meteorspeed = 5;
    int meteorhp = 10;
    int meteorcount = 40;
};

//Boss struct
struct bossstruct {

    double bossspeed = 5;
    int bosshp = 50;
    int eggcooldown[5];
    int eggcooldownvar = 301;

};






// Intialized Variables
long long cnt = 0;  //counter for score
int health = 100;
double PlayerMovement = 9, PlayerSpeed = 12;
double ChickenDir = 0, ChickenPositionX = 0, ChickenPositionY = 0,rectdir,bossdir=0;
int ChickenMovement = 0 ;
int timer[8][5];
int eggtimer = 0;
int x = 0, y = 0, z = 0 ,n=15;
int yolkcnt = 0;
int yolkvar = 10;
int countgm = 1;
int pause = 0;
int pausecount = 0;
int pausecooldown=0;
int pausecooldownvar = 40;
int countb = 1;
int option = 0;
int countback = 0;
int checkclick = 0;
int borderadjust = 0;
int animation = 0;
long long testing = 0;
bool checkchickenanimation = true, check = true, bossanimation=true;
ChickenStruct chicken;
bulletstruct bullet;
meteorstruct meteors;
bossstruct boss;
int chickenpx[8][6] = {}, chickenpy[8][6] = {};
int foodcnt = 0;
int tmp, meteortimer[40], meteorhp[40], meteorx = 0;
int xmeteor=0, ymeteor=0;

// Creating Game Window
RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders",Style::Fullscreen);

//delay when starting


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
Texture bossimage;
Texture gamelogo;
Texture gamemenubg;

// adding border
RectangleShape rectangle1(Vector2f(60, 1080));
RectangleShape rectangle2(Vector2f(60, 1080));
RectangleShape rectangle3(Vector2f(1300, 200));
//borders for boss!!
RectangleShape rectangle4(Vector2f(window.getSize().x, 75));
RectangleShape rectangle5(Vector2f(window.getSize().x, 75));


//Buttons
RectangleShape rectanglemainmenu[5];
RectangleShape rectangleoption[2]; 
RectangleShape rectangleback(Vector2f(200, 70));
RectangleShape rectanglecont(Vector2f(350, 70));
//adding texts
Text hp;
Text score;
Text foodscore;
Text play;
Text Options;
Text Leaderboard;
Text Credits;
Text Quit;
Text credits1;
Text credits2;
Text credits3;
Text credits4;
Text credits5;
Text credits6;
Text credits7;
Text controls;
Text sound;
Text back;
Text Option;
Text cont;
//adding font
Font font1;
Font font2;


// Ingame Sprites
Sprite _GameBackground;
Sprite Player;
Sprite Chicken[8][6];
Sprite Bullets[40];
Sprite health_bar;
Sprite Eggs[8][5];
Sprite eggyolk[5];
Sprite bossegg[5];
Sprite bossegg1[5];
Sprite bossegg2[5];
Sprite chicken_legs[8][6];
Sprite meteor[40];
Sprite bosssprite;
Sprite Logo;
Sprite menubg;

// Loading Ingame Files
void IngameImages()
{
    //fonts
    font1.loadFromFile("LATINWD.ttf");
    font2.loadFromFile("font1.ttf");

    // background
    Background.loadFromFile("IngameBackground.jpg");
    _GameBackground.setTexture(Background);
    _GameBackground.setScale(1.875f, 1.05f);
    gamemenubg.loadFromFile("gamemenubg.jpg");
    menubg.setTexture(gamemenubg);
    gamelogo.loadFromFile("logo.png");
    Logo.setTexture(gamelogo);
    Logo.setPosition(423.5, -25);
    Logo.setScale(1, 0.7f);

    //Buttons
    for (int i = 0; i < 5; i++)
    {
        rectanglemainmenu[i].setSize(Vector2f(350, 70));
        rectanglemainmenu[i].setPosition(785, 480 +i*100);
        rectanglemainmenu[i].setFillColor(Color(0, 0, 255, 40));
        rectanglemainmenu[i].setOutlineColor(Color(51, 153, 255, 60));
        rectanglemainmenu[i].setOutlineThickness(2.8f);
    }
    for (int i = 0; i < 2; i++)
    {
        rectangleoption[i].setSize(Vector2f(350, 70));
        rectangleoption[i].setPosition(785, 380 + i * 100);
        rectangleoption[i].setFillColor(Color(0, 0, 255, 40));
        rectangleoption[i].setOutlineColor(Color(51, 153, 255, 60));
        rectangleoption[i].setOutlineThickness(2.8f);
    }
    rectangleback.setPosition(50, 900);
    rectangleback.setFillColor(Color(0, 0, 255, 40));
    rectangleback.setOutlineColor(Color(51, 153, 255, 60));
    rectangleback.setOutlineThickness(2.8f);
    rectanglecont.setPosition(785, 480);
    rectanglecont.setFillColor(Color(0, 0, 255, 40));
    rectanglecont.setOutlineColor(Color(51, 153, 255, 60));
    rectanglecont.setOutlineThickness(2.8f);
    //Play text
    play.setFont(font1);
    play.setCharacterSize(23);
    play.setPosition(807, 500);
    play.setString("Save The World");
    play.setFillColor(Color(204, 229, 255,225));

    //Options text
    Options.setFont(font1);
    Options.setCharacterSize(23);
    Options.setPosition(880, 600); 
    Options.setString("Options");
    Options.setFillColor(Color(204, 229, 255, 225));
  
    //Leaderboard text
    Leaderboard.setFont(font1);
    Leaderboard.setCharacterSize(23);
    Leaderboard.setPosition(830, 700);
    Leaderboard.setString("Hall Of Fame");
    Leaderboard.setFillColor(Color(204, 229, 255, 225));

    //Credits text
    Credits.setFont(font1);
    Credits.setCharacterSize(23);
    Credits.setPosition(885, 800);
    Credits.setString("Credits");
    Credits.setFillColor(Color(204, 229, 255, 225));

    //Quit text
    Quit.setFont(font1);
    Quit.setCharacterSize(23);
    Quit.setPosition(915, 900);
    Quit.setString("Quit");
    Quit.setFillColor(Color(204, 229, 255, 225));

    //controls text
    controls.setFont(font1);
    controls.setCharacterSize(23);
    controls.setPosition(875, 400);
    controls.setString("Controls");
    controls.setFillColor(Color(204, 229, 255, 225));

    //sound text
    sound.setFont(font1);
    sound.setCharacterSize(23);
    sound.setPosition(900, 500);
    sound.setString("Sound");
    sound.setFillColor(Color(204, 229, 255, 225));

    //back text
    back.setFont(font1); 
    back.setCharacterSize(23);
    back.setPosition(80, 920);
    back.setString("< Back");
    back.setFillColor(Color(204, 229, 255, 225));

    //Option text
    Option.setFont(font1);
    Option.setCharacterSize(40);
    Option.setPosition(830, 100);
    Option.setString("Options");
    Option.setFillColor(Color(255, 255, 255, 255));

    //continue text
    cont.setFont(font1);
    cont.setCharacterSize(23);
    cont.setPosition(870, 500);
    cont.setString("Continue");
    cont.setFillColor(Color(204, 229, 255, 225));

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
  
    //boss borders
    rectangle4.setPosition((window.getSize().x / 2), (window.getSize().y / 2)+200);
    rectangle4.setOrigin(window.getSize().x / 2, 75 / 2);
    rectangle5.setPosition(0, -50);
    rectangle4.setFillColor(Color::Transparent);
    rectangle5.setFillColor(Color::Transparent);

    // chicken image
    ChickenSkin.loadFromFile("RedChicken.png");

    //Egg image
    eggTex.loadFromFile("egg.png");
    eggbreak.loadFromFile("eggBreak.png");


    // chicken leg
    Chickenlegs.loadFromFile("chicken leg.png");

    //boss image
    bossimage.loadFromFile("bossRed.png");
  
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
        meteor[i].setTextureRect(IntRect(62.625 * xmeteor, 62.25 * ymeteor, 62.625f, 62.25f));
    }

    //setting chicken textures and positions
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            Chicken[i][j].setTexture(ChickenSkin);
            Chicken[i][j].setScale(2.75, 2.75);
            Chicken[i][j].setPosition(120 + (ChickenPositionX * 170), 50 + (ChickenPositionY * 100));
            Chicken[i][j].setTextureRect(IntRect(ChickenMovement * 46.9, 0, 46.9, 38));
            ChickenPositionX++;
        }
        ChickenPositionX = 0;
        ChickenPositionY++;
    }

    //boss texture and position
    bosssprite.setTexture(bossimage);
    bosssprite.setPosition(Vector2f(200, 200));
    bosssprite.setScale(4.5 , 4.5);
    bosssprite.setTextureRect(IntRect(75*animation, 0, 75, 68));
   
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


            bossegg[j].setTexture(eggTex);
            bossegg[j].setScale(0.25, 0.25);
            bossegg[j].setPosition(10000, 10000);

            bossegg1[j].setTexture(eggTex);
            bossegg1[j].setScale(0.25, 0.25);
            bossegg1[j].setPosition(10000, 10000);

            bossegg2[j].setTexture(eggTex);
            bossegg2[j].setScale(0.25, 0.25);
            bossegg2[j].setPosition(10000, 10000);
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
    
    if ((Keyboard::isKeyPressed(Keyboard::Space)) && bullet.bulletCoolDown == 0 && pausecooldown == 0 || (Mouse::isButtonPressed(Mouse::Left)) && bullet.bulletCoolDown == 0 && pausecooldown == 0)
    {
        bullet.bulletCoolDown = bullet.bulletCoolDownvar;
        pausecooldown = 1;
    }
    if ((Keyboard::isKeyPressed(Keyboard::Space)) && bullet.bulletCoolDown == 0 && pausecooldown==1 || (Mouse::isButtonPressed(Mouse::Left)) && bullet.bulletCoolDown == 0 && pausecooldown == 1)
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

//vertical meteor
void meteorfast()
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
        meteorx++;
    }
    xmeteor++;
    // meteor animation loop
    for (int i = 0; i <= 20; i++)
    {
        meteor[i].setTextureRect(IntRect(62.625 * xmeteor, 62.25 * ymeteor, 62.625f, 62.25f));
        if (xmeteor == 7 && ymeteor < 8)
        {
            xmeteor = 0;
            ymeteor++;
            if (ymeteor == 7)
                ymeteor = 0;
        }
    }
    // meteor movement loop
    for (int i = 0; i <= 20; i++) {
        if (meteortimer[i] > 0) {
            meteortimer[i]--;
        }
        if (meteortimer[i] == 0) {
            meteor[i].move(0, meteors.meteorspeed * 4);
        }
        for (int i = 0; i < 40; i++)
        {
            for (int a = 0; a <= 20; a++)
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
    for (int i = 0; i <= 20; i++) {
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

//Main menu 
void mainmenu()
{
    Vector2i mousepos = Mouse::getPosition(window);
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550)
        {
            // Play
            countb = 0;
            checkclick++;
            pause = 0;
        }
        if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 580 && mousepos.y <= 650)
        {
            // option
            countgm = 0;
            option = 1;
            checkclick++;
        }
        if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 680 && mousepos.y <= 750)
        {
            // hall of fame
            countgm = 0;
            checkclick++;
        }
        if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 780 && mousepos.y <= 850)
        {
            //credits
            countgm = 0;
            checkclick++;
        }
        if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 880 && mousepos.y <= 950)
        {
            // quit
            window.close();
        }
        if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970)
        {
            // back
            countback = 1;
        }


    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 380 && mousepos.y <= 450)
    {
        //controls on
        rectangleoption[0].setFillColor(Color(0, 128, 255, 40));
        rectangleoption[0].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // controls off
        rectangleoption[0].setFillColor(Color(0, 0, 255, 40));
        rectangleoption[0].setOutlineColor(Color(51, 153, 255, 60));
    }

    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550)
    {
        // play continue sound on 
        rectanglemainmenu[0].setFillColor(Color(0,128,255,40));
        rectanglemainmenu[0].setOutlineColor(Color(102, 178, 255, 255));
        rectangleoption[1].setFillColor(Color(0, 128, 255, 40));
        rectangleoption[1].setOutlineColor(Color(102, 178, 255, 255));
        rectanglecont.setFillColor(Color(0, 128, 255, 40));
        rectanglecont.setOutlineColor(Color(102, 178, 255, 255));
    }
    else 
    {
        // play continue sound off
        rectanglemainmenu[0].setFillColor(Color(0, 0, 255, 40));
        rectanglemainmenu[0].setOutlineColor(Color(51, 153, 255, 60));
        rectangleoption[1].setFillColor(Color(0, 0, 255, 40));
        rectangleoption[1].setOutlineColor(Color(51, 153, 255, 60)); 
        rectanglecont.setFillColor(Color(0, 0, 255, 40));  
        rectanglecont.setOutlineColor(Color(51, 153, 255, 60)); 
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 580 && mousepos.y <= 650)
    {
        // options on
        rectanglemainmenu[1].setFillColor(Color(0, 128, 255, 40));
        rectanglemainmenu[1].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        //options off
        rectanglemainmenu[1].setFillColor(Color(0, 0, 255, 40));
        rectanglemainmenu[1].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 680 && mousepos.y <= 750)
    {
        // hall of fame on
        rectanglemainmenu[2].setFillColor(Color(0, 128, 255, 40));
        rectanglemainmenu[2].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // hall of fame off
        rectanglemainmenu[2].setFillColor(Color(0, 0, 255, 40));
        rectanglemainmenu[2].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 780 && mousepos.y <= 850)
    {
        //credits on
        rectanglemainmenu[3].setFillColor(Color(0, 128, 255, 40));
        rectanglemainmenu[3].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        //credits off
        rectanglemainmenu[3].setFillColor(Color(0, 0, 255, 40));
        rectanglemainmenu[3].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 880 && mousepos.y <= 950)
    {
        // quit on
        rectanglemainmenu[4].setFillColor(Color(0, 128, 255, 40));
        rectanglemainmenu[4].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        //quit off
        rectanglemainmenu[4].setFillColor(Color(0, 0, 255, 40));
        rectanglemainmenu[4].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970)
    {
        // back on
        rectangleback.setFillColor(Color(0, 128, 255, 40));
        rectangleback.setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // back off
        rectangleback.setFillColor(Color(0, 0, 255, 40));
        rectangleback.setOutlineColor(Color(51, 153, 255, 60));
    }

    if (Keyboard::isKeyPressed(Keyboard::P))
    {
        pause = 1;
        pausecooldown = 0;
        checkclick = 0;
        
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        pause = 0;
        pausecooldown = 1;
        checkclick = 1;
    }

}

//Boss   By mohamed akram , ziad khaled
void bossmove() {

    //Boss movement + animation
    bosssprite.setTextureRect(IntRect(75 * animation, 0, 75, 68));
    if(countb==0){
    if (bosssprite.getGlobalBounds().intersects(rectangle5.getGlobalBounds()))
        bossdir = 0;
    else if (bosssprite.getGlobalBounds().intersects(rectangle4.getGlobalBounds()))
        bossdir = 1;
    if (bossdir == 0)
        bosssprite.move(boss.bossspeed, boss.bossspeed);
    else if (bossdir == 1)
        bosssprite.move(boss.bossspeed, -boss.bossspeed);
   if (bosssprite.getGlobalBounds().intersects(rectangle2.getGlobalBounds())) {
        bossdir = 3;
    }
    else if (bosssprite.getGlobalBounds().intersects(rectangle1.getGlobalBounds())) {
        bossdir = 1;
    }
    if (bossdir == 3) {
        bosssprite.move(-boss.bossspeed, 0);
    }
    else if (bossdir == 0) {
        bosssprite.move(boss.bossspeed, 0);
    }

    if (animation == 9)
    {
        bossanimation = false;
    }
    else if (animation == 0)
    {
        bossanimation = true;
    }

    if (bossanimation == false)
    {
        animation--;
    }
    else
        animation++;

    //Boss getting killed after collision with bullets
    for (int i = 0; i < 40; i++)
    {
        if (Bullets[i].getGlobalBounds().intersects(bosssprite.getGlobalBounds()))
        {
            if (boss.bosshp > 0)
            {
                boss.bosshp -= 2;
            }
            else if (boss.bosshp == 0)
            {
                bosssprite.setPosition(10000, 10000);
                cnt += 5000;
                score.setString("score : " + to_string(cnt));
            }
            Bullets[i].setPosition(-2000, -2000);
        }
    }
    if (z == 0)
    {
        for (int i = 0; i < 5; i++)
        {

            boss.eggcooldown[i] = rand() % boss.eggcooldownvar;

        }
        z++;
    }

    for (int i = 0; i < 5; i++)
    {

        if (boss.eggcooldown[i] > 0)
        {
            boss.eggcooldown[i]--;
        }

        if (boss.eggcooldown[i] == 0)
        {
            boss.eggcooldown[i]--;
            bossegg[i].setScale(0.2, 0.2);
            bossegg[i].setPosition(bosssprite.getPosition().x, bosssprite.getPosition().y + 68);

            bossegg1[i].setScale(0.2, 0.2);
            bossegg1[i].setPosition(bosssprite.getPosition().x + 30, bosssprite.getPosition().y + 68);

            bossegg2[i].setScale(0.2, 0.2);
            bossegg2[i].setPosition(bosssprite.getPosition().x + 70, bosssprite.getPosition().y + 68);

        }
        if (boss.eggcooldown[i] == -1)
        {
            bossegg[i].move(-3, 9.8f);
            bossegg1[i].move(0, 9.8f);
            bossegg2[i].move(3, 9.8f);
        }
        if (bossegg[i].getPosition().y > Player.getPosition().y + 50)
        {
            boss.eggcooldown[i] = rand() % boss.eggcooldownvar;
            bossegg[i].setScale(0, 0);
            bossegg1[i].setScale(0, 0);
            bossegg2[i].setScale(0, 0);
        }

    }

        //collision egg
        /*if (bossegg[i].getGlobalBounds().intersects(Player.getGlobalBounds()))
        {
            Player.setPosition(10000, 10000);
        }*/


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
            
        //clear window
        window.clear();

        Vector2i mousepos = Mouse::getPosition(window);
        //draw window
        // main menu
        if (testing == 0)
        {
            window.draw(menubg);
            window.draw(Logo);
            mainmenu();
            window.draw(play);
            window.draw(Options);
            window.draw(Leaderboard);
            window.draw(Credits);
            window.draw(Quit);
            for (int i = 0; i < 5; i++)
            {
                window.draw(rectanglemainmenu[i]);
            }
            if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550)
            {
                testing = 1;
                goto vest;
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 580 && mousepos.y <= 650)
            {
                testing = 2;
                goto vest;
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 680 && mousepos.y <= 750)
            {
                testing = 3;
                goto vest;
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 780 && mousepos.y <= 850)
            {
                testing = 4;
                goto vest;
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 880 && mousepos.y <= 950)
            {
                window.close();
            }
        }
    vest: {};
        // select level testing ==1;
        if (testing == 1)
        {
            mainmenu();
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left))
            {
                testing = 0;
            }
            window.draw(menubg);
            window.draw(rectangleback);
            window.draw(back);

        }
        // options testing ==2
        if (testing == 2)
        {
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left))
            {
                testing = 0;
            }
            mainmenu();
            window.draw(menubg);
            window.draw(Option);
            window.draw(rectangleback);
            for(int i =0 ; i < 2 ;i++)
                window.draw(rectangleoption[i]);
            window.draw(controls);
            window.draw(sound);
            window.draw(back);
        }
        // hall of fame testing ==3
        if (testing == 3)
        {
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left))
            {
                testing = 0;
            }
            mainmenu();
            window.draw(menubg);
            window.draw(rectangleback);
            window.draw(back);
        }
        // credits testing ==4
        if (testing == 4)
        {
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left))
            {
                testing = 0;
            }
            mainmenu();
            window.draw(menubg);
            window.draw(rectangleback);
            window.draw(back);
        }
        // window display
        window.display();
    }
    return 0;
}