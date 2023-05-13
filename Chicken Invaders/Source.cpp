#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <utility>

using namespace std;
using namespace sf;

// Chicken Struct
struct ChickenStruct
{
    double HP[8][4], speed = 4;
    double chicken_healthvar = 1, chicken_health = 1;
};

//Bullet Struct
struct bulletstruct
{
    double bulletdamage = 1;
    float bulletSpeed = 10;
    int currentBullet = 0;
    float bulletCoolDownvar = 8;
    float bulletCoolDown = 0;
    float bulletCoolDown2 = 0;
    const int numberofbullets = 50;
};

//spark struct
struct spark_struct {
    int currentspark = 0;
    float sparkcooldownvar = 8;
    float sparkcooldown = 0;

};

//fog struct
struct fogstruct {
    int currentfog = 0;
    float fogcooldownvar = 8;
    float fogcooldown = 0;

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

//camera
sf::View view1(sf::Vector2f(960.f, 540.f), sf::Vector2f(1920.f, 1080.f));

// Creating Game Window
RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders", Style::Fullscreen);

/////////////////////////////////////////////////////////////////////////////////////////

//chicken variables
int ChickenMovement = 0;
double ChickenDir = 0, rectdir, chickeninitialpos = 0;
bool checkchickenanimation = true;
bool chickenalive = true, chickenalive2 = true;
int currentchickensfx = 0;
ChickenStruct chicken;
bool chickendead[8][4];
int alivechicken = 0;
int chick = 0;
int chicken_enter = 0;
Sound chickenhurt[2];
Texture ChickenSkin;
SoundBuffer chickensfx;
Sprite Chicken[8][4];
Sprite Chicken2[8][4];

// adding chicken border
RectangleShape rectangle1(Vector2f(60, 1080));
RectangleShape rectangle2(Vector2f(60, 1080));
RectangleShape rectangle3(Vector2f(1300, 200));

//egg variables
int eggvar = 601;
int timer[8][4];
int yolkcnt = 0;
int yolkanime = 0;
int yolkvar = 100;
int x = 0;
int currenteggshootsfx = 0;
Texture eggTex;
Texture eggbreak;
SoundBuffer eggshootsfx;
Sound eggshoot[2];
Sprite Eggs[8][4];
Sprite eggyolk[8][4];

//chicken food variables
int foodmovespeed = 10;
Texture Chickenlegs;
Sprite chicken_legs[8][4];

//spark and fog variables
int sparkx = 0, fogx = 0, fogy = 0;
int sparkbool = 0;
spark_struct Spark;
fogstruct Fog;
Texture sparkimage;
Texture fogimage;
Sprite spark[50];
Sprite fog[50];

/////////////////////////////////////////////////////////////////////////////////////////

//player1 and 2 variables
double PlayerMovement = 9, PlayerSpeed = 12, Player2Movement = 9, Player2Speed = 12;
bool playeralive = true, player2alive = true; 
bool player_2 = 1;
Texture PlayerSkin;
Texture Player2Skin;
Sprite Player;
Sprite Player2ship;

//ship fire
Texture shipfiretx;
Texture shipfiretx2;
Sprite shipfire;
Sprite shipfire2;
int shipfirescale = 0;
int shipfirescale2 = 0;

//coop variables
bool coopon = false;
int coopclick = 0;

// explosion variables
int exp_x = 0, exp_y = 0;
int exp_x2 = 0, exp_y2 = 0;
int expbool = 0;
int expbool2 = 0;
Sprite explosion;
Sprite explosion2;
Texture explosionimage;
Texture explosionimage2;
SoundBuffer explodingsfx;
Sound exploding;

//shield variables
bool shield_on = 0;
bool shield_on2 = 0;
int shield_timervar = 60;
int shield_timer = 0;
int shield_timervar2 = 60;
int shield_timer2 = 0;
int Timer = 2;
int Timer2 = 2;
CircleShape Shield(60);
CircleShape Shield2(60);

//bullet variables
bulletstruct bullet;
int currentshootsfx = 0, numberofshootsfx = 3;
char checkbullet = 'r';
int randomizer = 0;
int doublebullets = 0;
int pausecooldown = 0;
Texture bulletImage;
Sprite Bullets[50];
SoundBuffer shoot1sfx;
SoundBuffer rocketshootsfx;
SoundBuffer eatingsfx;
SoundBuffer upgradesfx;
SoundBuffer shipinsfx;
SoundBuffer gamewinsfx;
Sound rocketshoot;
Sound eating;
Sound upgradesound;
Sound shipin;
Sound gamewin;
Sound shoot1[3];
Sprite iongift;
Sprite crystalgift;
Texture GiftIon;
Texture GiftCrystal;
Texture crystaltear;

////////////////////////////////////////////////////////////////////////////////////////////

//score-bars variables
int health = 3;
int health3 = 3;
int rockets = 0;    
int powerlvls = 0;
long long cnt = 0;
int foodcnt = 0;
int health2 = health;
int health4 = health3;
Texture healthbar;
Texture GameBarSkin;
Texture BottomBarSkin;
Texture BottomBarSkin2;
Text hp;
Text hp2;
Text rocket;
Text rocket2;
Text score;
Text score2;
Text powerlvl;
Text powerlvl2;
Text foodscore;
Text foodscore2;
Sprite health_bar;
Sprite Gamebar;
Sprite Bottombar;
Sprite Bottombar2;

///////////////////////////////////////////////////////////////////////////////////////////

//boss1 variables
bossstruct boss;
double  bossdir = 0;
int z = 0;
bool  bossanimation=true;
bool bossalive = 0;
int aliveboss = 1;
int bosslvl=1;
int animation = 0;
Texture bossimage;
Sprite bosssprite;

//borders for boss!!
RectangleShape rectangle4(Vector2f(window.getSize().x, 75));
RectangleShape rectangle5(Vector2f(window.getSize().x, 75));


//boss1 egg variables
Sprite bossegg[5];
Sprite bossegg1[5];
Sprite bossegg2[5];

//////////////////////////////////////////////////////////////////////////////////////////

//meteorite variables
int tmp, meteortimer[40], meteorhp[40], meteorx = 0;
int xmeteor=0, ymeteor=0;
meteorstruct meteors;
int meteoralive = 0;
Texture meteortex;
Sprite meteor[40];

/////////////////////////////////////////////////////////////////////////////////////////

//missile variables
int missileScoreCount = 0, camerashakelength = 6;
bool activemissile = false, explosioncamerashake = false;
int rocketx = 0;
Texture missileTexture;
Sprite missile;

/////////////////////////////////////////////////////////////////////////////////////////
 //Main menu
int backgroundspeed = 2;
bool frommenu = true;
bool musicON = true;
bool soundeffectON = true;
int rotatecheck = 0;
bool MainMusicPlaying = true;
int menuchickenx = 5, menuchickeny = 5;
Texture Background;
Texture gamelogo;
Texture gamemenubg;
Texture fork;
Texture earth;
Sound MenuClick;
Music MenuMusic;
Text ret;
Text Quit;
Text back;
Text cont;
Text single;
Sprite _GameBackground[2];
Sprite Logo;
Sprite menubg[2];
Sprite Earth;
Sprite menuchicken;
RectangleShape rectanglemainmenu[5];
RectangleShape rectangleback(Vector2f(200, 70));
SoundBuffer Select;

//borders for interactive background
RectangleShape topborder(Vector2f(1920, 100));
RectangleShape bottomborder(Vector2f(1920, 100));
RectangleShape leftborder(Vector2f(100, 1080));
RectangleShape rightborder(Vector2f(100, 1080));

///////////////////////////////////////////////////////////////////////////////
//leaderboard variables
Text leadernameboard;
bool ldbcheck[5] = { 1,0,0,0,0 };
vector<pair<long long, string >>lvl1score;
vector<pair<long long, string >>lvl2score;
vector<pair<long long, string >>lvl3score;
map<string, long long >mapthird;
vector<pair<long long, string >>lvl4score;
map<string, long long >mapfourth;
vector<pair<long long, string >>lvl5score;
map<string, long long >mapfifth;
map<string, long long >mapfirst;
map<string, long long >mapsecond;
bool validname = false;
int searchl = 0;
Text ldb[5];
Text leadername[6], leaderscore[6], nametext, numbertext;
Text t1;
Text t2;
Text t3;
Text t4;
Font font1;
RectangleShape rectangleldbs[5];


/////////////////////////////////////////////////////////////////////////////////////////

//options variables (sound/controls)
Text Options;
Texture checkmark;
Texture arrow1;
Sprite arrow_l[2];
Sprite arrow_r[2];
Sprite arrow_up[2];
Sprite arrow_dw[2];
Sprite checkbox[2];
Text sound;
Text Option;
Text controls;
Text player1;
Text player2;
Text W;
Text S;
Text D;
Text A;
Text Fire;
Text Space;
Text Up;
Text Down;
Text Right;
Text Left;
Text Fire2;
Text Shift;
Text musiccheck;
Text soundeffectcheck;
RectangleShape rectangleoption[2];
RectangleShape rectanglecontrols[6][2];

/////////////////////////////////////////////////////////////////////////////////////////

//credits
double curscale[7] = { 1, 1, 1, 1, 1, 1, 1 };
Text Credits;
Text Cred[7];
string Name;
Font font3;

/////////////////////////////////////////////////////////////////////////////////////////

//save the world vars
Text play;
int modeselectdelay = 0;
bool IngameMusicPlay = false, IngameMusicPlaying = false;
int lastlevel = 1;
Clock clock4;
Clock clock3;
Music ingamemusic;
bool gameover = false;
bool Wave1 = 1, Wave2 = 0, Wave3 = 0, Wave4 = 0, Wave5 = 0;
char prevwave = '1';
char lvl = '1';
Text levels[5];
Text wave1first;
Text wave1second;
Text endofwave1;
Text congratulation;
Text coop;
Text endoflevel1;
Font font2;
RectangleShape rectanglelevels[5];
RectangleShape rectanglecheck[2];
RectangleShape rectangleselectmode[2];
RectangleShape rectanglecont(Vector2f(350, 70));
RectangleShape rectanglereturn(Vector2f(350, 70));

/////////////////////////////////////////////////////////////////////////////////////////



// Loading Ingame Files
void IngameImages()
{

    //borders for chicken bounce
    topborder.setPosition(0, 0);
    bottomborder.setPosition(0, 980);
    leftborder.setPosition(0, 0);
    rightborder.setPosition(1820, 0);
    //fonts
    font1.loadFromFile("RobotoCondensed-Bold.ttf");
    font3.loadFromFile("Wedgie_Regular.ttf");
    font2.loadFromFile("Lobster-Regular.ttf");
    // audio
    Select.loadFromFile("Select.wav");
    MenuClick.setBuffer(Select);
    shoot1sfx.loadFromFile("weapon1.wav");
    for (int i = 0; i < numberofshootsfx; i++)
    {
        shoot1[i].setBuffer(shoot1sfx);
    }
    chickensfx.loadFromFile("chicken.wav");
    for (int i = 0; i < 2; i++)
    {
        chickenhurt[i].setBuffer(chickensfx);
    }
    eggshootsfx.loadFromFile("eggshoot.wav");
    for (int i = 0; i < 2; i++)
    {
        eggshoot[i].setBuffer(eggshootsfx);
    }
    rocketshootsfx.loadFromFile("rocketshoot.wav");
    rocketshoot.setBuffer(rocketshootsfx);
    explodingsfx.loadFromFile("explosion.wav");
    exploding.setBuffer(explodingsfx);
    eatingsfx.loadFromFile("eating.wav");
    eating.setBuffer(eatingsfx);
    upgradesfx.loadFromFile("upgrade.wav");
    upgradesound.setBuffer(upgradesfx);
    shipinsfx.loadFromFile("player-starting.wav");
    shipin.setBuffer(shipinsfx);
    gamewinsfx.loadFromFile("game win.wav");
    gamewin.setBuffer(gamewinsfx);
    // music
    MenuMusic.openFromFile("IntroMenu.wav");
    ingamemusic.openFromFile("ingame.wav");
    // background
    Background.loadFromFile("IngameBackground.png");
    
    for (int i = 0; i < 2; i++)
    {
        _GameBackground[i].setTexture(Background);
    }
    _GameBackground[1].setPosition(0, -1080);
    gamemenubg.loadFromFile("gamemenubg.png");
    for (int i = 0; i < 2; i++)
    {
        menubg[i].setTexture(gamemenubg);
    }

    menubg[1].setPosition(0, -1080);
    
    gamelogo.loadFromFile("logo.png");
    Logo.setTexture(gamelogo);
    Logo.setPosition(423.5, -25);
    Logo.setScale(1, 0.7f);
    // ingame images
    GameBarSkin.setSmooth(true);
    GameBarSkin.loadFromFile("TopBar.png");
    BottomBarSkin.loadFromFile("leftbar1.png");
    BottomBarSkin.setSmooth(true);
    Bottombar.setTexture(BottomBarSkin);
    Bottombar.setPosition(-70 , 1004);
    Bottombar.setScale(1, 1);

    //ship fire
    shipfiretx.loadFromFile("shipfire.png");
    shipfire.setTexture(shipfiretx);
    shipfire.setOrigin(15, 0);
    shipfire.setColor(Color(255, 165, 6, 240));

    shipfiretx2.loadFromFile("shipfire.png");
    shipfire2.setTexture(shipfiretx2);
    shipfire2.setOrigin(15, 0);
    shipfire2.setColor(Color(255, 165, 6, 240));

    BottomBarSkin2.loadFromFile("rightbar1.png");
    BottomBarSkin2.setSmooth(true);
    Bottombar2.setTexture(BottomBarSkin2);
    Bottombar2.setPosition(1430, 1004);
    Bottombar2.setScale(1, 1);
    Gamebar.setTexture(GameBarSkin);
    Gamebar.setPosition(0, 0);
    Gamebar.setScale(1.5, 1.5);
    //player explosion
    explosionimage.loadFromFile("PlayerDeath.png");
    explosion.setTexture(explosionimage);
    explosion.setPosition(7000, 7000);
    sparkimage.loadFromFile("sparkspink.png");

    explosionimage2.loadFromFile("PlayerDeath.png");
    explosion2.setTexture(explosionimage2);
    explosion2.setPosition(8000, 8000);
    sparkimage.loadFromFile("sparkswhite.png");

    for (int i = 0; i < 50; i++) {
        spark[i].setTexture(sparkimage);
        spark[i].setPosition(8000, 8000);
    fogimage.loadFromFile("fogwhite.png"); 
    fog[i].setTexture(fogimage);
    fog[i].setPosition(9000, 9000);
    }
    

    //Shield
    Shield.setFillColor(Color(0, 102, 204, 140));
    Shield.setPosition(10000, 10000);

    Shield2.setFillColor(Color(0, 102, 204, 140));
    Shield2.setPosition(10500, 10500);

    //Buttons in main menu
    for (int i = 0; i < 5; i++)
    {
        rectanglemainmenu[i].setSize(Vector2f(350, 70));
        rectanglemainmenu[i].setPosition(785, 480 +i*100);
        rectanglemainmenu[i].setFillColor(Color(0, 0, 255, 40));
        rectanglemainmenu[i].setOutlineColor(Color(51, 153, 255, 60));
        rectanglemainmenu[i].setOutlineThickness(2.8f);
    }
    //Buttons in levels selection
    for (int i = 0; i < 5; i++)
    {
        rectanglelevels[i].setSize(Vector2f(350, 70));
        rectanglelevels[i].setPosition(785, 180 + i * 120);
        rectanglelevels[i].setFillColor(Color(0, 0, 255, 40));
        rectanglelevels[i].setOutlineColor(Color(51, 153, 255, 60));
        rectanglelevels[i].setOutlineThickness(2.8f);
    }
    //Buttons in options menu
    for (int i = 0; i < 2; i++)
    {
        rectangleoption[i].setSize(Vector2f(350, 70));
        rectangleoption[i].setPosition(785, 480 + i * 100);
        rectangleoption[i].setFillColor(Color(0, 0, 255, 40));
        rectangleoption[i].setOutlineColor(Color(51, 153, 255, 60));
        rectangleoption[i].setOutlineThickness(2.8f);
    }

    //Buttons in select mode menu
    for (int i = 0; i < 2; i++)
    {
        rectangleselectmode[i].setSize(Vector2f(350, 70));
        rectangleselectmode[i].setPosition(585+i*400 , 480);
        rectangleselectmode[i].setFillColor(Color(0, 0, 255, 40));
        rectangleselectmode[i].setOutlineColor(Color(51, 153, 255, 60));
        rectangleselectmode[i].setOutlineThickness(2.8f);
    }

    //Buttons in sound menu
    for (int i = 0; i < 2; i++)
    {
        rectanglecheck[i].setSize(Vector2f(70, 70));
        rectanglecheck[i].setPosition(985, 480 + i * 100);
        rectanglecheck[i].setFillColor(Color(0, 0, 255, 40));
        rectanglecheck[i].setOutlineColor(Color(51, 153, 255, 60));
        rectanglecheck[i].setOutlineThickness(2.8f);
    }
    //Buttons in control menu
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            rectanglecontrols[i][j].setSize(Vector2f(450, 70));
            rectanglecontrols[i][j].setPosition(500 + j * 470, 480 + i * 100);
            rectanglecontrols[i][j].setFillColor(Color(0, 0, 255, 40));
            rectanglecontrols[i][j].setOutlineColor(Color(51, 153, 255, 60));
            rectanglecontrols[i][j].setOutlineThickness(2.8f);
        }
    }
    //Buttons in leadernameboard menu
    for (int i = 0; i < 5; i++)
    {
        rectangleldbs[i].setSize(Vector2f(350, 70));
        rectangleldbs[i].setPosition(50+i*370, 25 );
        rectangleldbs[i].setFillColor(Color(0, 0, 255, 40));
        rectangleldbs[i].setOutlineColor(Color(51, 153, 255, 60));
        rectangleldbs[i].setOutlineThickness(2.8f);

        leadername[i].setFont(font1);
        leadername[i].setCharacterSize(50);
        leadername[i].setPosition(300, 300 + (100 * i));
        leadername[i].setFillColor(Color::White);

        leaderscore[i].setFont(font1);
        leaderscore[i].setCharacterSize(50);
        leaderscore[i].setPosition(1440, 300 + (100 * i));
        leaderscore[i].setFillColor(Color::White);

    }

    nametext.setString("Name:");
    nametext.setFont(font1);
    nametext.setCharacterSize(50);
    nametext.setFillColor(Color::White);
    nametext.setPosition(300, 200);

    numbertext.setString("Score:");
    numbertext.setFont(font1);
    numbertext.setCharacterSize(50);
    numbertext.setFillColor(Color::White);
    numbertext.setPosition(1440, 200);
 
    //Back Button
    rectangleback.setPosition(50, 900);
    rectangleback.setFillColor(Color(0, 0, 255, 40));
    rectangleback.setOutlineColor(Color(51, 153, 255, 60));
    rectangleback.setOutlineThickness(2.8f);

    //continue Button
    rectanglecont.setPosition(785, 480);
    rectanglecont.setFillColor(Color(0, 0, 255, 40));
    rectanglecont.setOutlineColor(Color(51, 153, 255, 60));
    rectanglecont.setOutlineThickness(2.8f);

    //leadernameboard
    t1.setFont(font1);
    t2.setFont(font1);
    t3.setFont(font1);
    t1.setString("Enter your name");
    t3.setString("Enter your names");
    t1.setCharacterSize(70);
    t2.setCharacterSize(70);
    t3.setCharacterSize(70);
    t4.setCharacterSize(70);
    t1.setPosition(750, 300);
    t2.setPosition(750, 400);
    t3.setPosition(10, 10);
    t4.setPosition(10, 100);
    t1.setFillColor(Color::White);
    t2.setFillColor(Color::White);
    t1.setOutlineColor(Color::Blue);
    t2.setOutlineColor(Color::Blue);
    t3.setFillColor(Color::White);
    t3.setOutlineColor(Color::Blue);
    t4.setFillColor(Color::White);
    t4.setOutlineColor(Color::Blue);


    //back to main menu Button
    rectanglereturn.setPosition(785, 880);
    rectanglereturn.setFillColor(Color(0, 0, 255, 40));
    rectanglereturn.setOutlineColor(Color(51, 153, 255, 60));
    rectanglereturn.setOutlineThickness(2.8f);

    //Play text
    play.setFont(font1);
    play.setCharacterSize(32);
    play.setPosition(860, 495);
    play.setString("Save The World");
    play.setFillColor(Color(204, 229, 255,225));

    //Options text
    Options.setFont(font1);
    Options.setCharacterSize(32);
    Options.setPosition(905, 595); 
    Options.setString("Options");
    Options.setFillColor(Color(204, 229, 255, 225));
  
    //leadernameboard text
    leadernameboard.setFont(font1);
    leadernameboard.setCharacterSize(32);
    leadernameboard.setPosition(880, 695);
    leadernameboard.setString("Hall Of Fame");
    leadernameboard.setFillColor(Color(204, 229, 255, 225));
    // first wave texts
    wave1first.setFont(font1);
    wave1first.setCharacterSize(50);
    wave1first.setPosition(860, 500);
    wave1first.setString("Get Ready!");
    wave1first.setFillColor(Color(204, 229, 255, 225));

    wave1second.setFont(font1);
    wave1second.setCharacterSize(30);
    wave1second.setPosition(920, 600);
    wave1second.setString("Wave "+to_string(prevwave-48));
    wave1second.setFillColor(Color(204, 229, 255, 225));

    endofwave1.setFont(font1);
    endofwave1.setCharacterSize(50);
    endofwave1.setPosition(860, 500);
    endofwave1.setString("Well Played!");
    endofwave1.setFillColor(Color(204, 229, 255, 225));

    congratulation.setFont(font1);
    congratulation.setCharacterSize(50);
    congratulation.setPosition(860, 500);
    congratulation.setString("Congratulations!!!");
    congratulation.setFillColor(Color(204, 229, 255, 225));

    endoflevel1.setFont(font1);
    endoflevel1.setCharacterSize(30);
    endoflevel1.setPosition(920, 600);
    endoflevel1.setString("You Win!!");
    endoflevel1.setFillColor(Color(204, 229, 255, 225));
    //Credits text
    Credits.setFont(font1);
    Credits.setCharacterSize(32);
    Credits.setPosition(910, 795);
    Credits.setString("Credits");
    Credits.setFillColor(Color(204, 229, 255, 225));

    //Quit text
    Quit.setFont(font1);
    Quit.setCharacterSize(32);
    Quit.setPosition(935, 895);
    Quit.setString("Quit");
    Quit.setFillColor(Color(204, 229, 255, 225));

    //controls text
    controls.setFont(font1);
    controls.setCharacterSize(32);
    controls.setPosition(900, 495);
    controls.setString("Controls");
    controls.setFillColor(Color(204, 229, 255, 225));

    //sound text
    sound.setFont(font1);
    sound.setCharacterSize(32);
    sound.setPosition(920, 595);
    sound.setString("Sound");
    sound.setFillColor(Color(204, 229, 255, 225));

    //back text
    back.setFont(font1); 
    back.setCharacterSize(32);
    back.setPosition(100, 915);
    back.setString("< Back");
    back.setFillColor(Color(204, 229, 255, 225));


    //continue text
    cont.setFont(font1);
    cont.setCharacterSize(32);
    cont.setPosition(900, 495);
    cont.setString("Continue");
    cont.setFillColor(Color(204, 229, 255, 225));

    //return text
    ret.setFont(font1);
    ret.setCharacterSize(32);
    ret.setPosition(895, 895);
    ret.setString("Main Menu");
    ret.setFillColor(Color(204, 229, 255, 225));

    //single text
    single.setFont(font1);
    single.setCharacterSize(32);
    single.setPosition(715, 495);
    single.setString("Single");
    single.setFillColor(Color(204, 229, 255, 225));

    //coop text
    coop.setFont(font1);
    coop.setCharacterSize(32);
    coop.setPosition(1115, 495);
    coop.setString("Coop");
    coop.setFillColor(Color(204, 229, 255, 225));

    //levels text
    for (int i = 0; i < 5; i++)
    {
        levels[i].setFont(font1);
        levels[i].setCharacterSize(32);
        levels[i].setPosition(910, 195+i*120);
        levels[i].setString("Level " + to_string(i+1));
        levels[i].setFillColor(Color(204, 229, 255, 225));
    }

    //ldbs text
    for (int i = 0; i < 5; i++)
    {
        ldb[i].setFont(font1);
        ldb[i].setCharacterSize(32);
        ldb[i].setPosition(180 + i * 370, 40);
        ldb[i].setString("Level " + to_string(i + 1));
        ldb[i].setFillColor(Color(204, 229, 255, 225));
    }

    // player1 text
    player1.setFont(font1);
    player1.setCharacterSize(50);
    player1.setPosition(650, 400);
    player1.setString("Player 1");
    player1.setFillColor(Color(0, 128, 255, 255));

    //player2 text
    player2.setFont(font1);
    player2.setCharacterSize(50);
    player2.setPosition(1100, 400);
    player2.setString("Player 2");
    player2.setFillColor(Color(0, 128, 255, 255));

    //music text
    musiccheck.setFont(font1);
    musiccheck.setCharacterSize(32);
    musiccheck.setPosition(825, 495);
    musiccheck.setString("Music");
    musiccheck.setFillColor(Color(204, 229, 255, 225));

    //sound effects text
    soundeffectcheck.setFont(font1);
    soundeffectcheck.setCharacterSize(32);
    soundeffectcheck.setPosition(775, 595);
    soundeffectcheck.setString("Sound Effects");
    soundeffectcheck.setFillColor(Color(204, 229, 255, 225));

    //Control Player 1 and 2 Text
    W.setFont(font1);
    W.setString("W");
    W.setScale(1.5, 1.5);
    W.setPosition(870, 680);
    S.setFont(font1);
    S.setString("S");
    S.setScale(1.5, 1.5);
    S.setPosition(875, 785);
    D.setFont(font1);
    D.setString("D");
    D.setScale(1.5, 1.5);
    D.setPosition(870, 485);
    A.setFont(font1);
    A.setString("A");
    A.setScale(1.5, 1.5);
    A.setPosition(870,585);
    Fire.setFont(font1);
    Fire.setString("Fire");
    Fire.setScale(1.5, 1.5);
    Fire.setPosition(1000, 885);
    Space.setFont(font1);
    Space.setString("Space");
    Space.setScale(1.5, 1.5);
    Space.setPosition(520, 882);
    Up.setFont(font1);
    Up.setString("Up");
    Up.setScale(1.5, 1.5);
    Up.setPosition(1330, 680);
    Down.setFont(font1);
    Down.setString("Down");
    Down.setScale(1.5, 1.5);
    Down.setPosition(1300, 785);
    Right.setFont(font1);
    Right.setString("Right");
    Right.setScale(1.5, 1.5);
    Right.setPosition(1300, 485);
    Left.setFont(font1);
    Left.setString("Left");
    Left.setScale(1.5, 1.5);
    Left.setPosition(1310, 585);
    Space.setFont(font1);
    Space.setString("LeftClick");
    Space.setScale(1.5, 1.5);
    Space.setPosition(1230, 885);
    Fire2.setFont(font1);
    Fire2.setString("Fire");
    Fire2.setScale(1.5, 1.5);
    Fire2.setPosition(530, 885);
    Shift.setFont(font1);
    Shift.setString("Space");
    Shift.setScale(1.5, 1.5);
    Shift.setPosition(830, 885);
    // initializing credits
    for (int i = 0; i < 7; i++)
    {
        Cred[0].setOrigin(332, 16);
        Cred[1].setOrigin(332, 16);
        Cred[2].setOrigin(348, 16);
        Cred[3].setOrigin(316, 16);
        Cred[4].setOrigin(300, 16);
        Cred[5].setOrigin(316, 16);
        Cred[6].setOrigin(300, 16);
        Cred[i].setFont(font3);
        Cred[i].setPosition(900, 1400 + i * 150);
        Cred[i].setCharacterSize(100);
        Cred[i].setFillColor(Color(255, 255, 255, 255));  
        
    }
    //inputing the names
    Cred[0].setString("Kareem Essam");
    Cred[1].setString("Mohamed Wael");
    Cred[2].setString("Mohamed Akram");
    Cred[3].setString(" Malek Ahmed");
    Cred[4].setString("  Ahmed Alaa");
    Cred[5].setString("  Ziad Khaled");
    Cred[6].setString("  Omar Ahmed");
    //sound checkmark
    checkmark.loadFromFile("checkmark.png");
    for (int i = 0; i < 2; i++)
    {
        checkbox[i].setTexture(checkmark);
        checkbox[i].setScale(0.3, 0.3);
        checkbox[i].setPosition(985 , 480+i*100);
        checkbox[i].setColor(Color::Green);
    }
  

    //settings arrows for control menu
    arrow1.loadFromFile("arrow.png");
    for (int i = 0; i < 2; i++)
    {
        arrow_l[i].setTexture(arrow1);
        arrow_l[i].setScale(0.25, 0.25);
        arrow_l[i].setPosition(515 + i * 470, 470);
    }
 
    for (int i = 0; i < 2; i++)
    {
        arrow_r[i].setTexture(arrow1);
        arrow_r[i].setScale(0.25, 0.25);
        arrow_r[i].setPosition(600 + i * 470, 660);
        if(rotatecheck==0)
            arrow_r[i].rotate(180);
    }
    
    for (int i = 0; i < 2; i++)
    {
        arrow_up[i].setTexture(arrow1);
        arrow_up[i].setScale(0.25, 0.25);
        arrow_up[i].setPosition(510 + i * 470, 745);
        arrow_up[i].setTextureRect(IntRect(100, 0, 360, 360));
        if(rotatecheck==0)
            arrow_up[i].rotate(270);
    }

    for (int i = 0; i < 2; i++)
    {
        arrow_dw[i].setTexture(arrow1);
        arrow_dw[i].setScale(0.25, 0.25);
        arrow_dw[i].setPosition(599 + i * 470, 788);
        arrow_dw[i].setTextureRect(IntRect(100, 0, 360, 360));
        if(rotatecheck==0)
            arrow_dw[i].rotate(90);
    }

    // player image
    PlayerSkin.loadFromFile("Playerr.png");
    Player.setTexture(PlayerSkin);
    Player.setTextureRect(IntRect(PlayerMovement * 60, 0, 60, 42));
    Player.setPosition(960, 850);
    Player.setScale(1.5, 1.5);
    rotatecheck=1;

    // player 2 image
    Player2Skin.loadFromFile("playerr22.png");
    Player2ship.setTexture(Player2Skin);
    Player2ship.setTextureRect(IntRect(Player2Movement * 60, 0, 60, 42));
    Player2ship.setPosition(960, 850);
    Player2ship.setScale(1.5, 1.5);



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

    //background chicken
    menuchicken.setTexture(ChickenSkin);
    menuchicken.setPosition(200, 200);
    menuchicken.setScale(1.5,1.5);
    //Egg image
    eggTex.loadFromFile("egg.png");
    eggbreak.loadFromFile("eggBreak.png");



    // chicken leg
    Chickenlegs.loadFromFile("chicken leg.png");

    //boss image
    bossimage.loadFromFile("bossRed.png");
  
    //bullet image
    bulletImage.loadFromFile("Bullet1Image.png");
    crystaltear.loadFromFile("crystaltear.png");

    //health
    hp.setFont(font1);
    hp.setCharacterSize(35);
    hp.setOrigin(0, 0);
    hp.setPosition(147, window.getSize().y - 58);
    hp.setString(to_string(health));

    foodscore2.setFont(font1);
    foodscore2.setCharacterSize(35);
    foodscore2.setOrigin(0, 0);
    foodscore2.setPosition(1810, window.getSize().y - 58);
    foodscore2.setString(to_string(health3));

    // rockets
    rocket.setFont(font1);
    rocket.setCharacterSize(35);
    rocket.setOrigin(0, 0);
    rocket.setPosition(240, window.getSize().y - 58);
    rocket.setString(to_string(rockets));

    powerlvl2.setFont(font1);
    powerlvl2.setCharacterSize(35);
    powerlvl2.setOrigin(0, 0);
    powerlvl2.setPosition(1720, window.getSize().y - 58);
    powerlvl2.setString(to_string(rockets));


    // powerlvl
    powerlvl.setFont(font1);
    powerlvl.setCharacterSize(35);
    powerlvl.setOrigin(0, 0);
    powerlvl.setPosition(325, window.getSize().y - 58);
    powerlvl.setString(to_string(powerlvls));

    rocket2.setFont(font1);
    rocket2.setCharacterSize(35);
    rocket2.setOrigin(0, 0);
    rocket2.setPosition(1635, window.getSize().y - 58);
    rocket2.setString(to_string(powerlvls));

    //score
    score.setFont(font2);
    score.setCharacterSize(45);
    score.setOrigin(0, 0);
    score.setPosition(10, 5);
    score.setString(to_string(cnt));

    //foodscore
    foodscore.setFont(font1);
    foodscore.setCharacterSize(35);
    foodscore.setOrigin(0, 0);
    foodscore.setPosition(420, window.getSize().y - 58);
    foodscore.setString( to_string(foodcnt));

    hp2.setFont(font1);
    hp2.setCharacterSize(35);
    hp2.setOrigin(0, 0);
    hp2.setPosition(1545, window.getSize().y - 58);
    hp2.setString(to_string(foodcnt));

    //meteor
    meteortex.loadFromFile("Stones.png");
    for (int i = 0; i < meteors.meteorcount; i++)
    {
        meteor[i].setTexture(meteortex);
        meteor[i].setTextureRect(IntRect(62.625 * xmeteor, 62.25 * ymeteor, 62.625f, 62.25f));
    }

    //missile image
    missileTexture.loadFromFile("rockets.png");
    missile.setTexture(missileTexture);
    missile.setPosition(10000, 10000);
    missile.setScale(0.3, 0.3);
    

    //boss texture and position
    bosssprite.setTexture(bossimage);
    bosssprite.setPosition(Vector2f(200, 200));
    bosssprite.setScale(0.3436 , 0.385);
    bosssprite.setTextureRect(IntRect(982*animation, 0, 982, 794));
    //setting bullet textures
    for (int i = 0; i < bullet.numberofbullets; i++)
    {
        Bullets[i].setTexture(bulletImage);
        Bullets[i].setScale(2, 2);
        Bullets[i].setPosition(-1000, -1000);

    }

    //Eggs textures
    for (int j = 0; j < 4; j++)
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

            eggyolk[i][j].setTexture(eggbreak);
            eggyolk[i][j].setTextureRect(IntRect(28 * 5, 0, 28, 24));
            eggyolk[i][j].setScale(2, 2);

    
        }

    }

    //setting chicken legs
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            chicken_legs[i][j].setTexture(Chickenlegs);
            chicken_legs[i][j].setScale(0.3, 0.3);
            chicken_legs[i][j].setPosition(-100, -100);
            chicken_legs[i][j].setOrigin(57, 70);
        }
    }

    //ion gift image
    GiftIon.loadFromFile("GIFTIonBlaster.png");
    iongift.setTexture(GiftIon);
    iongift.setPosition(-100, -100);


    //crystal gift image
    GiftCrystal.loadFromFile("GIFTHypergun.png");
    crystalgift.setTexture(GiftCrystal);
    crystalgift.setPosition(-100, -100);
}


// function for player movement
void PlayerMove()
{
    // Kareem Essam and Mohamed Wael
    // Creating Movement For Right Direction
    if (Keyboard::isKeyPressed(Keyboard::D)&& Player.getPosition().x <= 1800)
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
    else if (Keyboard::isKeyPressed(Keyboard::A) && Player.getPosition().x >= 15)
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

    if (Keyboard::isKeyPressed(Keyboard::Right) && Player2ship.getPosition().x <= 1800)
    {
        // changing ship to be facing to the right
        Player2ship.setTextureRect(IntRect(Player2Movement * 60, 0, 60, 42));
        Player2ship.move(PlayerSpeed, 0);

        if (Player2Movement < 18)
        {
            Player2Movement++;
        }

    }
    //Creating Movement For Left Direction
    else if (Keyboard::isKeyPressed(Keyboard::Left) && Player2ship.getPosition().x >= 15)
    {

        Player2ship.setTextureRect(IntRect(Player2Movement * 60, 0, 60, 42));
        // changing ship to be facing to the left
        Player2ship.move(-PlayerSpeed, 0);
        if (Player2Movement > 0)
        {
            Player2Movement--;
        }
    }
    else
    {
        if (Player2Movement > 9)
        {
            Player2Movement--;
            Player2ship.setTextureRect(IntRect(Player2Movement * 60, 0, 60, 42));
        }
        else if (Player2Movement < 9)
        {
            Player2Movement++;
            Player2ship.setTextureRect(IntRect(Player2Movement * 60, 0, 60, 42));
        }
    }
    //shipe fire
    shipfire.setPosition(Player.getPosition().x + 45, Player.getPosition().y + 45);
    if (shipfirescale == 0)
    {
        shipfire.setScale(1, 1.2);
        shipfirescale++;
    }
    else
    {
        shipfire.setScale(1, 1);
        shipfirescale--;
    }
    if (Keyboard::isKeyPressed(Keyboard::D) && Player.getPosition().x <= 1800)
    {
        if (shipfire.getRotation() <= 40)
        {
            shipfire.rotate(4);
            
        }

    }
    else
    {
        if (shipfire.getRotation() > 0 && shipfire.getRotation() < 50)
        {
            shipfire.rotate(-4);
            
        }
    }

    shipfire2.setPosition(Player2ship.getPosition().x + 45, Player2ship.getPosition().y + 45);
    if (shipfirescale2 == 0)
    {
        shipfire2.setScale(1, 1.2);
        shipfirescale2++;
    }
    else
    {
        shipfire2.setScale(1, 1);
        shipfirescale2--;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && Player2ship.getPosition().x <= 1800)
    {
        if (shipfire2.getRotation() <= 40)
        {
            shipfire2.rotate(4);

        }

    }
    else
    {
        if (shipfire2.getRotation() > 0 && shipfire2.getRotation() < 50)
        {
            shipfire2.rotate(-4);

        }
    }

    if (Keyboard::isKeyPressed(Keyboard::A) && Player.getPosition().x <= 1800)
    {
        if (shipfire.getRotation() >= 320 || shipfire.getRotation() == 0)
        {
            shipfire.rotate(-4);
        }
    }
    else
    {
        if (shipfire.getRotation() < 360 && shipfire.getRotation() >= 300)
        {
            shipfire.rotate(4);

        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && Player2ship.getPosition().x <= 1800)
    {
        if (shipfire2.getRotation() >= 320 || shipfire2.getRotation() == 0)
        {
            shipfire2.rotate(-4);
        }
    }
    else
    {
        if (shipfire2.getRotation() < 360 && shipfire2.getRotation() >= 300)
        {
            shipfire2.rotate(4);

        }
    }
}
//spark and fog
void spark_fog() {


    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 8; j++) {
            for (int z = 0; z < 4; z++) {
                if (Bullets[i].getGlobalBounds().intersects(Chicken[j][z].getGlobalBounds())) {
                    chickenalive = false;
                    spark[i].setPosition(Chicken[j][z].getPosition() - Vector2f(50, 50));
                
                       
                   
                }
            }
        }
    }
    if (chickenalive == false) {
        for (int i = 0; i < 50; i++) {
            spark[i].setTextureRect(IntRect(266 * sparkx, 0, 266, 266));
            fog[i].setTextureRect(IntRect(64 * fogx, 0, 64, 62));
        }
        fogx++;
        sparkx++;
        if (sparkx == 5)
        {
            sparkx = 0;
            spark[Spark.currentspark].setPosition(10000, 10000);
        }
        if (fogx == 10) {
            fogx = 0;

            chickenalive = true;
            if (chickenalive == true)
                for (int i = 0; i < 50; i++) {
                    spark[i].setPosition(4000, 5000);
                    fog[i].setPosition(6000, 5000);
                }
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
        //Shield.setPosition(10000, 10000);
    }

    if ((Keyboard::isKeyPressed(Keyboard::Space)) && bullet.bulletCoolDown == 0 && pausecooldown == 1)
    {
        bullet.bulletCoolDown = bullet.bulletCoolDownvar;
        if (doublebullets==0)
        Bullets[bullet.currentBullet].setPosition(Player.getPosition().x + 35, Player.getPosition().y - 45);
        else if (doublebullets == 1)
        {
            Bullets[bullet.currentBullet].setPosition(Player.getPosition().x + 20, Player.getPosition().y - 45);
            Bullets[bullet.currentBullet+1].setPosition(Player.getPosition().x + 50, Player.getPosition().y - 45);
            bullet.currentBullet++;
            if (bullet.currentBullet >= 40 ) {
                bullet.currentBullet = 0;
            }
        }
        else if (doublebullets == 2)
        {
            Bullets[bullet.currentBullet].setPosition(Player.getPosition().x + 20, Player.getPosition().y - 45);
            if (bullet.currentBullet+1 >= 40) {
                bullet.currentBullet = 0;
            }
            Bullets[bullet.currentBullet + 1].setPosition(Player.getPosition().x + 50, Player.getPosition().y - 45);
            if (bullet.currentBullet+2 >= 40) {
                bullet.currentBullet = 0;
            }
            Bullets[bullet.currentBullet + 2].setPosition(Player.getPosition().x + 35, Player.getPosition().y -70);
            bullet.currentBullet += 2;
            if (bullet.currentBullet >= 40) {
                bullet.currentBullet = 0;
            }
        }
       

        //sfx
        if (soundeffectON && playeralive)
        {
            shoot1[currentshootsfx].play();
            currentshootsfx++;
            if (currentshootsfx == numberofshootsfx)
            {
                currentshootsfx = 0;
            }
        }
        //current bullet for shooting
        if (bullet.currentBullet >= 40) {
            bullet.currentBullet = 0;
        }
        bullet.currentBullet++;
        
    }
    if ((Mouse::isButtonPressed(Mouse::Left)) && bullet.bulletCoolDown2 == 0 && pausecooldown == 1 && coopon)
    {
        bullet.bulletCoolDown2 = bullet.bulletCoolDownvar;
        Bullets[bullet.currentBullet].setPosition(Player2ship.getPosition().x + 29, Player2ship.getPosition().y - 45);

        //sfx
        if (soundeffectON && playeralive)
        {
            shoot1[currentshootsfx].play();
            currentshootsfx++;
            if (currentshootsfx == numberofshootsfx)
            {
                currentshootsfx = 0;
            }
        }
        //current bullet for shooting
        if (bullet.currentBullet == bullet.numberofbullets - 1) {
            bullet.currentBullet = 0;
        }
        bullet.currentBullet++;
    }


    if (bullet.bulletCoolDown2 > 0) {
        bullet.bulletCoolDown2--;
    }
    if (bullet.bulletCoolDown > 0) {
        bullet.bulletCoolDown--;
    }

    //bullet moving
    for (int i = 0; i < bullet.numberofbullets; i++) {
        Bullets[i].move(0, -bullet.bulletSpeed);
        if (Bullets[i].getPosition().y < 0)
        {
            Bullets[i].setPosition(20000, 20000);
        }
    }
}

//missile shooting function
void rocketshooting()
{
    //shooting
    if (Keyboard::isKeyPressed(Keyboard::LShift) && activemissile == false && rockets > 0)
    {
        activemissile = true;
        if (soundeffectON)
        {
            rocketshoot.play();
        }
        missile.setPosition(Player.getPosition().x + 29, Player.getPosition().y - 45);
        rockets--;
        rocket.setString(to_string(rockets));
        rocket2.setString(to_string(rockets));
    }

    if (Mouse::isButtonPressed(Mouse::Right) && activemissile == false && rockets > 0 && coopon)
    {
        activemissile = true;
        if (soundeffectON) 
        {
            rocketshoot.play();
        }
        missile.setPosition(Player2ship.getPosition().x + 29, Player2ship.getPosition().y - 45);
        rockets--;
        rocket.setString(to_string(rockets));
        rocket2.setString(to_string(rockets));
    }

    //missile moving
    if (activemissile == true)
    {
        missile.move(0, -bullet.bulletSpeed * 2);
        missile.setTextureRect(IntRect(183 * rocketx, 0, 183, 229));
        rocketx++;
        if (rocketx == 10)
        {
            rocketx = 0;
        }
    }


    //missile explosion
    if (missile.getPosition().y <= 400)
    {
        activemissile = false;
        missile.setPosition(10000, 10000);
        explosioncamerashake = true;
        if (soundeffectON)
        {
            exploding.play();
        }
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                Chicken[i][j].setPosition(10000, 10000);
            }
        }
        if (aliveboss == 1)
        {
            boss.bosshp -= 15;
        }
    }

}

//camera shake
void camerashake()
{
    if (camerashakelength > 0 && camerashakelength % 2 == 0 && explosioncamerashake)
    {
        view1.zoom(0.9f);
        camerashakelength--;
    }
    else if (camerashakelength > 0 && explosioncamerashake)
    {
        view1.zoom(1.1f);
        camerashakelength--;
    }
    if (camerashakelength == 0)
    {
        view1.setSize(sf::Vector2f(1920.f, 1080.f));
        //aliveboss = 0;
        alivechicken = 0;
        meteoralive = 0;
        explosioncamerashake = false;
        camerashakelength = 6;
    }
}
// function for chicken movement
void ChickenMove()
{
    // mohamed wael and kareem essam
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            Chicken[i][j].setTexture(ChickenSkin);
            Chicken[i][j].setScale(3.25, 3.25);
            if (chickeninitialpos == 0) 
            {
                if (j == 0 || j == 2)
                {
                    
                    Chicken[i][j].setPosition(-1842 + (i * 170), 70 + (j * 150));
                }
                else
                Chicken[i][j].setPosition(2065 + (i * 170), 70 + (j * 150));
            }
            Chicken[i][j].setTextureRect(IntRect(ChickenMovement * 46.9, 0, 46.9, 38));


            
        }
    }
    chickeninitialpos = 1;

    if (chick==0)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                chicken.HP[i][j] = chicken.chicken_health + (chicken.chicken_healthvar * 0.5 + 0.5);
            }
        }
        

        chick++;
    }
    
    
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 8; i++)
        {   
            if (chicken_enter == 0)
            {
                if (j == 0 || j == 2)
                {
                    Chicken[i][j].move(8, 0);
                }
                else
                    Chicken[i][j].move(-8, 0);
                
                if (Chicken[0][0].getPosition().x >= 115)
                {
                    chicken_enter = 1;
                }
            }
            else
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
    }
            
    if (chicken_enter != 0)
    {
        if (rectdir == 0)
            rectangle3.move(-chicken.speed, 0);
        else if (rectdir == 1)
            rectangle3.move(chicken.speed, 0);
        
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
//reducing heart by 1  (ahmed,ziad)
void playerdamage() {

    if (true)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                if (Eggs[i][j].getGlobalBounds().intersects(Player.getGlobalBounds())) {
                    health -= 1;
                    if (doublebullets > 0)
                        doublebullets -= 1;
                    if (soundeffectON)
                    {
                        exploding.play();
                    }
                    hp.setString(to_string(health));
                    Eggs[i][j].setPosition(4000, 5000);
                }
                if (Eggs[i][j].getGlobalBounds().intersects(Player2ship.getGlobalBounds()) && coopon)
                {
                    health3 -= 1;
                    if (soundeffectON)
                    {
                        exploding.play();
                    }
                    hp2.setString(to_string(health3));
                    Eggs[i][j].setPosition(4000, 5000);

                }

            }
        }
        //boss egg damage
        for (int i = 0; i < 5; i++)
        {
            if (bossegg[i].getGlobalBounds().intersects(Shield.getGlobalBounds()))
            {
                bossegg[i].setPosition(10000, 10000);
            }
            if (bossegg[i].getGlobalBounds().intersects(Shield2.getGlobalBounds()))
            {
                bossegg[i].setPosition(10000, 10000);
            }

            if (bossegg1[i].getGlobalBounds().intersects(Shield.getGlobalBounds()))
            {
                bossegg1[i].setPosition(10000, 10000);
            }
            if (bossegg1[i].getGlobalBounds().intersects(Shield2.getGlobalBounds()))
            {
                bossegg1[i].setPosition(10000, 10000);
            }

            if (bossegg2[i].getGlobalBounds().intersects(Shield.getGlobalBounds()))
            {
                bossegg2[i].setPosition(10000, 10000);
            }
            if (bossegg2[i].getGlobalBounds().intersects(Shield2.getGlobalBounds()))
            {
                bossegg2[i].setPosition(10000, 10000);
            }


            if (bossegg[i].getGlobalBounds().intersects(Player.getGlobalBounds())) {
                health -= 1;
                if (soundeffectON)
                {
                    exploding.play();
                }
                hp.setString(to_string(health));
                bossegg[i].setPosition(4000, 5000);
            }
            if (bossegg[i].getGlobalBounds().intersects(Player2ship.getGlobalBounds()) && coopon)
            {
                health3 -= 1;
                if (soundeffectON)
                {
                    exploding.play();
                }
                hp2.setString(to_string(health3));
                bossegg[i].setPosition(4000, 5000);

            }

            if (bossegg1[i].getGlobalBounds().intersects(Player.getGlobalBounds())) {
                health -= 1;
                if (soundeffectON)
                {
                    exploding.play();
                }
                hp.setString(to_string(health));
                bossegg1[i].setPosition(4000, 5000);
            }
            if (bossegg1[i].getGlobalBounds().intersects(Player2ship.getGlobalBounds()) && coopon)
            {
                health3 -= 1;
                if (soundeffectON)
                {
                    exploding.play();
                }
                hp2.setString(to_string(health3));
                bossegg1[i].setPosition(4000, 5000);

            }

            if (bossegg2[i].getGlobalBounds().intersects(Player.getGlobalBounds())) {
                health -= 1;
                if (soundeffectON)
                {
                    exploding.play();
                }
                hp.setString(to_string(health));
                bossegg2[i].setPosition(4000, 5000);
            }
            if (bossegg2[i].getGlobalBounds().intersects(Player2ship.getGlobalBounds()) && coopon)
            {
                health3 -= 1;
                if (soundeffectON)
                {
                    exploding.play();
                }
                hp2.setString(to_string(health3));
                bossegg2[i].setPosition(4000, 5000);

            }
        }
        
        if (health < health2) {

            playeralive = false;

        }

        if (health3 < health4)
        {
            player2alive = false;
        }

        if (playeralive == false) {

            if (expbool == 0) {
                expbool = 1;
                explosion.setPosition(Player.getPosition());
            }
            Player.setPosition(6000, 6000);
            explosion.setTextureRect(IntRect(96.6 * exp_x, 5 + (90.6 * exp_y), 96.6, 90.6));
            exp_x++;
            if (exp_x == 7 && exp_y < 3) {
                exp_y++;
                exp_x = 0;
            }
            if (exp_y == 2 && exp_x == 5) {
                exp_y = 0;
                exp_x = 0;
                health2 = health;
                expbool = 0;

                if (Timer <= 0) {
                    playeralive = true;

                    Timer = 2;

                    if (coopon == false)
                    {
                        if (health == 0)
                        {
                            Player.setPosition(12121, 12121);
                            gameover = true;
                            MainMusicPlaying = true;
                            IngameMusicPlaying = false;
                            if (musicON)
                            {
                                MenuMusic.play();
                                ingamemusic.stop();
                            }
                        }
                        else
                        {
                            Player.setPosition(960, 850);
                            Shield.setPosition(Player.getPosition().x - 18, Player.getPosition().y - 25);
                            shield_on = 1;
                            shield_timer = shield_timervar;

                        }
                    }
                   
                    if (coopon)
                    {
                        if (health == 0 && health3 == 0) {
                            gameover = true;
                            MainMusicPlaying = true;
                            IngameMusicPlaying = false;
                            if (musicON)
                            {
                                MenuMusic.play();
                                ingamemusic.stop();
                            }
                        }
                        if (health == 0)
                        {
                            Player.setPosition(12121, 12121);
                        }
                        else
                        {
                            Player.setPosition(960, 850);
                            Shield.setPosition(Player.getPosition().x - 18, Player.getPosition().y - 25);
                            shield_on = 1;
                            shield_timer = shield_timervar;

                        }
                    }
                    
                    

                }
                else
                    Timer--;

            }

        }
        if (player2alive == false)
        {
            if (expbool2 == 0) {
                expbool2 = 1;
                explosion2.setPosition(Player2ship.getPosition());
            }
            Player2ship.setPosition(9000, 9000);
            explosion2.setTextureRect(IntRect(96.6 * exp_x2, 5 + (90.6 * exp_y2), 96.6, 90.6));
            exp_x2++;
            if (exp_x2 == 7 && exp_y2 < 3) {
                exp_y2++;
                exp_x2 = 0;
            }
            if (exp_y2 == 2 && exp_x2 == 5) {
                exp_y2 = 0;
                exp_x2 = 0;
                health4 = health3;
                expbool2 = 0;

                if (Timer2 <= 0) {
                    player2alive = true;

                    Timer2 = 2;


                    if (health3 == 0 ) {
                        Player2ship.setPosition(11111, 11111);
                        player_2 = 0;
                    }
                    else
                    {
                        Player2ship.setPosition(1000, 850);
                        Shield2.setPosition(Player2ship.getPosition().x - 18, Player2ship.getPosition().y - 25);
                        shield_on2 = 1;
                        shield_timer2 = shield_timervar2;
                    }

                    if (health == 0 && health3 == 0) {
                        gameover = true;
                        MainMusicPlaying = true;
                        IngameMusicPlaying = false;
                        if (musicON)
                        {
                            MenuMusic.play();
                            ingamemusic.stop();
                        }
                    }
                }
                else
                    Timer2--;

            }
        }
    }
}

//Shield movement
void shield_move()
{
    if (shield_on == 1 && shield_timer > 0)
    {

        Shield.setPosition(Player.getPosition().x - 18, Player.getPosition().y - 25);
        shield_timer--;
    }
    else
    {
        Shield.setPosition(10000, 10000);
        shield_on = 0;
    }
    if (shield_on2 == 1 && shield_timer2 > 0)
    {

        Shield2.setPosition(Player2ship.getPosition().x - 18, Player2ship.getPosition().y - 25);
        shield_timer2--;
    }
    else
    {
        Shield2.setPosition(10000, 10000);
        shield_on2 = 0;
    }

}

// egg movement function
void eggmovement()
{
    if (x == 0)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 8; i++)
            {

                timer[i][j] = 0;

            }

        }
        eggvar = 601 - chicken.chicken_health * 50;
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 8; i++)
            {

                timer[i][j] = rand() % eggvar;

            }

        }
        x++;
    }

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 8; i++)
        {

            if (timer[i][j] > 0)
            {
                timer[i][j]--;
            }

            if (timer[i][j] == 0)
            {
                eggyolk[i][j].setScale(0, 0);
                Eggs[i][j].setScale(0.13, 0.13);
                Eggs[i][j].setPosition(Chicken[i][j].getPosition().x + 53.45, Chicken[i][j].getPosition().y + 75);


                if (soundeffectON && Eggs[i][j].getPosition().x < 1920)
                {
                    eggshoot[currenteggshootsfx].play();
                    currenteggshootsfx++;
                    if (currenteggshootsfx == 2)
                    {
                        currenteggshootsfx = 0;
                    }
                }
                timer[i][j]--;
            }
            if (timer[i][j] == -1)
            {
                Eggs[i][j].move(0, 9.8f);
            }
            if (Eggs[i][j].getPosition().y >= 1000)
            {
                eggyolk[i][j].setPosition(Eggs[i][j].getPosition().x, 1000);
                timer[i][j] = rand() % eggvar;
                timer[i][j]--;
                Eggs[i][j].setScale(0, 0);
                eggyolk[i][j].setScale(2, 2);

            }
            if (Eggs[i][j].getGlobalBounds().intersects(Shield.getGlobalBounds()))
            {
                Eggs[i][j].setPosition(10000, 10000);
            }
            if (Eggs[i][j].getGlobalBounds().intersects(Shield2.getGlobalBounds()))
            {
                Eggs[i][j].setPosition(10000, 10000);
            }

        }
    }
}
//Food Movment Function
void FoodMovment() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (Chicken[i][j].getPosition().x > 3000 && Chicken[i][j].getPosition().y > 3000)
            {
                chicken_legs[i][j].move(0, foodmovespeed); 
                chicken_legs[i][j].rotate(10);
            }
        }
        iongift.move(0, 1);
        crystalgift.move(0, 1);
    }
}

void bouncingchicken() 
{
    menuchicken.setTextureRect(IntRect(ChickenMovement * 46.9, 0, 46.9, 38));
    if (ChickenMovement == 9)
        checkchickenanimation = false;
    else if (ChickenMovement == 0)
        checkchickenanimation = true;
    if (checkchickenanimation == false)
        ChickenMovement--;
    else
        ChickenMovement++;
    menuchicken.setOrigin(23,19);
    menuchicken.rotate(7);
    

    if (menuchicken.getGlobalBounds().intersects(rightborder.getGlobalBounds()))
    {
        menuchickenx *= -1;
    }
    else if (menuchicken.getGlobalBounds().intersects(bottomborder.getGlobalBounds()))
    {
        menuchickeny *= -1;
    }
    else if (menuchicken.getGlobalBounds().intersects(topborder.getGlobalBounds()))
    {
        menuchickeny *= -1;
    }
    else if (menuchicken.getGlobalBounds().intersects(leftborder.getGlobalBounds()))
    {
        menuchickenx *= -1;
    }
    
    

    menuchicken.move(menuchickenx, menuchickeny);
}

void movingbackround()
{
    for (int i = 0; i < 2; i++)
    {
        //menu bg
        menubg[i].move(0, backgroundspeed);
        if (menubg[i].getPosition().y >= 1080)
        {
            menubg[i].setPosition(0, menubg[i].getPosition().y - (1080 * 2));
        }
        
        window.draw(menubg[i]);

        //ingame bg
        _GameBackground[i].move(0, backgroundspeed);
        if (_GameBackground[i].getPosition().y >= 1080)
        {
            _GameBackground[i].setPosition(0, _GameBackground[i].getPosition().y - (1080 * 2));
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
        for (int i = 0; i < bullet.numberofbullets; i++)
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
                        score.setString(to_string(cnt));
                    }
                    Bullets[i].setPosition(-2000, -2000);
                }
            }
        }
    }

    for (int i = 0; i < 40; i++) {
        if (Player.getGlobalBounds().intersects(meteor[i].getGlobalBounds()) && shield_on == false) {
            health -= 1;
            if (soundeffectON)
            {
                exploding.play();
            }
            hp.setString(to_string(health));
            if (health < health2) {

                playeralive = false;

            }
            if (playeralive == false) {

                if (expbool == 0) {
                    expbool = 1;
                    explosion.setPosition(Player.getPosition());
                }
                Player.setPosition(6000, 6000);
                explosion.setTextureRect(IntRect(96.6 * exp_x, 5 + (90.6 * exp_y), 96.6, 90.6));
                exp_x++;
                if (exp_x == 7 && exp_y < 3) {
                    exp_y++;
                    exp_x = 0;
                }
                if (exp_y == 2 && exp_x == 5) {
                    exp_y = 0;
                    exp_x = 0;
                    health2 = health;
                    expbool = 0;

                    if (Timer <= 0) {
                        playeralive = true;

                        Timer = 2;
                        if (health == 0)
                        {
                            Player.setPosition(12121,12121);
                        }

                        if (health == 0 && player_2==0) {
                            gameover = true;
                        }
                        else
                        {
                            Player.setPosition(960, 850);
                            Shield.setPosition(Player.getPosition().x - 18, Player.getPosition().y - 25);
                            shield_on = 1;
                        }

                    }
                    else
                        Timer--;

                }

            }
        }

        if (Player2ship.getGlobalBounds().intersects(meteor[i].getGlobalBounds()) && shield_on2 == false) {
            health3 -= 1;
            if (soundeffectON)
            {
                exploding.play();
            }
            hp2.setString(to_string(health3));
            if (health3 < health4) {

                player2alive = false;

            }
            if (player2alive == false) {

                if (expbool2 == 0) {
                    expbool2 = 1;
                    explosion2.setPosition(Player2ship.getPosition());
                }
                Player2ship.setPosition(6000, 6000);
                explosion2.setTextureRect(IntRect(96.6 * exp_x2, 5 + (90.6 * exp_y2), 96.6, 90.6));
                exp_x2++;
                if (exp_x2 == 7 && exp_y2 < 3) {
                    exp_y2++;
                    exp_x2 = 0;
                }
                if (exp_y2 == 2 && exp_x2 == 5) {
                    exp_y2 = 0;
                    exp_x2 = 0;
                    health4 = health3;
                    expbool2 = 0;

                    if (Timer2 <= 0) {
                        player2alive = true;

                        Timer2 = 2;


                        if (health3 == 0) {
                            player_2 = 0;
                        }
                        else
                        {
                            Player2ship.setPosition(960, 850);
                            Shield2.setPosition(Player2ship.getPosition().x - 18, Player2ship.getPosition().y - 25);
                            shield_on2 = 1;
                        }

                    }
                    else
                        Timer2--;

                }

            }
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
        for (int i = 0; i < bullet.numberofbullets; i++)
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
    for (int i = 0; i < 20; i++) {
        if (Player.getGlobalBounds().intersects(meteor[i].getGlobalBounds()) && shield_on == false) {
            health -= 1;
            if (soundeffectON)
            {
                exploding.play();
            }
            if (health < health2) {

                playeralive = false;

            }
            if (playeralive == false) {

                if (expbool == 0) {
                    expbool = 1;
                    explosion.setPosition(Player.getPosition());
                }
                Player.setPosition(6000, 6000);
                explosion.setTextureRect(IntRect(96.6 * exp_x, 5 + (90.6 * exp_y), 96.6, 90.6));
                exp_x++;
                if (exp_x == 7 && exp_y < 3) {
                    exp_y++;
                    exp_x = 0;
                }
                if (exp_y == 2 && exp_x == 5) {
                    exp_y = 0;
                    exp_x = 0;
                    health2 = health;
                    expbool = 0;

                    if (Timer <= 0) {
                        playeralive = true;

                        Timer = 2;

                        if (health == 0)
                        {
                            Player.setPosition(12121, 12121);
                        }

                        if (health == 0 && player_2 == 0) {
                            gameover = true;
                        }
                        else
                        {
                            Player.setPosition(960, 850);
                            Shield.setPosition(Player.getPosition().x - 18, Player.getPosition().y - 25);
                            shield_on = 1;

                        }

                    }
                    else
                        Timer--;

                }

            }

        }

        if (Player2ship.getGlobalBounds().intersects(meteor[i].getGlobalBounds()) && shield_on2 == false) {
            health3 -= 1;
            if (soundeffectON)
            {
                exploding.play();
            }
            hp2.setString(to_string(health3));
            if (health3 < health4) {

                player2alive = false;

            }
            if (player2alive == false) {

                if (expbool2 == 0) {
                    expbool2 = 1;
                    explosion2.setPosition(Player2ship.getPosition());
                }
                Player2ship.setPosition(6000, 6000);
                explosion2.setTextureRect(IntRect(96.6 * exp_x2, 5 + (90.6 * exp_y2), 96.6, 90.6));
                exp_x2++;
                if (exp_x2 == 7 && exp_y2 < 3) {
                    exp_y2++;
                    exp_x2 = 0;
                }
                if (exp_y2 == 2 && exp_x2 == 5) {
                    exp_y2 = 0;
                    exp_x2 = 0;
                    health4 = health3;
                    expbool2 = 0;

                    if (Timer2 <= 0) {
                        player2alive = true;

                        Timer2 = 2;


                        if (health3 == 0) {
                            player_2 = 0;
                        }
                        else
                        {
                            Player2ship.setPosition(960, 850);
                            Shield2.setPosition(Player2ship.getPosition().x - 18, Player2ship.getPosition().y - 25);
                            shield_on2 = 1;
                        }

                    }
                    else
                        Timer2--;

                }

            }
        }


    }
}

//increasing score
void scorecalc() {
    for (int i = 0; i < bullet.numberofbullets; i++) {
        for (int j = 0; j < 8; j++) {
            for (int z = 0; z < 4; z++) {

                if (Bullets[i].getGlobalBounds().intersects(Chicken[j][z].getGlobalBounds()))
                {
                    if (chicken.HP[j][z] > 0)
                    {
                        Bullets[i].setPosition(-10000, -10000);
                        chicken.HP[j][z] = chicken.HP[j][z] - (powerlvls * 0.5) - bullet.bulletdamage;
                    }
                    if (chicken.HP[j][z] <= 0)
                    {
                        if (coopon)
                        {
                            randomizer = 0;
                        }
                        else
                        {
                            randomizer = 1 + rand() % 160;
                        }

                        if (randomizer == 1 || randomizer == 2)
                        {
                            iongift.setPosition(Chicken[j][z].getPosition().x, Chicken[j][z].getPosition().y);

                        }
                        if (randomizer == 3)
                        {

                            crystalgift.setPosition(Chicken[j][z].getPosition().x, Chicken[j][z].getPosition().y);

                        }
                        fog[i].setPosition(Chicken[j][z].getPosition() - Vector2f(-50, -20));
                        chicken_legs[j][z].setPosition(Chicken[j][z].getPosition().x, Chicken[j][z].getPosition().y);
                        Chicken[j][z].setPosition(10000, 10000);
                        Bullets[i].setPosition(-10000, -10000);
                        cnt += 1000;
                        chickendead[j][z] = 1;
                        score.setString(to_string(cnt));
                        missileScoreCount += 1000;
                    }

                    if (missileScoreCount == 70000)
                    {
                        missileScoreCount = 0;
                        rockets += 1;
                        rocket.setString(to_string(rockets));
                        rocket2.setString(to_string(rockets));
                    }
                    if (soundeffectON)
                    {
                        chickenhurt[currentchickensfx].play();
                        currentchickensfx++;
                        if (currentchickensfx == 2)
                        {
                            currentchickensfx = 0;
                        }
                    }


                }
                if (checkbullet == 'b')
                {
                    bullet.bulletdamage = 2;
                }
                else if (checkbullet == 'r')
                {
                    bullet.bulletdamage = 1;
                }

                if (iongift.getGlobalBounds().intersects(Player.getGlobalBounds()))
                {
                    if (soundeffectON)
                    {
                        upgradesound.play();
                    }
                    iongift.setPosition(4000, -100);
                    for (int i = 0; i < 50; i++)
                    {
                        Bullets[i].setTexture(bulletImage);
                    }
                    if (checkbullet == 'b')
                    {
                        doublebullets = 0;
                        checkbullet = 'r';
                    }
                    else if (doublebullets < 2)
                        doublebullets++;

                }
                if (crystalgift.getGlobalBounds().intersects(Player.getGlobalBounds()))
                {
                    if (soundeffectON)
                    {
                        upgradesound.play();
                    }
                    crystalgift.setPosition(4000, -100);
                    for (int i = 0; i < 50; i++)
                    {
                        Bullets[i].setTexture(crystaltear);
                    }
                    if (checkbullet == 'r')
                    {
                        doublebullets = 0;
                        checkbullet = 'b';
                    }
                    else if (doublebullets < 2)
                        doublebullets++;
                }




                if (chicken_legs[j][z].getGlobalBounds().intersects(Player.getGlobalBounds()))
                {
                    chicken_legs[j][z].setPosition(4000, -100);
                    cnt += 100;
                    score.setString(to_string(cnt));
                    score2.setString(to_string(cnt));
                    foodcnt += 1;
                    foodscore.setString(to_string(foodcnt));
                    foodscore2.setString(to_string(foodcnt));
                    if (soundeffectON)
                    {
                        eating.play();
                    }

                }
                if (coopon)
                {
                    if (chicken_legs[j][z].getGlobalBounds().intersects(Player2ship.getGlobalBounds()))
                    {
                        chicken_legs[j][z].setPosition(4000, -100);
                        foodcnt += 1;
                        foodscore.setString(to_string(foodcnt));
                        foodscore2.setString(to_string(foodcnt));
                        if (soundeffectON)
                        {
                            eating.play();
                        }
                    }
                }
            }
        }
    }
}
//Main menu 
void mainmenu()
{
    Vector2i mousepos = Mouse::getPosition(window);


    //Buttons in select mode menu
    for (int i = 0; i < 2; i++)
    {
        if (mousepos.x >= 585 + i * 400 && mousepos.x <= 935 + i * 400 && mousepos.y >= 480 && mousepos.y <= 550)
        {
            //Buttons in select mode menu on
            rectangleselectmode[i].setFillColor(Color(0, 128, 255, 40));
            rectangleselectmode[i].setOutlineColor(Color(102, 178, 255, 255));
        }
        else
        {
            //Buttons in select mode menu off
            rectangleselectmode[i].setFillColor(Color(0, 0, 255, 40));
            rectangleselectmode[i].setOutlineColor(Color(51, 153, 255, 60));
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (mousepos.x >= 50 + i * 370 && mousepos.x <= 400 + i * 370 && mousepos.y >= 25 && mousepos.y <= 95)
        {
            //ldbs buttons on
            rectangleldbs[i].setFillColor(Color(0, 128, 255, 40));
            rectangleldbs[i].setOutlineColor(Color(102, 178, 255, 255));
        }
        else
        {
            //ldbs buttons off
            rectangleldbs[i].setFillColor(Color(0, 0, 255, 40));
            rectangleldbs[i].setOutlineColor(Color(51, 153, 255, 60));
        }
    }



    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (mousepos.x >= 500 + j * 470 && mousepos.x <= 950 + j * 470 && mousepos.y >= 480 + i * 100 && mousepos.y <= 550 + i * 100)
            {
                //controls button on
                rectanglecontrols[i][j].setFillColor(Color(0, 128, 255, 40));
                rectanglecontrols[i][j].setOutlineColor(Color(102, 178, 255, 255));
            }
            else
            {
                //controls button off
                rectanglecontrols[i][j].setFillColor(Color(0, 0, 255, 40));
                rectanglecontrols[i][j].setOutlineColor(Color(51, 153, 255, 60));
            }

        }
    }

    for (int i = 0; i < 2; i++)
    {
        if (mousepos.x >= 985 && mousepos.x <= 1055 && mousepos.y >= 480 + i * 100 && mousepos.y <= 550 + i * 100)
        {
            //check boxes on
            rectanglecheck[i].setFillColor(Color(0, 128, 255, 40));
            rectanglecheck[i].setOutlineColor(Color(102, 178, 255, 255));
        }
        else
        {
            //check boxes off
            rectanglecheck[i].setFillColor(Color(0, 0, 255, 40));
            rectanglecheck[i].setOutlineColor(Color(51, 153, 255, 60));
        }
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 180 && mousepos.y <= 250)
    {
        // level1 on
        rectanglelevels[0].setFillColor(Color(0, 128, 255, 40));
        rectanglelevels[0].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // level1 off
        rectanglelevels[0].setFillColor(Color(0, 0, 255, 40));
        rectanglelevels[0].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 300 && mousepos.y <= 370)
    {
        // level2 on
        rectanglelevels[1].setFillColor(Color(0, 128, 255, 40));
        rectanglelevels[1].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // level2 off
        rectanglelevels[1].setFillColor(Color(0, 0, 255, 40));
        rectanglelevels[1].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 420 && mousepos.y <= 490)
    {
        // level3 on
        rectanglelevels[2].setFillColor(Color(0, 128, 255, 40));
        rectanglelevels[2].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // level3 off
        rectanglelevels[2].setFillColor(Color(0, 0, 255, 40));
        rectanglelevels[2].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 540 && mousepos.y <= 610)
    {
        // level4 on
        rectanglelevels[3].setFillColor(Color(0, 128, 255, 40));
        rectanglelevels[3].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // level4 off
        rectanglelevels[3].setFillColor(Color(0, 0, 255, 40));
        rectanglelevels[3].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 660 && mousepos.y <= 730)
    {
        // level5 on
        rectanglelevels[4].setFillColor(Color(0, 128, 255, 40));
        rectanglelevels[4].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // level5 off
        rectanglelevels[4].setFillColor(Color(0, 0, 255, 40));
        rectanglelevels[4].setOutlineColor(Color(51, 153, 255, 60));
    }

    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550)
    {
        // controls on 
        rectangleoption[0].setFillColor(Color(0, 128, 255, 40));
        rectangleoption[0].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // controls off
        rectangleoption[0].setFillColor(Color(0, 0, 255, 40));
        rectangleoption[0].setOutlineColor(Color(51, 153, 255, 60));
    }

    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 580 && mousepos.y <= 650)
    {
        // sound on 
        rectangleoption[1].setFillColor(Color(0, 128, 255, 40));
        rectangleoption[1].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // sound off
        rectangleoption[1].setFillColor(Color(0, 0, 255, 40));
        rectangleoption[1].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550)
    {
        // play on 
        rectanglemainmenu[0].setFillColor(Color(0, 128, 255, 40));
        rectanglemainmenu[0].setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // play off
        rectanglemainmenu[0].setFillColor(Color(0, 0, 255, 40));
        rectanglemainmenu[0].setOutlineColor(Color(51, 153, 255, 60));
    }
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550)
    {
        // continue on 
        rectanglecont.setFillColor(Color(0, 128, 255, 40));
        rectanglecont.setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        // continue off
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
    if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 880 && mousepos.y <= 950)
    {
        // return on
        rectanglereturn.setFillColor(Color(0, 128, 255, 40));
        rectanglereturn.setOutlineColor(Color(102, 178, 255, 255));
    }
    else
    {
        //return off
        rectanglereturn.setFillColor(Color(0, 0, 255, 40));
        rectanglereturn.setOutlineColor(Color(51, 153, 255, 60));
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
}
//Boss   By mohamed akram , ziad khaled
void bossmove() {

    //Boss movement + animation
    bosssprite.setTextureRect(IntRect(982 * animation, 0, 982, 794));
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
    for (int i = 0; i < bullet.numberofbullets; i++)
    {
        if (Bullets[i].getGlobalBounds().intersects(bosssprite.getGlobalBounds()))
        {
            if (boss.bosshp > 0)
            {
                boss.bosshp = boss.bosshp - (powerlvls * 0.5) - bullet.bulletdamage;
            }
            if (boss.bosshp <= 0)
            {
                bosssprite.setPosition(10000, 10000);
                cnt += 5000;
                score.setString(to_string(cnt));
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




}
void reset()
{
    eggvar = 501;
    chicken.chicken_healthvar = 1;
    if (soundeffectON)
    {
        for (int i = 0; i < 3; i++)
        {
            shoot1[i].stop();
        }
        for (int i = 0; i < 2; i++)
        {
            chickenhurt[i].stop();
            eggshoot[i].stop();
        }
        rocketshoot.stop();
        exploding.stop();
        eating.stop();
        upgradesound.stop();
    }
    shipfire.setRotation(0);
    shipfire.setRotation(0);
    crystalgift.setPosition(-10000, -10000);
    iongift.setPosition(-10000, -10000);
    Player.setPosition(900, 850);
    Player2ship.setPosition(1000, 850);
    coopon = false;
    validname = false;
    view1.setSize(sf::Vector2f(1920.f, 1080.f));
    doublebullets = 0;
    checkbullet = 'r';
    for (int i = 0; i < 50; i++)
    {
        Bullets[i].setTexture(bulletImage);
        Bullets[i].setPosition(-10000, -10000);
        spark[i].setPosition(100000, 100000);
        fog[i].setPosition(100000, 100000);
    }
    randomizer = 0;
    chick = 0;
    chickeninitialpos = 0;
    cnt = 0;
    foodcnt = 0;
    foodscore.setString(to_string(foodcnt));
    foodscore2.setString(to_string(foodcnt));
    health = 3;
    hp.setString(to_string(health));
    health2 = 3;
    health3 = 3;
    hp2.setString(to_string(health3));
    health4 = 3;
    powerlvls = 0;
    powerlvl2.setString(to_string(powerlvls));
    powerlvl.setString(to_string(powerlvls));
    rockets = 0;
    rocket.setString(to_string(rockets));
    rocket2.setString(to_string(rockets));
    missileScoreCount = 0;
    Timer = 2;
    Timer2 = 2;
    cnt = 0;
    score.setString(to_string(cnt));
    boss.bosshp = 50 + (bosslvl * 10);
    boss.eggcooldownvar = 301;
    tmp = 100;
    meteorx = 0;
    meteoralive = 0;
    aliveboss = 1;
    player_2 = 1;
    powerlvls = 0;
    playeralive = true;
    player2alive = true;
    shield_on = false;
    shield_on2 = false;
    explosion.setPosition(10000, 10000);
    explosion2.setPosition(10000, 10000);
    exp_y = 0;
    exp_x = 0;
    exp_y2 = 0;
    exp_x2 = 0;
    rectangle3.setPosition(770, 400);
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
    prevwave = '1';
    wave1second.setString("Wave " + to_string(prevwave - 48));
    Wave2 = false, Wave3 = false, Wave4 = false, Wave5 = false, Wave1 = true;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            eggyolk[i][j].setPosition(10000, 10000);
            chickendead[i][j] = 0;
            Eggs[i][j].setPosition(11112, 11112);
            chicken_legs[i][j].setPosition(-10000, -10000);
        }
    }
    bosssprite.setPosition(Vector2f(200, 200));
    x = 0;
}

void lvldiff()
{
    if (lvl == '1')
    {
        bosslvl = 1;
        chicken.chicken_health = 1;
        chicken.speed = 4;
        boss.bosshp = 50;
        boss.bossspeed = 5;
        meteors.meteorspeed = 5;
    }
    if (lvl == '2')
    {
        bosslvl = 2;
        chicken.chicken_health = 2;
        chicken.speed = 4;
        boss.bosshp = 60;
        boss.bossspeed = 6;
        meteors.meteorspeed = 10;
    }
    if (lvl == '3')
    {
        bosslvl = 3;
        chicken.chicken_health = 3;
        chicken.speed = 3.5;
        boss.bosshp = 90;
        boss.bossspeed = 7;
        meteors.meteorspeed = 11;
    }
    if (lvl == '4')
    {
        bosslvl = 4;
        chicken.chicken_health = 4;
        chicken.speed = 3.2;
        boss.bosshp = 120;
        boss.bossspeed = 9;
        meteors.meteorspeed = 12;
    }
    if (lvl == '5')
    {
        bosslvl = 5;
        chicken.chicken_health = 5;
        chicken.speed = 3;
        boss.bosshp = 200;
        boss.bossspeed = 10;
        meteors.meteorspeed = 13.5;
    }
}

int main()
{
    //variable for game pages
    long long page = 0;
    
    //sound effect variables
    int temptest = 0, temptest2 = 0, temptest3 = 0;

    //variables for button delays
    int checkdelay = 0;
    int delay = 0;
    int backdelay = 0;
    Clock c4;

    window.setMouseCursorVisible(false); // Hide cursor  
    View fixed = window.getView(); // Create a fixed view  

    // Load image and create sprite
    
    fork.loadFromFile("Fork.png");  
    Sprite sprite(fork);   
    sprite.setScale(1.4, 1); 
    // add functions
    cnt = 0;
    boss.eggcooldownvar = 301;
    IngameImages();
    
    MenuMusic.play();
beginning: {};
    
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
           
            if (page == 10)
            {
                
                if (event.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::Enter) && Name.size()<=20) {

                    Name += static_cast<char>(event.text.unicode);

                }
                if (Keyboard::isKeyPressed(Keyboard::BackSpace) && Name.size() > 0) {
                    Name.resize(Name.size() - 1);
                }
            }
            
        }
        
        //clear window
        window.clear();

        Vector2i mousepos = Mouse::getPosition(window);

        //background
        movingbackround();

        

        //draw window
        // main menu
        if (page == 0)
        {
            if (searchl == 0)
            {
                
                mapfirst.clear();
                mapsecond.clear();
                mapthird.clear();
                mapfourth.clear();
                mapfifth.clear();
                ifstream infile;
                infile.open("firstlvl.txt", ios::in);
                string line;
                while (getline(infile, line, '*'))
                {
                    long long indx = 0;
                    long long scr = 0;
                    string nm;
                    for (int i = 0; i < line.size(); i++)
                    {
                        if (line[i] == ' ')
                        {
                            indx = i;
                        }
                    }
                    for (int i = 0; i < indx; i++)
                    {
                        nm += line[i];
                    }
                    for (int i = indx + 1; i < line.size(); i++)
                    {
                        scr *= 10;
                        scr += int(line[i]) - 48;

                    }
                    for (int i = 0; i < nm.length(); i++)
                    {
                        if(nm[i]=='\n')
                            nm.erase(nm.begin() + i);
                    }
                    mapfirst[nm] = scr;

                }
                for (auto it : mapfirst)
                {
                    lvl1score.push_back({ it.second,it.first});
                }
                sort(lvl1score.begin(), lvl1score.end());
                lvl1score.erase(unique(lvl1score.begin(), lvl1score.end()), lvl1score.end());
                sort(lvl1score.begin(), lvl1score.end());
                infile.close();

                ifstream infile2;
                infile2.open("secondlvl.txt", ios::in);
                string line2;
                while (getline(infile2, line2, '*'))
                {
                    long long indx = 0;
                    long long scr = 0;
                    string nm;
                    for (int i = 0; i < line2.size(); i++)
                    {
                        if (line2[i] == ' ')
                        {
                            indx = i;
                        }
                    }
                    for (int i = 0; i < indx; i++)
                    {
                        nm += line2[i];
                    }
                    for (int i = indx + 1; i < line2.size(); i++)
                    {
                        scr *= 10;
                        scr += int(line2[i]) - 48;

                    }
                    for (int i = 0; i < nm.length(); i++)
                    {
                        if (nm[i] == '\n')
                            nm.erase(nm.begin() + i);
                    }
                    mapsecond[nm] = scr;

                }
                for (auto it : mapsecond)
                {
                    lvl2score.push_back({ it.second,it.first });
                }
                sort(lvl2score.begin(), lvl2score.end());
                lvl2score.erase(unique(lvl2score.begin(), lvl2score.end()), lvl2score.end());
                sort(lvl2score.begin(), lvl2score.end());
                infile2.close();
                ifstream infile3;
                infile3.open("thirdlvl.txt", ios::in);
                string line3;
                while (getline(infile3, line3, '*'))
                {
                    long long indx = 0;
                    long long scr = 0;
                    string nm;
                    for (int i = 0; i < line3.size(); i++)
                    {
                        if (line3[i] == ' ')
                        {
                            indx = i;
                        }
                    }
                    for (int i = 0; i < indx; i++)
                    {
                        nm += line3[i];
                    }
                    for (int i = indx + 1; i < line3.size(); i++)
                    {
                        scr *= 10;
                        scr += int(line3[i]) - 48;

                    }
                    for (int i = 0; i < nm.length(); i++)
                    {
                        if (nm[i] == '\n')
                            nm.erase(nm.begin() + i);
                    }
                    mapthird[nm] = scr;

                }
                for (auto it : mapthird)
                {
                    lvl3score.push_back({ it.second,it.first });
                }
                sort(lvl3score.begin(), lvl3score.end());
                lvl3score.erase(unique(lvl3score.begin(), lvl3score.end()), lvl3score.end());
                sort(lvl3score.begin(), lvl3score.end());
                infile3.close();
                fstream infile4;
                infile4.open("fourthlvl.txt", ios::in);
                string line4;
                while (getline(infile4, line4, '*'))
                {
                    long long indx = 0;
                    long long scr = 0;
                    string nm;
                    for (int i = 0; i < line4.size(); i++)
                    {
                        if (line4[i] == ' ')
                        {
                            indx = i;
                        }
                    }
                    for (int i = 0; i < indx; i++)
                    {
                        nm += line4[i];
                    }
                    for (int i = indx + 1; i < line4.size(); i++)
                    {
                        scr *= 10;
                        scr += int(line4[i]) - 48;

                    }
                    for (int i = 0; i < nm.length(); i++)
                    {
                        if (nm[i] == '\n')
                            nm.erase(nm.begin() + i);
                    }
                    mapfourth[nm] = scr;

                }
                for (auto it : mapfourth)
                {
                    lvl4score.push_back({ it.second,it.first });
                }
                sort(lvl4score.begin(), lvl4score.end());
                lvl4score.erase(unique(lvl4score.begin(), lvl4score.end()), lvl4score.end());
                sort(lvl4score.begin(), lvl4score.end());
                infile4.close();
                fstream infile5;
                infile5.open("fifthlvl.txt", ios::in);
                string line5;
                while (getline(infile5, line5, '*'))
                {
                    long long indx = 0;
                    long long scr = 0;
                    string nm;
                    for (int i = 0; i < line5.size(); i++)
                    {
                        if (line5[i] == ' ')
                        {
                            indx = i;
                        }
                    }
                    for (int i = 0; i < indx; i++)
                    {
                        nm += line5[i];
                    }
                    for (int i = indx + 1; i < line5.size(); i++)
                    {
                        scr *= 10;
                        scr += int(line5[i]) - 48;

                    }
                    for (int i = 0; i < nm.length(); i++)
                    {
                        if (nm[i] == '\n')
                            nm.erase(nm.begin() + i);
                    }
                    mapfifth[nm] = scr;

                }
                for (auto it : mapfifth)
                {
                    lvl5score.push_back({ it.second,it.first });
                }
                sort(lvl5score.begin(), lvl5score.end());
                lvl5score.erase(unique(lvl5score.begin(), lvl5score.end()), lvl5score.end());
                sort(lvl5score.begin(), lvl5score.end());
                infile5.close();
                searchl++;
            }
            reset();
            backgroundspeed = 2;
            modeselectdelay = 0;
            delay = 0;
            frommenu = true;
            window.draw(menuchicken);
            window.draw(Logo);
            mainmenu();
            window.draw(play);
            window.draw(Options);
            window.draw(leadernameboard);
            window.draw(Credits);
            window.draw(Quit);
            window.draw(sprite);
            /*window.draw(topborder);
            window.draw(bottomborder);
            window.draw(leftborder);
            window.draw(rightborder);*/
            bouncingchicken();
            
            
            
            for (int i = 0; i < 5; i++)
            {
                window.draw(rectanglemainmenu[i]);
            }

            if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550 )
            {
                if (soundeffectON)
                    MenuClick.play();
                
                c4.restart();
                page = 1;
                goto pagecode;
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 580 && mousepos.y <= 650 )
            {
                if (soundeffectON)
                    MenuClick.play();
                page = 2;
                goto pagecode;
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 680 && mousepos.y <= 750)
            {
                if (soundeffectON)
                    MenuClick.play();
                page = 3;
                goto pagecode;
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 780 && mousepos.y <= 850 )
            {
                if (soundeffectON)
                    MenuClick.play();
                page = 4;
                goto pagecode;
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 880 && mousepos.y <= 950 )
            {
                window.close();
            }
        }
    pagecode: {};
        // select level page ==1;
        if (page == 1)
        {
            reset();
            backgroundspeed = 2;
            if (temptest == 1)
            {
                if (soundeffectON)
                    MenuClick.play();
                temptest = 0;
            }
            modeselectdelay = 0;
            backdelay++;
            delay = 0;
            checkdelay = 0;
            mainmenu();
            //back
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left) && backdelay>=5 )
            {
                if (soundeffectON)
                    MenuClick.play();
                backdelay = 0;
                    page = 0;
            }
            
            window.draw(rectangleback);
            window.draw(back);
           
            for (int i = 0; i < 5; i++)
            {
                window.draw(rectanglelevels[i]);
                window.draw(levels[i]);
            }
            //levels
            if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 180 && mousepos.y <= 250 && Mouse::isButtonPressed(Mouse::Left) && c4.getElapsedTime().asSeconds() >= 0.2)
            {
                if (soundeffectON)
                    MenuClick.play();
                lvl = '1';
                c4.restart();
                page = 9;
 
            }
            if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 301 && mousepos.y <= 367 && Mouse::isButtonPressed(Mouse::Left) && c4.getElapsedTime().asSeconds() >= 0.2)
            {
                if (soundeffectON)
                    MenuClick.play();
                lvl = '2';
                c4.restart();
                page = 9;

            }
            if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 421 && mousepos.y <= 482 && Mouse::isButtonPressed(Mouse::Left) && c4.getElapsedTime().asSeconds() >= 0.2)
            {
                if (soundeffectON)
                    MenuClick.play();
                lvl = '3';
                c4.restart();
                page = 9;

            }
            if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 541 && mousepos.y <= 606 && Mouse::isButtonPressed(Mouse::Left) && c4.getElapsedTime().asSeconds() >= 0.2)
            {
                if (soundeffectON)
                    MenuClick.play();
                lvl = '4';
                c4.restart();
                page = 9;

            }
            if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 662 && mousepos.y <= 727 && Mouse::isButtonPressed(Mouse::Left) && c4.getElapsedTime().asSeconds() >= 0.2)
            {
                if (soundeffectON)
                    MenuClick.play();
                lvl = '5';
                c4.restart();
                page = 9;

            }
            window.draw(sprite);
        }
        // options page ==2
        if (page == 2)
        {
            backgroundspeed = 2;
            // back
            modeselectdelay = 0;
            backdelay++;
            delay++;
            checkdelay = 0;
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left) && backdelay >= 5)
            {
                if (soundeffectON)
                    MenuClick.play();
                backdelay = 0;
                if (frommenu)
                    page = 0;
                else
                    page = 5;
            }
            mainmenu();

            window.draw(Logo);
            window.draw(Option);
            window.draw(rectangleback);
            for (int i = 0; i < 2; i++)
                window.draw(rectangleoption[i]);
            window.draw(controls);
            window.draw(sound);
            window.draw(back);
            window.draw(sprite);
            if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550 && delay >= 5)
            {
                if (soundeffectON)
                    MenuClick.play();
                delay = 0;
                page = 7;
            }
            if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 580 && mousepos.y <= 650 && delay >= 5)
            {
                if (soundeffectON)
                    MenuClick.play();
                delay = 0;
                page = 8;
            }
        }
        // hall of fame page ==3
        if (page == 3)
        {

            backgroundspeed = 2;

            temptest3++;
            modeselectdelay = 0;
            backdelay = 0;
            checkdelay = 0;
            delay = 0;
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left))
            {
                if (soundeffectON)
                    MenuClick.play();
                if (frommenu)
                    page = 0;
                else
                    page = 5;
            }
            mainmenu();
           

            for (int i = 0; i < 5; i++)
            {
                if (i == 0 && ldbcheck[i] == 1)
                {             
                    for (int a = lvl1score.size() - 1, x = 0; x < 5; a--, x++)
                    {
                        if (lvl1score[a].second != " ")
                        {
                            leadername[x].setString(lvl1score[a].second);        
                            leaderscore[x].setString(to_string(lvl1score[a].first));
                        }
                    }
                }
                if (i == 1 && ldbcheck[i] == 1)
                {
                    for (int a = lvl2score.size() - 1, x = 0; x < 5; a--, x++)
                    {
                            leadername[x].setString(lvl2score[a].second);        
                            leaderscore[x].setString(to_string(lvl2score[a].first));
                    }
                }
                if (i == 2 && ldbcheck[i] == 1)
                {
                    for (int a = lvl3score.size() - 1, x = 0; x < 5; a--, x++)
                    {
                            leadername[x].setString(lvl3score[a].second);     
                            leaderscore[x].setString(to_string(lvl3score[a].first));
                    }
                }
                if (i == 3 && ldbcheck[i] == 1)
                {
                    for (int a = lvl4score.size() - 1, x = 0; x < 5; a--, x++)
                    {
                        leadername[x].setString(lvl4score[a].second);
                        leaderscore[x].setString(to_string(lvl4score[a].first));
                    }
                }
                if (i == 4 && ldbcheck[i] == 1)
                {
                    for (int a = lvl5score.size() - 1, x = 0; x < 5; a--, x++)
                    {
                        leadername[x].setString(lvl5score[a].second);
                        leaderscore[x].setString(to_string(lvl5score[a].first));
                    }
                }
                if (mousepos.x >= 50 + i * 370 && mousepos.x <= 400 + i * 370 && mousepos.y >= 25 && mousepos.y <= 95 && Mouse::isButtonPressed(Mouse::Left))
                {
                    ldbcheck[lastlevel - 1] = 0;
                    ldbcheck[i] = 1;
                    lastlevel = i + 1;
                    if (soundeffectON && temptest3>=5)
                    {
                        MenuClick.play();
                        temptest3 = 0;
                    }
                }
                if (ldbcheck[i] == 1)
                {
                    rectangleldbs[i].setFillColor(Color(0, 128, 255, 40));
                    rectangleldbs[i].setOutlineColor(Color(102, 178, 255, 255));
                }
                else
                {
                    
                    rectangleldbs[i].setFillColor(Color(0, 0, 255, 40));
                    rectangleldbs[i].setOutlineColor(Color(51, 153, 255, 60));
                }
            }
            for (int i = 0; i < 5; i++)
            {
                window.draw(rectangleldbs[i]);
            }
            for (int i = 0; i < 5; i++)
            {
                window.draw(ldb[i]);
            }
            window.draw(rectangleback);
            window.draw(back);
            window.draw(sprite);  
            window.draw(nametext);
            window.draw(numbertext);
            for (int i = 0; i < 5; i++) 
            {
                window.draw(leaderscore[i]);
                window.draw(leadername[i]);
            }
        }
        // credits page ==4
        if (page == 4)
        {
            backgroundspeed = 2;
            modeselectdelay = 0;
            backdelay = 0;
            checkdelay = 0;
            delay = 0;
            //credit positioning
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left))
            {
                if (soundeffectON)
                    MenuClick.play();
               if (frommenu)
               {
                   page = 0;

                   
                   for (int i = 0; i < 7;i++)
                   {
                       Cred[i].setPosition(900, 1400 + i * 150);
                       curscale[i] = 1;
                   }        
               }
               
               else
               {
                   if (soundeffectON)
                       MenuClick.play();
                   page = 5;
                   for (int i = 0; i < 7; i++)
                   {
                       Cred[i].setPosition(900, 1400 + i * 150);
                       curscale[i] = 1;
                   }

               }
            }
            mainmenu();
            
            window.draw(rectangleback);
            window.draw(back);

            //credit scrolling
            for(int i =0 ; i < 7;i++)
                Cred[i].move(0, -7);

            //credit scaling
            for (int i = 0; i < 7; i++)
            {
                if (curscale[i] > 0 && Cred[i].getPosition().y < 540)
                {
                    curscale[i] -= 0.01;
                }
            }
            
            for (int i = 0; i < 7; i++)
            {

                Cred[i].setScale(curscale[i], curscale[i]);
                window.draw(Cred[i]);
            }
            window.draw(sprite);  
            if (Cred[6].getScale().x <= 0.15)
            {
                if (frommenu)
                {
                    page = 0;
                    for (int i = 0; i < 7; i++)
                    {
                        Cred[i].setPosition(900, 1400 + i * 150);
                        curscale[i] = 1;
                    }
                }
                else
                {
                    page = 5;
                    for (int i = 0; i < 7; i++)
                    {
                        Cred[i].setPosition(900, 1400 + i * 150);
                        curscale[i] = 1;
                    }
                }
            }
        }
        //pause menu
        if (page == 5)
        {
            backgroundspeed = 2;
            modeselectdelay = 0;
            backdelay = 0;
            checkdelay = 0;
            delay = 0;
            mainmenu();
          if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550)
          {
              if (soundeffectON)
                  MenuClick.play();
              pausecooldown = 0;
              page = 6;
              goto pagecode;
          }
          else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 580 && mousepos.y <= 650)
          {
              if (soundeffectON)
                  MenuClick.play();
             page = 2;
             goto pagecode;
          }
          else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 680 && mousepos.y <= 750)
          {
              if (soundeffectON)
                  MenuClick.play();
             page = 3;

             

             goto pagecode;
          }
          else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 780 && mousepos.y <= 850)
          {
              if (soundeffectON)
                  MenuClick.play();
              page = 4;
              goto pagecode;
          }
          else if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 880 && mousepos.y <= 950)
          {
              gameover = false;
              
              temptest = 1;
              page = 1;
              IngameMusicPlaying = false;
              MainMusicPlaying = true;
              
              if (musicON)
              {
                  ingamemusic.stop();
                  MenuMusic.play();
              }
              

              coopon = false;
              reset();
              goto beginning;

          }
            
            window.draw(Logo);
            for (int i = 1; i < 4; i++)
            {
                window.draw(rectanglemainmenu[i]);
            }
            window.draw(rectanglecont);
            window.draw(rectanglereturn);
            window.draw(cont); 
            window.draw(Options); 
            window.draw(leadernameboard); 
            window.draw(Credits); 
            window.draw(ret); 
            window.draw(sprite); 
        } 
        
        // ingame
        if (page == 6)
        {
            //drawing ingame bg
            for (int i = 0; i < 2; i++)
            {
                window.draw(_GameBackground[i]);
            }
            if (temptest2 == 1)
            {
                if (soundeffectON)
                    MenuClick.play();
                temptest2 = 0;
            }
            modeselectdelay = 0;
            backdelay = 0;
            delay = 0;
            checkdelay = 0;
            frommenu = false;
            
            if (Wave1 == true)
            {
                chicken.chicken_healthvar = 1;
                prevwave = '1';
                alivechicken = 0;
                if (clock4.getElapsedTime().asSeconds() >= 9)
                {
                    backgroundspeed = 3;
                    foodmovespeed = 10;
                    PlayerShooting();
                    rocketshooting();
                    ChickenMove();
                    eggmovement();
                    spark_fog();
                    scorecalc();
                    FoodMovment();
                    
                    window.draw(rectangle1);
                    window.draw(rectangle2);

                    if (gameover == true) {
                        searchl = 0;
                        if(lvl=='1')
                        {
                            ofstream offile;
                            offile.open("firstlvl.txt",ios::app);
                            offile << Name <<" "<< cnt << "*" << endl;
                            offile.close();
                            
                        }
                        if (lvl == '2')
                        {
                            ofstream offile;
                            offile.open("secondlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '3')
                        {
                            ofstream offile;
                            offile.open("thirdlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '4')
                        {
                            ofstream offile;
                            offile.open("fourthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '5')
                        {
                            ofstream offile;
                            offile.open("fifthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        gameover = false;
                        temptest = 1;
                        page = 1;
                        reset();
                        goto beginning;

                    }


                    for (int j = 0; j < 4; j++)
                    {
                        for (int i = 0; i < 8; i++)
                        {

                            window.draw(eggyolk[i][j]);
                            window.draw(Chicken[i][j]);
                            window.draw(Eggs[i][j]);
                            window.draw(chicken_legs[i][j]);

                        }
                    }
                  

                    window.draw(crystalgift); 
                    window.draw(iongift);
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    window.draw(explosion);
                    for (int i = 0; i < bullet.numberofbullets; i++)
                    {
                        window.draw(Bullets[i]);
                        if (Bullets[i].getGlobalBounds().intersects(Gamebar.getGlobalBounds()))
                        {
                            Bullets[i].setPosition(4000, 4000);
                        }
                    }
                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (chickendead[i][j] == 0)
                                alivechicken++;
                        }
                    }
                    camerashake();
                    if (alivechicken == 0)
                    {
                        Wave1 = false;
                        Wave2 = true;
                        clock4.restart();
                        clock3.restart();
                        for (int i = 0; i < bullet.numberofbullets; i++)
                        {
                            Bullets[i].setPosition(9000, 9000);
                                spark[i].setPosition(9000, 9000);
                                fog[i].setPosition(9000, 9000);
                        }
                    }
                    shield_move();
                    window.draw(Shield);
                    window.draw(Shield2);


                    //drawing missile
                    window.draw(missile);
                    for (int i = 0; i < 50; i++) {
                        window.draw(spark[i]);
                        window.draw(fog[i]);
                    }
               
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        page = 5;
                        shipin.stop();
                    }
                }
                else
                {
                   
                    backgroundspeed = 20;
                    foodmovespeed = 20;
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                   
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    if (clock3.getElapsedTime().asSeconds() <= 8)
                    {
                        if (clock3.getElapsedTime().asSeconds() <= 5)
                        {
                            window.draw(wave1second);
                        }
                        window.draw(wave1first);
                    }
                }
            }
            else if (Wave2 == true)
            {
                powerlvls = 1;
                meteoralive = 0;
                powerlvl2.setString(to_string(powerlvls));
                powerlvl.setString(to_string(powerlvls));
                wave1second.setString("Wave " + to_string(prevwave - 48));
                if (prevwave == '1')
                {
                    x = 0;
                    clock3.restart();
                    clock4.restart();
                    for (int i = 0; i < 8; i++)
                    {
                        for (int a = 0; a < 4; a++)
                        {
                            Chicken[i][a].setPosition(10000, 10000);
                            eggyolk[i][a].setPosition(10000, 10000);
                            Eggs[i][a].setPosition(10000, 10000);
                            chickendead[i][a] = 0;
                            chicken.chicken_healthvar = 3;
                        }
                    }
                    chickeninitialpos = 0;
                    rectangle3.setPosition(770, 400);
                }
                prevwave = '2';
                if (clock4.getElapsedTime().asSeconds() >= 9)
                {
                    backgroundspeed = 3;
                    foodmovespeed = 10;
                    meteormove();
                    PlayerShooting();
                    rocketshooting();
                    spark_fog();
                    scorecalc();
                    FoodMovment();
                    
                    window.draw(rectangle1);
                    window.draw(rectangle2);

                    if (gameover == true) {
                        searchl = 0;
                        if (lvl == '1')
                        {
                            ofstream offile;
                            offile.open("firstlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();

                        }
                        if (lvl == '2')
                        {
                            ofstream offile;
                            offile.open("secondlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '3')
                        {
                            ofstream offile;
                            offile.open("thirdlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '4')
                        {
                            ofstream offile;
                            offile.open("fourthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '5')
                        {
                            ofstream offile;
                            offile.open("fifthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        gameover = false;
                        temptest = 1;
                        page = 1;
                        reset();
                        goto beginning;

                    }
                    for (int i = 0; i <= 39; i++)
                    {
                        window.draw(meteor[i]);
                    }
                    for (int i = 0; i < 40; i++)
                    {
                        if (meteor[i].getPosition().y < 1100 && meteor[i].getPosition().x < 1920)
                        {
                            meteoralive++;
                        }
                    }
                    camerashake();
                    if (meteoralive == 0)
                    {
                        Wave2 = false;
                        Wave3 = true;

                        clock4.restart();
                        clock3.restart();
                        for (int i = 0; i < bullet.numberofbullets; i++)
                        {
                            Bullets[i].setPosition(9000, 9000);

                                spark[i].setPosition(9000, 9000);
                                fog[i].setPosition(9000, 9000);

                        }

                    }
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);                  
                    window.draw(explosion);
                    
                    for (int i = 0; i < bullet.numberofbullets; i++)
                    {
                        window.draw(Bullets[i]);
                        if (Bullets[i].getGlobalBounds().intersects(Gamebar.getGlobalBounds()))
                        {
                            Bullets[i].setPosition(4000, 4000);
                        }
                    }
                    shield_move();
                    window.draw(Shield);
                    window.draw(Shield2);
                    //drawing missile
                    window.draw(missile);
                    for (int i = 0; i < 50; i++) {
                        window.draw(spark[i]);
                    window.draw(fog[i]);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        page = 5;
                        shipin.stop();
                    }
                }
                else
                {
                    backgroundspeed = 20;
                    foodmovespeed = 20;
                    for (int j = 0; j < 4; j++)
                    {
                        for (int i = 0; i < 8; i++)
                        {

                            window.draw(eggyolk[i][j]);
                            window.draw(Eggs[i][j]);
                            window.draw(chicken_legs[i][j]);

                        }
                    }
                    eggmovement();
                    scorecalc();
                    FoodMovment();
                    window.draw(crystalgift);
                    window.draw(iongift);
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);

                    if (clock3.getElapsedTime().asSeconds() <= 8)
                    {
                        if (clock3.getElapsedTime().asSeconds() <= 5)
                        {
                            window.draw(endofwave1);
                        }
                        window.draw(wave1second);
                    }
                }

            }
            else if (Wave3 == true)
            {
                chicken.chicken_healthvar = 3;
                powerlvls = 2;
                powerlvl2.setString(to_string(powerlvls));
                powerlvl.setString(to_string(powerlvls));
                alivechicken = 0;
                wave1second.setString("Wave " + to_string(prevwave - 48));
                if (prevwave == '2')
                {
                    chick = 0;
                    clock3.restart();
                    clock4.restart();
                    meteorx = 0;
                    for (int i = 0; i < 40; i++)
                    {
                        meteor[i].setPosition(10000, 10000);
                    }
                }
                prevwave = '3';

                if (clock4.getElapsedTime().asSeconds() >= 9)
                {
                    backgroundspeed = 3;
                    foodmovespeed = 10;
                    PlayerShooting();
                    rocketshooting();
                    ChickenMove();
                    eggmovement();
                    spark_fog();
                    scorecalc();
                    FoodMovment();
                    
                    window.draw(rectangle1);
                    window.draw(rectangle2);

                    if (gameover == true) {
                        searchl = 0;
                        if (lvl == '1')
                        {
                            ofstream offile;
                            offile.open("firstlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();

                        }
                        if (lvl == '2')
                        {
                            ofstream offile;
                            offile.open("secondlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '3')
                        {
                            ofstream offile;
                            offile.open("thirdlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '4')
                        {
                            ofstream offile;
                            offile.open("fourthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '5')
                        {
                            ofstream offile;
                            offile.open("fifthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        gameover = false;
                        temptest = 1;
                        page = 1;
                        reset();
                        goto beginning;

                    }


                    for (int j = 0; j < 4; j++)
                    {

                        for (int i = 0; i < 8; i++)
                        {

                            window.draw(eggyolk[i][j]);
                            window.draw(Chicken[i][j]);
                            window.draw(Eggs[i][j]);
                            window.draw(chicken_legs[i][j]);
                        }
                    }
                    window.draw(iongift);
                    window.draw(crystalgift);
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    window.draw(explosion);
                    for (int i = 0; i < bullet.numberofbullets; i++)
                    {
                        window.draw(Bullets[i]);
                        if (Bullets[i].getGlobalBounds().intersects(Gamebar.getGlobalBounds()))
                        {
                            Bullets[i].setPosition(4000, 4000);
                        }
                    }

                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (chickendead[i][j] == 0)
                                alivechicken++;
                        }
                    }
                    camerashake();
                    if (alivechicken == 0)
                    {
                        Wave3 = false;
                        Wave4 = true;
                        clock4.restart();
                        clock3.restart();
                        for (int i = 0; i < bullet.numberofbullets; i++)
                        {
                            Bullets[i].setPosition(9000, 9000);

                                spark[i].setPosition(9000, 9000);
                                fog[i].setPosition(9000, 9000);

                        }
                        for (int i = 0; i < 8; i++)
                        {
                            for (int a = 0; a < 4; a++)
                            {
                                Chicken[i][a].setPosition(-2000, 2000);
                            }
                        }
                    }
                    shield_move();
                    window.draw(Shield);
                    window.draw(Shield2);
                    //drawing missile
                    window.draw(missile);
                    for (int i = 0; i < 50; i++) {
                        window.draw(spark[i]);
                    window.draw(fog[i]);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        page = 5;
                        shipin.stop();
                    }
                }
                else
                {
                    backgroundspeed = 20;
                    foodmovespeed = 20;
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                   
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    if (clock3.getElapsedTime().asSeconds() <= 8)
                    {
                        if (clock3.getElapsedTime().asSeconds() <= 5)
                        {
                            window.draw(endofwave1);
                        }
                        window.draw(wave1second);
                    }
                }
            }
            else if (Wave4 == true)
            {
                x = 0;
                chicken.chicken_healthvar = 0;
                powerlvls = 3;
                powerlvl2.setString(to_string(powerlvls));
                powerlvl.setString(to_string(powerlvls));
                meteoralive = 0;
                wave1second.setString("Wave " + to_string(prevwave - 48));
                if (prevwave == '3')
                {
                    clock3.restart();
                    clock4.restart();
                    for (int i = 0; i < 8; i++)
                    {
                        for (int a = 0; a < 4; a++)
                        {
                            Chicken[i][a].setPosition(10000, 10000);
                            eggyolk[i][a].setPosition(10000, 10000);
                            Eggs[i][a].setPosition(10000, 10000);
                            chickendead[i][a] = 0;
                        }
                    }
                    chickeninitialpos = 0;
                }
                prevwave = '4';
                if (clock4.getElapsedTime().asSeconds() >= 9)
                {
                    backgroundspeed = 3;
                    foodmovespeed = 10;
                    meteorfast();
                    PlayerShooting();
                    rocketshooting();
                    spark_fog();
                    scorecalc();
                    FoodMovment();
                    
                    window.draw(rectangle1);
                    window.draw(rectangle2);

                    if (gameover == true) {
                        searchl = 0;
                        if (lvl == '1')
                        {
                            ofstream offile;
                            offile.open("firstlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();

                        }
                        if (lvl == '2')
                        {
                            ofstream offile;
                            offile.open("secondlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '3')
                        {
                            ofstream offile;
                            offile.open("thirdlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '4')
                        {
                            ofstream offile;
                            offile.open("fourthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '5')
                        {
                            ofstream offile;
                            offile.open("fifthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        gameover = false;
                        temptest = 1;
                        page = 1;
                        reset();
                        goto beginning;

                    }
                    for (int i = 0; i <= 39; i++)
                    {
                        window.draw(meteor[i]);
                    }
                    for (int i = 0; i < 40; i++)
                    {
                        if (meteor[i].getPosition().y < 1100 && meteor[i].getPosition().x < 1920)
                        {
                            meteoralive++;
                        }
                    }
                    camerashake();
                    if (meteoralive == 0)
                    {
                        Wave4 = false;
                        Wave5 = true;

                        clock4.restart();
                        clock3.restart();
                        for (int i = 0; i < bullet.numberofbullets; i++)
                        {
                            Bullets[i].setPosition(9000, 9000);
                            
                                spark[i].setPosition(9000, 9000);
                                fog[i].setPosition(9000, 9000);
                            
                        }

                    }
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    window.draw(explosion);
                    for (int i = 0; i < bullet.numberofbullets; i++)
                    {
                        window.draw(Bullets[i]);
                        if (Bullets[i].getGlobalBounds().intersects(Gamebar.getGlobalBounds()))
                        {
                            Bullets[i].setPosition(4000, 4000);
                        }
                    }
                    shield_move();
                    window.draw(Shield);
                    window.draw(Shield2);

                    //drawing missile
                    window.draw(missile);
                    for (int i = 0; i < 50; i++) {
                        window.draw(spark[i]);
                        window.draw(fog[i]);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        page = 5;
                        shipin.stop();
                    }
                }
                else
                {
                    backgroundspeed = 20;
                    foodmovespeed = 20;
                    for (int j = 0; j < 4; j++)
                    {
                        for (int i = 0; i < 8; i++)
                        {

                            window.draw(eggyolk[i][j]);
                            window.draw(Eggs[i][j]);
                            window.draw(chicken_legs[i][j]);

                        }
                    }
                    window.draw(crystalgift);
                    window.draw(iongift);
                    eggmovement();
                    scorecalc();
                    FoodMovment();
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    if (clock3.getElapsedTime().asSeconds() <= 8)
                    {
                        if (clock3.getElapsedTime().asSeconds() <= 5)
                        {
                            window.draw(endofwave1);
                        }
                        window.draw(wave1second);
                    }
                }

            }
            else if (Wave5 == true)
            {
                powerlvls = 4;
                powerlvl2.setString(to_string(powerlvls));
                powerlvl.setString(to_string(powerlvls));
                aliveboss = 1;
                wave1second.setString("Wave " + to_string(prevwave - 48));
                if (prevwave == '4')
                {
                    boss.bosshp = 50 + (bosslvl * 10);
                    bossalive = 1;
                    clock3.restart();
                    clock4.restart();
                    meteorx = 0;
                    for (int i = 0; i < 40; i++)
                    {
                        meteor[i].setPosition(10000, 10000);
                    }
                }
                prevwave = '5';

                if (clock4.getElapsedTime().asSeconds() >= 9)
                {
                    backgroundspeed = 3;
                    foodmovespeed = 10;
                    PlayerShooting();
                    rocketshooting();
                    bossmove();
                    spark_fog();
                    scorecalc();

                    
                    window.draw(rectangle1);
                    window.draw(rectangle2);

                    if (gameover == true) {
                        searchl = 0;
                        if (lvl == '1')
                        {
                            ofstream offile;
                            offile.open("firstlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();

                        }
                        if (lvl == '2')
                        {
                            ofstream offile;
                            offile.open("secondlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '3')
                        {
                            ofstream offile;
                            offile.open("thirdlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '4')
                        {
                            ofstream offile;
                            offile.open("fourthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '5')
                        {
                            ofstream offile;
                            offile.open("fifthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        gameover = false;
                        temptest = 1;
                        page = 1;
                        reset();
                        goto beginning;

                    }


                    for (int i = 0; i < 5; i++)
                    {
                        window.draw(bossegg[i]);
                        window.draw(bossegg1[i]);
                        window.draw(bossegg2[i]);
                    }
                    window.draw(bosssprite);
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    window.draw(explosion);
                    for (int i = 0; i < bullet.numberofbullets; i++)
                    {
                        window.draw(Bullets[i]);
                        if (Bullets[i].getGlobalBounds().intersects(Gamebar.getGlobalBounds()))
                        {
                            Bullets[i].setPosition(4000, 4000);
                        }
                    }
                    for (int i = 0; i < 40; i++)
                    {
                        window.draw(meteor[i]);
                    }
                    if (boss.bosshp <= 0)
                        aliveboss = 0;
                    
                    camerashake();
                    if (aliveboss <= 0)
                    {
                        
                        searchl = 0;
                        if (lvl == '1')
                        {
                            ofstream offile;
                            offile.open("firstlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();

                        }
                        if (lvl == '2')
                        {
                            ofstream offile;
                            offile.open("secondlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '3')
                        {
                            ofstream offile;
                            offile.open("thirdlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '4')
                        {
                            ofstream offile;
                            offile.open("fourthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        if (lvl == '5')
                        {
                            ofstream offile;
                            offile.open("fifthlvl.txt", ios::app);
                            offile << Name << " " << cnt << "*" << endl;
                            offile.close();
                        }
                        view1.setSize(sf::Vector2f(1920.f, 1080.f));
                        bosssprite.setPosition(11112, 11112);
                        Wave5 = false;
                        clock4.restart();
                        clock3.restart();
                        for (int i = 0; i < bullet.numberofbullets; i++)
                        {
                            Bullets[i].setPosition(9000, 9000);
                            {
                                spark[i].setPosition(9000, 9000);
                            }
                        }
                        for (int i = 0; i < 8; i++)
                        {
                            for (int a = 0; a < 4; a++)
                            {
                                Chicken[i][a].setPosition(10000, 10000);
                            }
                        }
                        
                        IngameMusicPlaying = false;
                        if (musicON)
                        {
                            
                            ingamemusic.stop();
                        }
                        if (soundeffectON)
                        {
                            gamewin.play();
                        }
                    }
                    shield_move();
                    window.draw(Shield);
                    window.draw(Shield2);


                    //drawing missile
                    window.draw(missile);
                    for (int i = 0; i < 50; i++) {
                        window.draw(spark[i]);
                    window.draw(fog[i]);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        page = 5;
                        shipin.stop();
                        gamewin.stop();
                    }
                }
                else
                {
                    backgroundspeed = 20;
                    foodmovespeed = 20;
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    if (coopon)
                    {
                        window.draw(Bottombar2);
                        window.draw(foodscore2);
                        window.draw(hp2);
                        window.draw(rocket2);
                        window.draw(powerlvl2);
                        window.draw(explosion2);
                    }
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    if (clock3.getElapsedTime().asSeconds() <= 8)
                    {
                        if (clock3.getElapsedTime().asSeconds() <= 5)
                        {
                            window.draw(endofwave1);
                        }
                        window.draw(wave1second);
                    }
                }
            }

            else
            {
                bossmove();
                scorecalc();
                for (int i = 0; i < 5; i++)
                {
                    window.draw(bossegg[i]);
                    window.draw(bossegg1[i]);
                    window.draw(bossegg2[i]);
                }
                window.draw(health_bar);
                window.draw(Gamebar);
                window.draw(score);
                window.draw(Bottombar);
                if (coopon)
                {
                    window.draw(Bottombar2);
                    window.draw(foodscore2);
                    window.draw(hp2);
                    window.draw(rocket2);
                    window.draw(powerlvl2);
                    window.draw(explosion2);
                }
                window.draw(foodscore);
                window.draw(hp);
                window.draw(rocket);
                window.draw(powerlvl);
                if (prevwave == '4')
                {
                    clock3.restart();
                    clock4.restart();
                }
                prevwave = '5';
                if (clock3.getElapsedTime().asSeconds() <= 8)
                {
                    if (clock3.getElapsedTime().asSeconds() <= 5)
                    {
                        window.draw(congratulation);
                    }
                    window.draw(endoflevel1);
                }
                else
                {
                    MainMusicPlaying = true;
                    IngameMusicPlaying = false;
                    if (musicON)
                    {
                        MenuMusic.play();
                        ingamemusic.stop();
                    }
                    temptest = 1;
                    page = 1;
                    reset();
                    goto beginning;
                }

            }

            playerdamage();
            PlayerMove();
            
            window.draw(Player);
            window.draw(shipfire);


            if (coopon)
            {
                window.draw(Player2ship);
                window.draw(shipfire2);
            }
            else
            {
                Player2ship.setPosition(10000, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                page = 5;
                shipin.stop();
                gamewin.stop();
            }
        }

        // control
        if (page == 7)
        {
            modeselectdelay = 0;
            delay = 0;
            checkdelay = 0;
            backdelay++;
            mainmenu();
            
            window.draw(Logo);
            for (int j = 0; j < 2; j++)
            {
                for (int i = 0; i < 5; i++)
                {
                    window.draw(rectanglecontrols[i][j]);
                }
            }
            window.draw(player1);
            window.draw(player2);
            for (int i = 0; i < 2; i++)
            {
                window.draw(arrow_l[i]);
                window.draw(arrow_r[i]);
                window.draw(arrow_up[i]);
                window.draw(arrow_dw[i]);
            }
            window.draw(Up);
            window.draw(Down);
            window.draw(Right);
            window.draw(Left);
            window.draw(Fire);
            window.draw(Space);
            window.draw(A);
            window.draw(D);
            window.draw(S);
            window.draw(W);
            window.draw(Fire2);
            window.draw(Shift);
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left) &&backdelay>=5)
            {
                if(soundeffectON)
                    MenuClick.play();
                backdelay = 0;
                page = 2;
            }
            window.draw(rectangleback);
            window.draw(back);
            window.draw(sprite);
            
        }
        // sound
        if (page == 8)
        {
            modeselectdelay = 0;
            delay = 0;
            backdelay = 0;
            checkdelay++;
            mainmenu();
            
            window.draw(Logo);
            window.draw(rectangleback);
            window.draw(back);
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left))
            {
                if (soundeffectON)
                    MenuClick.play();
                page = 2;
            }
            for (int i = 0; i < 2; i++)
            {
                window.draw(rectanglecheck[i]);
            }
            window.draw(musiccheck);
            window.draw(soundeffectcheck);

            if (mousepos.x >= 985 && mousepos.x <= 1055 && mousepos.y >= 480  && mousepos.y <= 550 && Mouse::isButtonPressed(Mouse::Left) && checkdelay>=5)
            {
                
                    if (soundeffectON)
                    {
                        MenuClick.play();
                    }
                    musicON = !musicON;
                    if (musicON == false)
                    {
                        MenuMusic.stop();
                        ingamemusic.stop();
                    }
                    if (musicON && IngameMusicPlaying && MainMusicPlaying == false)
                    {
                        ingamemusic.play();
                    }
                    if (musicON && MainMusicPlaying && IngameMusicPlaying == false)
                    {
                        MenuMusic.play();
                    }
                    checkdelay = 0;

                    
                
            }
            if (mousepos.x >= 985 && mousepos.x <= 1055 && mousepos.y >= 580 && mousepos.y <= 650 && Mouse::isButtonPressed(Mouse::Left) && checkdelay >= 5)
            {
                if (soundeffectON)
                    MenuClick.play();
                soundeffectON = !soundeffectON;
                checkdelay = 0;
            }

            if (musicON == true) 
            {
                window.draw(checkbox[0]);
            }
            if (soundeffectON == true)
            {
                window.draw(checkbox[1]);
            }
            window.draw(sprite);
        }
        // coop or single menu
        if (page == 9)
        {
            lvldiff();
            mainmenu();
            modeselectdelay++;
            coopclick++;
            backdelay=0;
            
            window.draw(Logo);
            for (int i = 0; i < 2; i++)
            {
                window.draw(rectangleselectmode[i]);
            }
            //single
            if (mousepos.x >= 585 && mousepos.x <= 935 && mousepos.y >= 480 && mousepos.y <= 550 && Mouse::isButtonPressed(Mouse::Left) && modeselectdelay >= 5)
            {
                page = 10;
                
                
            }
            //coop
            if (mousepos.x >= 985 && mousepos.x <= 1335 && mousepos.y >= 480 && mousepos.y <= 550 && Mouse::isButtonPressed(Mouse::Left) && modeselectdelay >= 5)
            {
                
                coopon = true;
                temptest2 = 1;
                MainMusicPlaying = false;
                IngameMusicPlaying = true;
                if (musicON)
                {
                    ingamemusic.play();
                    MenuMusic.stop();
                }
                if (soundeffectON)
                {
                    shipin.play();
                }
                clock4.restart();
                clock3.restart();
                page = 6;
                pausecooldown = 0;
                modeselectdelay = 0;
               
                goto beginning;
            }
            //back
            if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left) )
            {
                if (soundeffectON)
                    MenuClick.play();
                page = 1;
               
            }
            window.draw(rectangleback);
            window.draw(back);
            window.draw(single);
            window.draw(coop);
            window.draw(sprite);
         
        }
            if (page == 10) {
                
    
                    if (Keyboard::isKeyPressed(Keyboard::Enter) && Name.size() >= 1)
                    {
                        for (int i = 0; i < Name.size();i++)
                        {
                            for (char v = 'a'; v <= 'z';v++)
                            {
                                if (Name[i] == v || Name[i] == toupper(v))
                                {
                                    temptest2 = 1;
                                    MainMusicPlaying = false;
                                    IngameMusicPlaying = true;
                                    clock3.restart();
                                    clock4.restart();
                                    if (musicON)
                                    {
                                        ingamemusic.play();
                                        MenuMusic.stop();
                                    }
                                    if (soundeffectON)
                                    {
                                        shipin.play();
                                    }
                                    
                                    page = 6;
                                    pausecooldown = 0;
                                    modeselectdelay = 0;
                                    MainMusicPlaying = false;
                                    IngameMusicPlaying = true;
                                    if (musicON)
                                    {
                                        ingamemusic.play();
                                        MenuMusic.stop();
                                    }
                                    goto beginning;
                                }
                            }
                        }
                        


                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        page = 9;
                        Name = "";
                        shipin.stop();
                    }
                    t2.setString(Name);

                    window.draw(t1);
                    window.draw(t2);

            }
            
        sprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(window))); // Set position 
        
        // window display
        window.setView(view1);
     
        window.display();
    }
    return 0;
}









