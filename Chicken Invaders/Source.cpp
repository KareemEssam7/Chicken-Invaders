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

//camera
sf::View view1(sf::Vector2f(960.f, 540.f), sf::Vector2f(1920.f, 1080.f));

// Intialized Variables
int exp_x=0,exp_y=0 ;
int sparkx = 0;
long long cnt = 0;  //counter for
 int health = 3;
int rockets = 0;
int powerlvls = 0;
double PlayerMovement = 9, PlayerSpeed = 12;
double ChickenDir = 0,rectdir,bossdir=0,chickeninitialpos=0;
int ChickenMovement = 0 ;
int timer[8][5];
int x = 0, y = 0, z = 0 ,n=15;
int yolkcnt = 0;
int pausecooldown = 0;
int animation = 0;
long long page = 0;
bool checkchickenanimation = true, check = true, bossanimation=true;
bool playeralive=true;
bool chickenalive = true;
ChickenStruct chicken;
bulletstruct bullet;
meteorstruct meteors;
bossstruct boss;
int chickenpx[8][6] = {}, chickenpy[8][6] = {};
int foodcnt = 0;
int yolktimer[8][5] = {} ;
int tmp, meteortimer[40], meteorhp[40], meteorx = 0;
int xmeteor=0, ymeteor=0;
bool frommenu = true;
int delay = 0;
int backdelay = 0;
int rotatecheck = 0;
int checkdelay = 0;
int modeselectdelay = 0;
int soundeffectstart = 0;
int coopclick = 0;
int yolkanime = 0;
int yolkvar = 100;
int eggvar = 501;
int expbool = 0;
int sparkbool = 0;
int health2 = health;
bool musicON = true;
bool soundeffectON = true;
bool ldbcheck[5] = {};
bool MainMusicPlaying = true, IngameMusicPlay = false, IngameMusicPlaying = false;
int lastlevel = 1;
double curscale[7] = {1, 1, 1, 1, 1, 1, 1};
int temptest = 0, temptest2 = 0,temptest3=0;
bool arr[5] = {};
//missile variables
int missileScoreCount = 0, camerashakelength = 6;
bool activemissile = false, explosioncamerashake = false;
bool yolk[8][5] = { };
int Timer=2;
int timer2 = 1;
bool gameover=false;
//sound variables
int currentshootsfx = 0, currentchickensfx = 0, currenteggshootsfx = 0;
//shield variables
bool bullet_shot = 0;
bool shield_on = 0;
Clock clock4;
Clock clock3;
bool Wave1 = 1, Wave2 =0, Wave3 = 0, Wave4 = 0, Wave5 = 0;
char prevwave = '1';
bool chickendead[8][5];
int alivechicken = 0;
int meteoralive = 0;
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
Texture bossimage;
Texture gamelogo;
Texture gamemenubg;
Texture arrow1;
Texture fork;
Texture checkmark;
Texture earth;
Texture GameBarSkin;
Texture BottomBarSkin;
Texture explosionimage;
Texture missileTexture;
Texture sparkimage;
Texture fogimage;

// adding border
RectangleShape rectangle1(Vector2f(60, 1080));
RectangleShape rectangle2(Vector2f(60, 1080));
RectangleShape rectangle3(Vector2f(1300, 200));

//borders for boss!!
RectangleShape rectangle4(Vector2f(window.getSize().x, 75));
RectangleShape rectangle5(Vector2f(window.getSize().x, 75));
// sound buffers
SoundBuffer Select;
SoundBuffer shoot1sfx;
SoundBuffer chickensfx;
SoundBuffer eggshootsfx;
SoundBuffer rocketshootsfx;
SoundBuffer explodingsfx;
// sounds
Sound MenuClick;
Sound shoot1[2];
Sound chickenhurt[2];
Sound eggshoot[2];
Sound rocketshoot;
Sound exploding;
//music
Music MenuMusic;
Music ingamemusic;
//Buttons
RectangleShape rectanglemainmenu[5];
RectangleShape rectangleoption[2]; 
RectangleShape rectangleback(Vector2f(200, 70));
RectangleShape rectanglecont(Vector2f(350, 70));
RectangleShape rectanglereturn(Vector2f(350, 70));
RectangleShape rectanglelevels[5];
RectangleShape rectanglecontrols[6][2];
RectangleShape rectanglecheck[2];
RectangleShape rectangleldbs[5];
RectangleShape rectangleselectmode[2];
//shield
CircleShape Shield(60);


//adding texts
Text hp;
Text rocket;
Text score;
Text powerlvl;
Text foodscore;
Text play;
Text Options;
Text Leaderboard;
Text Credits;
Text Quit;
Text controls;
Text sound;
Text back;
Text Option;
Text cont;
Text levels[5];
Text ret;
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
Text ldb[5];
Text Cred[7];
Text single;
Text coop;
Text wave1first;
Text wave1second;
Text endofwave1;
//adding font
Font font1;
Font font3;
Font font2;
// Ingame Sprites
Sprite _GameBackground;
Sprite Player;
Sprite Chicken[8][6];
Sprite Chicken2[8][6];
Sprite explosion;
Sprite Bullets[40];
Sprite health_bar;
Sprite Eggs[8][5];
Sprite eggyolk[8][5];
Sprite bossegg[5];
Sprite bossegg1[5];
Sprite bossegg2[5];
Sprite chicken_legs[8][6];
Sprite meteor[40];
Sprite bosssprite;
Sprite Logo;
Sprite menubg;
Sprite arrow_l[2];
Sprite arrow_r[2];
Sprite arrow_up[2];
Sprite arrow_dw[2];
Sprite checkbox[2];
Sprite Earth;
Sprite Gamebar;
Sprite Bottombar;
Sprite missile;
Sprite spark;
Sprite fog;
// Loading Ingame Files
void IngameImages()
{
    //fonts
    font1.loadFromFile("RobotoCondensed-Bold.ttf");
    font3.loadFromFile("Wedgie_Regular.ttf");
    font2.loadFromFile("Lobster-Regular.ttf");
    // audio
    Select.loadFromFile("Select.wav");
    MenuClick.setBuffer(Select);
    shoot1sfx.loadFromFile("weapon1.wav");
    for (int i = 0; i < 2; i++)
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
    // music
    MenuMusic.openFromFile("IntroMenu.wav");
    ingamemusic.openFromFile("ingame.wav");
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
    // ingame images
    GameBarSkin.setSmooth(true);
    GameBarSkin.loadFromFile("TopBar.png");
    BottomBarSkin.loadFromFile("BottomBar.png");
    BottomBarSkin.setSmooth(true);
    Bottombar.setTexture(BottomBarSkin);
    Bottombar.setPosition(0, 975);
    Bottombar.setScale(1.5, 1.5);
    Gamebar.setTexture(GameBarSkin);
    Gamebar.setPosition(0, 0);
    Gamebar.setScale(1.5, 1.5);
    //player explosion
    explosionimage.loadFromFile("PlayerDeath.png");
    explosion.setTexture(explosionimage);
    explosion.setPosition(7000, 7000);
    sparkimage.loadFromFile("sparkspink.png");
    spark.setTexture(sparkimage);
    spark.setPosition(8000, 8000);

    //Shield
    Shield.setFillColor(Color(0, 102, 204, 140));
    Shield.setPosition(10000, 10000);

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
    //Buttons in leaderboard menu
    for (int i = 0; i < 5; i++)
    {
        rectangleldbs[i].setSize(Vector2f(350, 70));
        rectangleldbs[i].setPosition(50+i*370, 25 );
        rectangleldbs[i].setFillColor(Color(0, 0, 255, 40));
        rectangleldbs[i].setOutlineColor(Color(51, 153, 255, 60));
        rectangleldbs[i].setOutlineThickness(2.8f);
    }
 
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
  
    //Leaderboard text
    Leaderboard.setFont(font1);
    Leaderboard.setCharacterSize(32);
    Leaderboard.setPosition(880, 695);
    Leaderboard.setString("Hall Of Fame");
    Leaderboard.setFillColor(Color(204, 229, 255, 225));
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

    //health
    hp.setFont(font1);
    hp.setCharacterSize(35);
    hp.setOrigin(0, 0);
    hp.setPosition(70, window.getSize().y - 58);
    hp.setString(to_string(health));

    // rockets
    rocket.setFont(font1);
    rocket.setCharacterSize(35);
    rocket.setOrigin(0, 0);
    rocket.setPosition(160, window.getSize().y - 58);
    rocket.setString(to_string(rockets));

    // powerlvl
    powerlvl.setFont(font1);
    powerlvl.setCharacterSize(35);
    powerlvl.setOrigin(0, 0);
    powerlvl.setPosition(260, window.getSize().y - 58);
    powerlvl.setString(to_string(powerlvls));

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
    foodscore.setPosition(350, window.getSize().y - 58);
    foodscore.setString( to_string(foodcnt));

    //meteor
    meteortex.loadFromFile("Stones.png");
    for (int i = 0; i < meteors.meteorcount; i++)
    {
        meteor[i].setTexture(meteortex);
        meteor[i].setTextureRect(IntRect(62.625 * xmeteor, 62.25 * ymeteor, 62.625f, 62.25f));
    }

    //missile image
    missileTexture.loadFromFile("missile.png");
    missile.setTexture(missileTexture);
    missile.setPosition(10000, 10000);
    missile.setScale(0.05, 0.05);
    

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

            eggyolk[i][j].setTexture(eggbreak);
            eggyolk[i][j].setTextureRect(IntRect(28 * 5, 0, 28, 24));
            eggyolk[i][j].setScale(2, 2);

            yolktimer[i][j] = 50;
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
//spark and fog
void spark_fog() {


    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 8; j++) {
            for (int z = 0; z < 5; z++) {
                if (Bullets[i].getGlobalBounds().intersects(Chicken[j][z].getGlobalBounds())) {

                    chickenalive = false;
                    spark.setPosition(Chicken[j][z].getPosition()-Vector2f(50,50));
                }



            }
        }
    }
    if (chickenalive == false) {
        spark.setTextureRect(IntRect(277 * sparkx, 0, 277, 269));
        sparkx++;
        if (sparkx == 10) {
            sparkx = 0;

           // if (timer2 <= 0) {
                chickenalive = true;

            //    timer2= 1;


              


           // }
           // else
           //     timer2--;
            if(chickenalive==true)
                spark.setPosition(4000,5000);
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
        Shield.setPosition(10000, 10000);


    }
    if ((Keyboard::isKeyPressed(Keyboard::Space)) && bullet.bulletCoolDown == 0 && pausecooldown == 1 || (Mouse::isButtonPressed(Mouse::Left)) && bullet.bulletCoolDown == 0 && pausecooldown == 1)
    {
        bullet.bulletCoolDown = bullet.bulletCoolDownvar;
        bullet_shot = 0;
        shield_on = 0;
        Bullets[bullet.currentBullet].setPosition(Player.getPosition().x + 29, Player.getPosition().y - 45);

        if (soundeffectON && playeralive)
        {
            shoot1[currentshootsfx].play();
            currentshootsfx++;
            if (currentshootsfx == 2)
            {
                currentshootsfx = 0;
            }
        }

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

//missile shooting function
void rocketshooting()
{
    //shooting
    if (Mouse::isButtonPressed(Mouse::Right) && activemissile == false && rockets > 0)
    {
        activemissile = true;
        if (soundeffectON) 
        {
            rocketshoot.play();
        }
        missile.setPosition(Player.getPosition().x + 29, Player.getPosition().y - 45);
        rockets--;
        rocket.setString(to_string(rockets));
    }

    //missile moving
    if (activemissile == true)
    {
        missile.move(0, -bullet.bulletSpeed * 2);
    }


    //missile explosion
    if (missile.getPosition().y <= 400)
    {
        activemissile = false;
        missile.setPosition(10000, 100000);
        explosioncamerashake = true;
        if (soundeffectON)
        {
            exploding.play();
        }
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                Chicken[i][j].setPosition(10000, 10000);
            }
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
        explosioncamerashake = false;
        camerashakelength = 6;
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

            Chicken[i][j].setTexture(ChickenSkin);
            Chicken[i][j].setScale(2.75, 2.75);
            if (chickeninitialpos == 0) 
            {
                Chicken[i][j].setPosition(120 + (i * 170), 70 + (j * 100));
            }
            Chicken[i][j].setTextureRect(IntRect(ChickenMovement * 46.9, 0, 46.9, 38));
        }
    }
    chickeninitialpos = 1;

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
//reducing heart by 1  (ahmed,ziad)
void playerdamage() {

    if (shield_on == 0)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                if (Eggs[i][j].getGlobalBounds().intersects(Player.getGlobalBounds())) {
                    health -= 1;
                    if (soundeffectON)
                    {
                        exploding.play();
                    }
                    hp.setString(to_string(health));
                    Eggs[i][j].setPosition(4000, 5000);
                }

            }
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


                    if (health == 0) {
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
}

//Shield movement
void shield_move()
{
    if (shield_on == 1)
    {
        Shield.setPosition(Player.getPosition().x - 18, Player.getPosition().y - 25);
    }
    else
    {
        Shield.setPosition(10000, 10000);
    }

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

                timer[i][j] = rand() % eggvar;

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
            if (timer[i][j]==-1)
            {
                Eggs[i][j].move(0, 9.8f);
            }
            if (Eggs[i][j].getPosition().y >= 1000)
            {

                yolk[i][j] = 1;
                eggyolk[i][j].setPosition(Eggs[i][j].getPosition().x, 1000);
                timer[i][j] = rand() % eggvar;
                timer[i][j]--;
                Eggs[i][j].setScale(0,0);
                eggyolk[i][j].setScale(2,2);
                /*if (yolktimer[i][j] >= 0)
                {
                    eggyolk[i][j].setScale(2, 2);
                    yolktimer[i][j]--;
                }
                if (yolktimer[i][j] == 0)
                {
                    
                    yolktimer[i][j] = 50;
                }*/
                
            }
            if (Eggs[i][j].getGlobalBounds().intersects(Shield.getGlobalBounds()))
            {
                Eggs[i][j].setPosition(10000, 10000);
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
          if (Player.getGlobalBounds().intersects(meteor[i].getGlobalBounds()) && shield_on==false) {
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


                          if (health == 0) {
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

                if (Bullets[i].getGlobalBounds().intersects(Chicken[j][z].getGlobalBounds())) 
                {
                    chickendead[j][z] = 1;
                    eggvar -= 5;
                    cnt += 1000;
                    score.setString(to_string(cnt));
                    Bullets[i].setPosition(-10000, -10000);
                    chicken_legs[j][z].setPosition(Chicken[j][z].getPosition().x, Chicken[j][z].getPosition().y);
                    Chicken[j][z].setPosition(10000, 100000);
                    missileScoreCount += 1000;
                    if (missileScoreCount == 70000)
                    {
                        missileScoreCount = 0;
                        rockets += 1;
                        rocket.setString(to_string(rockets));
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

                if (chicken_legs[j][z].getGlobalBounds().intersects(Player.getGlobalBounds())) 
                {
                    chicken_legs[j][z].setPosition(4000, -100);
                    foodcnt += 1;
                    foodscore.setString(to_string(foodcnt));
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
        if (mousepos.x >= 585 + i * 400 && mousepos.x <= 935+ i * 400 && mousepos.y >= 480 && mousepos.y <= 550)
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
        if (mousepos.x >= 50 + i*370  && mousepos.x <= 400 + i * 370 && mousepos.y >= 25  && mousepos.y <= 95)
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
            if (mousepos.x >= 500 + j*470  && mousepos.x <= 950 +j*470  && mousepos.y >= 480 +i * 100 && mousepos.y <= 550 + i *100 )
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
        if (mousepos.x >= 985 && mousepos.x <= 1055  && mousepos.y >= 480 + i * 100 && mousepos.y <= 550 + i * 100)
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
    bosssprite.setTextureRect(IntRect(75 * animation, 0, 75, 68));
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

        //collision egg
        /*if (bossegg[i].getGlobalBounds().intersects(Player.getGlobalBounds()))
        {
            Player.setPosition(10000, 10000);
        }*/


  
    







}
void reset()
{
    chickeninitialpos = 0;
    cnt = 0;
    foodcnt = 0;
    health = 3;
    health2 = 3;
    powerlvls = 0;
    rockets = 0;
    missileScoreCount = 0;
    Timer = 2;
    cnt = 0;
    boss.bosshp = 50;
    boss.eggcooldownvar = 301;
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
    prevwave = '1';
    Wave2 = false,Wave3=false,Wave4=false,Wave5=false,Wave1=true;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            eggyolk[i][j].setPosition(10000, 10000);
            chickendead[i][j] = 0;
        }
    }
}
int main()
{

    window.setMouseCursorVisible(false); // Hide cursor  
    View fixed = window.getView(); // Create a fixed view  

    

    // Load image and create sprite
    
    fork.loadFromFile("Fork.png");  
    Sprite sprite(fork);   
    sprite.setScale(1.4, 1); 
    // add functions
beginning: {};
    cnt = 0;
    boss.bosshp = 50;
    boss.eggcooldownvar = 301;
    IngameImages();

    // main game loop
    if (MainMusicPlaying && musicON && IngameMusicPlaying == false)
    {
        MenuMusic.play();
    }
    if (musicON && IngameMusicPlaying && MainMusicPlaying == false)
    {
        ingamemusic.play();
    }


    MainMusicPlaying = false;
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
        if (page == 0)
        {
            modeselectdelay = 0;
            delay = 0;
            frommenu = true;
            window.draw(menubg);
            window.draw(Logo);
            mainmenu();
            window.draw(play);
            window.draw(Options);
            window.draw(Leaderboard);
            window.draw(Credits);
            window.draw(Quit);
            window.draw(sprite);
            for (int i = 0; i < 5; i++)
            {
                window.draw(rectanglemainmenu[i]);
            }
            if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550 )
            {
                if (soundeffectON)
                    MenuClick.play();
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
            window.draw(menubg);
            window.draw(rectangleback);
            window.draw(back);
           
            for (int i = 0; i < 5; i++)
            {
                window.draw(rectanglelevels[i]);
                window.draw(levels[i]);
            }
            //level1
            if (mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 180 && mousepos.y <= 250 && Mouse::isButtonPressed(Mouse::Left))
            {
                if (soundeffectON)
                    MenuClick.play();
                page = 9;
 
            } 
            window.draw(sprite);
        }
        // options page ==2
        if (page == 2)
        {
            // back
            modeselectdelay = 0;
            backdelay++;
            delay++;
            checkdelay = 0;
                if (mousepos.x >= 50 && mousepos.x <= 250 && mousepos.y >= 900 && mousepos.y <= 970 && Mouse::isButtonPressed(Mouse::Left) && backdelay>=5)
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
                window.draw(menubg);
                window.draw(Logo);
                window.draw(Option);
                window.draw(rectangleback);
                for (int i = 0; i < 2; i++)
                    window.draw(rectangleoption[i]);
                window.draw(controls);
                window.draw(sound);
                window.draw(back);
                window.draw(sprite);
                if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 480 && mousepos.y <= 550 &&delay>=5)
                {
                    if (soundeffectON)
                        MenuClick.play();
                    delay = 0;
                    page = 7;
                }
                if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x >= 785 && mousepos.x <= 1135 && mousepos.y >= 580 && mousepos.y <= 650 && delay>=5)
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
           
            window.draw(menubg);
            for (int i = 0; i < 5; i++)
            {
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
        }
        // credits page ==4
        if (page == 4)
        {
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
            window.draw(menubg);
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
                page = 0;
            }
        }
        //pause menu
        if (page == 5)
        {
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
              reset();
              goto beginning;

          }
            window.draw(menubg);
            window.draw(Logo);
            for (int i = 1; i < 4; i++)
            {
                window.draw(rectanglemainmenu[i]);
            }
            window.draw(rectanglecont);
            window.draw(rectanglereturn);
            window.draw(cont); 
            window.draw(Options); 
            window.draw(Leaderboard); 
            window.draw(Credits); 
            window.draw(ret); 
            window.draw(sprite); 
        } 
        // ingame
        if (page == 6)
        {

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
            /*if (IngameMusicPlay)
            {
                ingamemusic.play();
                IngameMusicPlay = false;
                IngameMusicPlaying = true;
            }*/
            if (Wave1 == true)
            {
                prevwave = '1';
                alivechicken = 0;
                if (clock4.getElapsedTime().asSeconds() >= 9)
                {

                    PlayerShooting();
                    rocketshooting();
                    ChickenMove();
                    eggmovement();
                    spark_fog();
                    scorecalc();
                    camerashake();
                    window.draw(_GameBackground);
                    window.draw(rectangle1);
                    window.draw(rectangle2);

                    if (gameover == true) {
                        gameover = false;

                        temptest = 1;
                        page = 1;
                        reset();
                        goto beginning;

                    }


                    for (int j = 0; j < 5; j++)
                    {

                        for (int i = 0; i < 8; i++)
                        {

                            window.draw(eggyolk[i][j]);
                            window.draw(Chicken[i][j]);
                            window.draw(Eggs[i][j]);
                        }
                    }

                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    window.draw(explosion);
                    for (int i = 0; i < 40; i++)
                    {
                        window.draw(Bullets[i]);
                        if (Bullets[i].getGlobalBounds().intersects(Gamebar.getGlobalBounds()))
                        {
                            Bullets[i].setPosition(4000, 4000);
                        }
                    }
                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (chickendead[i][j] == 0)
                                alivechicken++;
                        }
                    }
                    if (alivechicken == 0)
                    {
                        Wave1 = false;
                        Wave2 = true;
                        clock4.restart();
                        clock3.restart();
                        for (int i = 0; i < 40; i++)
                        {
                            Bullets[i].setPosition(9000, 9000);
                        }
                        spark.setPosition(9000, 9000);
                       
                          
                       
                    }
                    shield_move();
                    window.draw(Shield);

                    //drawing missile
                    window.draw(missile);
                    window.draw(spark);

                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        page = 5;


                    }
                }
                else
                {
                    window.draw(_GameBackground);
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
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
            if (Wave2 == true)
            {
                meteoralive = 0;
                wave1second.setString("Wave " + to_string(prevwave - 48));
                if (prevwave == '1')
                {
                    clock3.restart();
                    clock4.restart();
                    for (int i = 0; i < 8; i++)
                    {
                        for (int a = 0; a < 5; a++)
                        {
                            Chicken[i][a].setPosition(-2000, 2000);
                            eggyolk[i][a].setPosition(10000, 10000);
                            chickendead[i][a] = 0;
                        }
                    }
                    chickeninitialpos = 0;
                }
                prevwave = '2';
                if (clock4.getElapsedTime().asSeconds() >= 9)
                {
                    meteormove();
                    PlayerShooting();
                    rocketshooting();
                    spark_fog();
                    scorecalc();
                    camerashake();
                    window.draw(_GameBackground);
                    window.draw(rectangle1);
                    window.draw(rectangle2);

                    if (gameover == true) {
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
                    if (meteoralive == 0)
                    {
                        Wave2 = false;
                        Wave3 = true;
                       
                        clock4.restart();
                        clock3.restart();
                        for (int i = 0; i < 40; i++)
                        {
                            Bullets[i].setPosition(9000, 9000);
                        }
                        spark.setPosition(9000, 9000);
                        
                    }
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    window.draw(explosion);
                    for (int i = 0; i < 40; i++)
                    {
                        window.draw(Bullets[i]);
                        if (Bullets[i].getGlobalBounds().intersects(Gamebar.getGlobalBounds()))
                        {
                            Bullets[i].setPosition(4000, 4000);
                        }
                    }
                    shield_move();
                    window.draw(Shield);

                    //drawing missile
                    window.draw(missile);
                    window.draw(spark);
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        page = 5;


                    }
                }
                else
                {
                    window.draw(_GameBackground);
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
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
            if (Wave3 == true)
            {
                alivechicken = 0;
                wave1second.setString("Wave " + to_string(prevwave - 48));
                if (prevwave == '2' )
                {
                    clock3.restart();
                    clock4.restart();
                }
                prevwave = '3';
              
                if (clock4.getElapsedTime().asSeconds() >= 9)
                {

                    PlayerShooting();
                    rocketshooting();
                    ChickenMove();
                    eggmovement();
                    spark_fog();
                    scorecalc();
                    camerashake();
                    window.draw(_GameBackground);
                    window.draw(rectangle1);
                    window.draw(rectangle2);

                    if (gameover == true) {
                        gameover = false;

                        temptest = 1;
                        page = 1;
                        reset();
                        goto beginning;

                    }


                    for (int j = 0; j < 5; j++)
                    {

                        for (int i = 0; i < 8; i++)
                        {

                            window.draw(eggyolk[i][j]);
                            window.draw(Chicken[i][j]);
                            window.draw(Eggs[i][j]);
                        }
                    }

                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
                    window.draw(foodscore);
                    window.draw(hp);
                    window.draw(rocket);
                    window.draw(powerlvl);
                    window.draw(explosion);
                    for (int i = 0; i < 40; i++)
                    {
                        window.draw(Bullets[i]);
                        if (Bullets[i].getGlobalBounds().intersects(Gamebar.getGlobalBounds()))
                        {
                            Bullets[i].setPosition(4000, 4000);
                        }
                    }
                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (chickendead[i][j] == 0)
                                alivechicken++;
                        }
                    }
                    if (alivechicken == 0)
                    {
                        Wave3 = false;
                        Wave4 = true;
                        clock4.restart();
                        clock3.restart();
                        for (int i = 0; i < 40; i++)
                        {
                            Bullets[i].setPosition(9000, 9000);
                        }
                        spark.setPosition(9000, 9000);
                        for (int i = 0; i < 8; i++)
                        {
                            for (int a = 0; a < 5; a++)
                            {
                                Chicken[i][a].setPosition(-2000, 2000);
                            }
                        }
                    }
                    shield_move();
                    window.draw(Shield);

                    //drawing missile
                    window.draw(missile);
                    window.draw(spark);
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        page = 5;

                    }
                }
                else
                {
                    window.draw(_GameBackground);
                    window.draw(health_bar);
                    window.draw(Gamebar);
                    window.draw(score);
                    window.draw(Bottombar);
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
            playerdamage();
            PlayerMove();
            window.draw(Player);
        }
        // control
        if (page == 7)
        {
            modeselectdelay = 0;
            delay = 0;
            checkdelay = 0;
            backdelay++;
            mainmenu();
            window.draw(menubg);
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
            window.draw(menubg);
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
                if (!IngameMusicPlaying)
                {
                    if (soundeffectON)
                    {
                        MenuClick.play();
                        MenuMusic.play();
                        MenuMusic.play();
                    }
                    musicON = !musicON;
                    if (musicON)
                    {
                        MainMusicPlaying = true;
                        goto beginning;
                    }
                    else
                    {
                        MainMusicPlaying = false;
                        goto beginning;
                    }
                    checkdelay = 0;
                }
                else
                {
                    if (soundeffectON)
                    {
                        MenuClick.play();
                    }
                    musicON = !musicON;
                    if (musicON)
                    {
                        IngameMusicPlay = true;
                        goto beginning;
                    }
                    else
                    {
                        IngameMusicPlay = false;
                        goto beginning;
                    }
                    checkdelay = 0;
                }
                
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
            clock3.restart();
            clock4.restart();
            mainmenu();
            modeselectdelay++;
            coopclick++;
            backdelay=0;
            window.draw(menubg);
            window.draw(Logo);
            for (int i = 0; i < 2; i++)
            {
                window.draw(rectangleselectmode[i]);
            }
            //single
            if (mousepos.x >= 585 && mousepos.x <= 935 && mousepos.y >= 480 && mousepos.y <= 550 && Mouse::isButtonPressed(Mouse::Left) && modeselectdelay >= 5)
            {
                temptest2 = 1;
                MainMusicPlaying = false;
                IngameMusicPlaying = true;
                page = 6;
                pausecooldown = 0;
                modeselectdelay = 0;
                    goto beginning;
            }
            //coop
            if (mousepos.x >= 985 && mousepos.x <= 1335 && mousepos.y >= 480 && mousepos.y <= 550 && Mouse::isButtonPressed(Mouse::Left) && modeselectdelay >= 5)
            {
             
                if (soundeffectON && coopclick >= 5)
                {
                    MenuClick.play();
                    coopclick = 0;
                }
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
        sprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(window))); // Set position 
        
        // window display
        window.setView(view1);
     
        window.display();
    }
    return 0;
}