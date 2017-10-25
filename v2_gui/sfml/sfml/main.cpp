
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include <iostream>
#include <string.h>
#include <sstream>
#include <Tile.hpp>
#include "Swipe.h"

using namespace sf;


int score = 0;
int hiscore = 0;

bool moved = false;
int timesRendered = 0;
int screenXoffset = 100;
int screenYoffset = 150;
int boxWidth = 100;

Swipe game;

sf::Text scoreLabel;
sf::Text hiscoreLabel;
sf::Text roundOver;

sf::RectangleShape loadGame;
sf::RectangleShape saveGame;
sf::RectangleShape newGame;




void drawGrid(RenderWindow & window){
    for(int i = 0; i < 5; i++){
        RectangleShape line(Vector2f(400,5));
        line.setPosition( screenXoffset , boxWidth * i + screenYoffset  );
        window.draw(line);
    }
    
    for(int i = 0; i < 5; i++){
        RectangleShape line(Vector2f(405,5));
        line.setPosition(boxWidth * i + screenXoffset , screenYoffset);
        line.rotate(90);
       window.draw(line);
    }
}

void processInput(RenderWindow & window){
    
}

void update(){
    
}

void render(RenderWindow & window){
    
}

void drawScore(RenderWindow & window){
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    std::stringstream ss;
    ss << "Score: ";
    ss << game.score;
    sf::Text text(ss.str(), font, 40);
    text.setFillColor(sf::Color::Green);
    text.setPosition(0 + 15, 0 + 15);
    
    std::stringstream hss;
    hss << "Hiscore: ";
    hss << game.hiscore;
    sf::Text hi(hss.str(), font, 40);
    hi.setFillColor(sf::Color::Green);
    hi.setPosition(0 + 15, 50 + 15);

    
    window.draw(hi);
    window.draw(text);
}
int calculateFontSize(int value){
    int size = 50;
    if(value > 100 && value <= 999){
        size = 40;
    }
    if( value > 1000 && value <= 9999){
        size = 30;
    }
    if( value > 10000 && value <= 999999){
        size = 20;
    }
    return size;
}

int calculateFontOffset(int value){
    int offset = 30;
     if(value > 100 && value <= 999){
        offset = 25;
    }
    if( value > 1000 && value <= 9999){
        offset = 20;
    }
    if( value > 10000 && value <= 999999){
        offset = 15;
    }
    return offset;
}

Color selectColor(int value){
    if(value == 2){
        return Color(235, 222, 210);
    }
    if(value == 4){
        return Color(234, 218, 188);
    }
    if(value == 8){
        return Color(238, 162, 102);
    }
    if(value == 16){
        return Color(240, 129, 81);
    }
    if(value == 32){
        return Color(241, 101, 77);
    }
    if(value == 64){
        return Color(223, 64, 45);
    }
    if(value == 128){
        return Color(238, 208, 88);
    }
   if(value == 256){
       return Color(232, 195, 81);
   }
   if(value == 512){
       return Color(230, 190, 64);
   }
   if(value == 1024){
       return Color(232, 187, 49);
   }
   if(value == 2048){
       return Color(232, 182, 36);
   }
  if(value == 4096){
    return Color(168, 111, 156);
  }
  if(value == 8192){
    return Color(158, 85, 153);
  }
}

void draw(int x, int y, int v, RenderWindow & window){
    Tile t(y * 100 + screenXoffset + 2, x * 100 + screenYoffset + 7, v );
    t.twoTile.setFillColor(selectColor(v));
    t.render(window);
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    std:std::stringstream ss;
    ss << v ;
    int fontSize = calculateFontSize(v);
    sf::Text text(ss.str(), font, fontSize);
    text.setFillColor(sf::Color::Black);
    
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(100/2.0f + t.x,100/2.0f + t.y));
    
   // std::cout << "Width of text area: " << width << " " << v << std::endl;
  //  text.setPosition(t.x + calculateFontOffset(v), t.y + calculateFontOffset(v));
    
    window.draw(text);
    
}

bool contains(RectangleShape s, int x, int y){
    bool contains = false;
    if(x > s.getPosition().x && x <= s.getPosition().x + s.getLocalBounds().width){
        if(y > s.getPosition().y && y <= s.getPosition().y + s.getLocalBounds().height){
            contains = true;
            std::cout << "Contains!" << std::endl;
        }
    }
    
    return contains;
}

void drawButtons(RenderWindow & window){
    
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Load", font, 30);
    
    text.setFillColor(sf::Color::Green);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(loadGame.getLocalBounds().width/2.0f + loadGame.getPosition().x ,loadGame.getLocalBounds().height/2.0f + loadGame.getPosition().y));
    
    sf::Text hi("Save", font, 30);
    hi.setFillColor(sf::Color::Green);
    sf::FloatRect t = hi.getLocalBounds();
    hi.setOrigin(t.left + t.width/2.0f, t.top  + t.height/2.0f);
    hi.setPosition(sf::Vector2f(saveGame.getLocalBounds().width/2.0f + saveGame.getPosition().x ,loadGame.getLocalBounds().height/2.0f + loadGame.getPosition().y));

    sf::Text n("New", font, 30);
    n.setFillColor(sf::Color::Green);
    sf::FloatRect bound = n.getLocalBounds();
    n.setOrigin(t.left + bound.width/2.0f, t.top  + bound.height/2.0f);
    n.setPosition(sf::Vector2f(newGame.getLocalBounds().width/2.0f + newGame.getPosition().x ,newGame.getLocalBounds().height/2.0f + newGame.getPosition().y));

    window.draw(loadGame);
    window.draw(saveGame);
    window.draw(newGame);
    window.draw(text);
    window.draw(hi);
    window.draw(n);
}
void convert(RenderWindow & window){
    window.clear();
    drawGrid(window);
    for(int i = 0; i < game.rows; i++){
        for (int j = 0; j < game.cols; j++){
            if(!game.isOpen(i, j)){
               // std::cout << "AT: " << i << " " << j << " value: " << game.board[i][j] << std::endl;
                draw(i,j, game.board[i][j], window);
            }
        }
    }
    drawScore(window);
    drawButtons(window);
    
    if(!game.playing){
        window.draw(roundOver);
    }
   // window.draw(roundOver);

    window.display();
}

void gameOver(RenderWindow & window){
    
    std::cout << "Press space bar to play again " << std::endl;
    
}

void handleInput(int d, RenderWindow & window){ //0 down, 1 up, 2 right, 3 left
    if(d == 0){
        game.down();
    }
    if(d == 1){
        game.up();
    }
    if(d == 2){
        game.right();
    }
    if(d == 3){
        game.left();
    }
    game.spawn();
    game.print();
    convert(window);
    
    if(game.playing){
        std::cout << "STILL PLAYING" << std::endl;
        
    }else{
        std::cout << "OVER\n";
    }
    
}

int main(int, char const**){
    
    int HEIGHT = 700;
    int WIDTH = 600;
    
    // Create the main window
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2048 by Preston Meade");
        window.setKeyRepeatEnabled(false);
    
    loadGame.setSize(Vector2f(100,50));
    loadGame.setFillColor(Color::Blue);
    loadGame.setPosition(100, 600);
    
    saveGame.setSize(Vector2f(100,50));
    saveGame.setFillColor(Color::Blue);
    saveGame.setPosition(400, 600);
    

    newGame.setSize(Vector2f(100,50));
    newGame.setFillColor(Color::Blue);
    newGame.setPosition(250, 600);
    
    
    
    
    
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
   
    roundOver.setFont(font);
    roundOver.setFillColor(Color::Red);
    roundOver.setString("Game Over!\nPress Space bar");
    roundOver.setPosition(300, 50);

    
    
    
    Tile tile(100,100, 2);
    
    sf::Text text("Score: ", font, 50);
    text.setFillColor(sf::Color::White);


    
    
    //Load inital screen
        window.clear();
        drawGrid(window);
        drawScore((window));
    
        convert(window);
    
        // Update the window
      //  window.display();

    while (window.isOpen()){
        
    sf:sleep(sf::seconds(0.05)); // Slows cpu from 100% to 1% :)
        
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::Resized){
                convert(window);
            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if(event.type == sf::Event::MouseButtonPressed){
                std::cout << "LEFT CLICK\n";
                std::cout << "x: " << event.mouseButton.x << std::endl;
                std::cout << "y: " << event.mouseButton.y << std::endl;
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                
                if(contains(loadGame, x, y) ) {
                        std::cout << "Load clicked!\n";
                        game.loadSave();
                        convert(window);
                    }
                if(contains(saveGame, x, y)){
                    std::cout << "Save clicked!\n";
                    game.saveGame();
                    convert(window);
                }
                
                if(contains(newGame, x,y)){
                    game.clear();
                    convert(window);

                }
                
                
                
                

            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if(game.playing){
                    std::cout << "Playing game currently\n";
                }else{
                    std::cout << "Resarting game...\n";
                    game.clear();
                    convert(window);
                }
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                handleInput(2, window);
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                handleInput(3, window);
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                handleInput(0, window);
            }
          
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                handleInput(1, window);
            }
            
            
        }

       
    }


    return EXIT_SUCCESS;
}
