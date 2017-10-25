#ifndef SWIPE_H
#define SWIPE_H

#include <string.h>
#include <iostream>
#include "ResourcePath.hpp"

class Swipe{
  private:

  public:
    Swipe();
    
    
    int board[4][4];
    int rows;
    int cols;
    
    int score;
    int hiscore;
    
    bool playing;
    bool moved;

    void up();
    void down();
    void right();
    void left();

    void clear();
    void move(int x1, int y1, int x2, int y2);
    bool combine(int x1, int y1, int x2, int y2);
    bool isOpen(int x, int y);
    int get(int x, int y);
    bool checkEnd();
    void spawn();
    void print();
    bool over();
    void fill(int empty);
    void fillTest();
    void promptNewRound();
    
    void save();
    int load();
    void loadSave();
    void saveGame();
    


};




#endif
