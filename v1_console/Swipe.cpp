#include "Swipe.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>


using namespace std;

Swipe::Swipe(){
  srand (time(NULL));

  //cout << "new game" << endl;
  rows = 4;
  cols = 4;
  moved = true;

  clear();

  spawn();
  moved = true;
  spawn();

}

void Swipe::clear(){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      board[i][j] = 0;
    }
  }
  score = 0;
}

void Swipe::right(){
  for(int r = 0; r < rows; r++){
    for(int c = cols - 1; c >= 0; c-- ){
      //cout << "checking r: " << r << " c: " << c << endl;
      //cout << "value is: " << board[r][c] << endl;

      if(!isOpen(r,c)){
      bool canMove = isOpen(r,c + 1);
      int i = 0;

      if(!canMove){
        combine(r , c  + i, r, c + 1 + i);
      }
      //cout << "can move: " << canMove << endl;
      while(canMove){
        move(r,c + i,r,c + 1 + i);
        i++;
        canMove = isOpen(r,c + 1 + i);
        if(!canMove){
          combine(r , c  + i, r, c + 1 + i);
        }
      //  cout << "can move: " << canMove << endl;
        }
      }
  }
  }
}


void Swipe::left(){
  for(int r = 0; r < rows; r++){
    for(int c = 1; c < cols; c++ ){
    //  cout << "checking r: " << r << " c: " << c << endl;
    //  cout << "value is: " << board[r][c] << endl;

      if(!isOpen(r,c)){
        int i = 0;

      bool canMove = isOpen(r,c - 1);
      if(!canMove){
        combine(r , c  - i, r, c - 1 - i);
      }
    //  cout << "can move: " << canMove << endl;
      while(canMove){
        move(r,c - i,r,c - 1 - i);
        i++;
        canMove = isOpen(r,c - 1 - i);

        if(!canMove){
          combine(r , c  - i, r, c - 1 - i);
        }
      //  cout << "can move: " << canMove << endl;
        }
      }
  }
  }
}

void Swipe::up(){
  for(int r = 0; r < rows; r++){
    for(int c = 0; c < cols; c++ ){
    //  cout << "checking r: " << r << " c: " << c << endl;
    //  cout << "value is: " << board[r][c] << endl;

      if(!isOpen(r,c)){
        int i = 0;

      bool canMove = isOpen(r - 1,c);
      if(!canMove){
        combine(r - i, c, r - i - 1, c);
      }
    //  cout << "can move: " << canMove << endl;
      while(canMove){
        move(r - i,c,r - 1 - i,c);
        i++;
        canMove = isOpen(r - 1 - i,c );
        if(!canMove){
          combine(r - i, c, r - i - 1, c);
        }
      //  cout << "can move: " << canMove << endl;
        }
      }
  }
  }
}

void Swipe::down(){
  for(int r = rows - 1; r >= 0; r--){
    for(int c = 0; c < cols; c++ ){
    //  cout << "checking r: " << r << " c: " << c << endl;
    //  cout << "value is: " << board[r][c] << endl;

      if(!isOpen(r,c)){
      bool canMove = isOpen(r + 1,c);
      int i = 0;

      if(!canMove){
        combine(r + i, c, r + i + 1, c);
      }
      // cout << "can move: " << canMove << endl;
      while(canMove){
        move(r + i,c,r + 1 + i,c);
        i++;
        canMove = isOpen(r + 1 + i,c );
        if(!canMove){
          combine(r + i, c, r + i + 1, c);
        }
        //cout << "can move: " << canMove << endl;
        }
      }
  }
  }
}

void Swipe::combine(int x1, int y1, int x2, int y2){
  if(x1 < rows && x2 < rows && y1 < cols && y2 < cols){
    if(x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0){
  //  cout << "COMBINE " << board[x1][y1] << " " << board[x2][y2] << endl;
    if( board[x1][y1] == board[x2][y2]){
      board[x2][y2] += board[x1][y1];
      score += board[x1][y1] * 2;

      board[x1][y1] = 0;
      moved = true;
    //  cout << "MOVED SET to true" << endl;
      }
    }
  }
}

bool Swipe::isOpen(int x, int y){
  return (board[x][y] == 0);
}

void Swipe::move(int x1, int y1, int x2, int y2){
  if(x1 < rows && x2 < rows && y1 < cols && y2 < cols){
    if(x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0){

    int temp = board[x1][y1];
    board[x2][y2] = temp;
    board[x1][y1] = 0;

  //  cout << "moving from " << x1 << "," << y1 << " to " << x2 << "," << y2 << endl;
    moved = true;
  //  cout << "MOVED SET to true" << endl;

    }

  }
}


void Swipe::spawn(){
  if(moved){
  int x = rand() % 4;
  int y = rand() % 4;
  while(!isOpen(x,y)){
    x = rand() % 4;
    y = rand() % 4;
  }
    board[x][y] = 2;
  //  cout << "spawened at: " << x << " " << y << endl;
  }else{
    cout << "no tiles moved... cant not spawn" << endl;
  }

  moved = false;

}

void Swipe::fill(int emptySpots){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      board[i][j] = 2;
    }
  }
  board[0][0] = 0;
}

void Swipe::print(){
  cout << "---------------------------" << endl;
  cout << "Score: " << score << endl;
  cout << "---------------------------\n" << endl;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      cout << "   " << board[i][j] << "   ";
    }
    cout << "\n\n\n";
  }
}
