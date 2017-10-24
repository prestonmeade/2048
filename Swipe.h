#ifndef SWIPE_H
#define SWIPE_H

class Swipe{
  private:

  public:
    Swipe();
    int board[4][4];
    int rows;
    int cols;
    int score;
    bool playing;
    bool moved;

    void up();
    void down();
    void right();
    void left();

    void clear();
    void move(int x1, int y1, int x2, int y2);
    void combine(int x1, int y1, int x2, int y2);
    bool isOpen(int x, int y);
    int get(int x, int y);
    void spawn();
    void print();

    void fill(int empty);




};




#endif
