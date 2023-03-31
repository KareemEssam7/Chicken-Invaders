#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <algorithm>
#include<ctime>
using namespace std;
using namespace sf;
// Creating Game Window
RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders");
// adding textures
Texture Background;




// Ingame Sprites
Sprite _GameBackground;



// Loading Ingame Files
void IngameImages()
{
    // background
    Background.loadFromFile("IngameBackground.jpg");
    _GameBackground.setTexture(Background);
    _GameBackground.setScale(1.875f, 1.05f);
}
int main()
{
    // add functions
    IngameImages();
    // main game loop
    while (window.isOpen())
    {
        // set framelimit
        window.setFramerateLimit(60);
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
        //draw window
        window.draw(_GameBackground);
        // show window
        window.display();
    }
    return 0;
}