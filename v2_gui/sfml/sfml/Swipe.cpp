#include "Swipe.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

using namespace std;

Swipe::Swipe(){
  srand (time(NULL));
  //cout << "new game" << endl;
  rows = 4;
  cols = 4;
  moved = true;

    hiscore = load();

    clear();

   // fillTest();


}

void Swipe::clear(){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      board[i][j] = 0;
    }
  }
    score = 0;
    moved = true;
    spawn();
    moved = true;
    spawn();
    playing = true;
    
    save();

}

bool Swipe::over(){
    return checkEnd();
}

void Swipe::right(){
    bool combined = false;

  for(int r = 0; r < rows; r++){
    for(int c = cols - 1; c >= 0; c-- ){
      //cout << "checking r: " << r << " c: " << c << endl;
      //cout << "value is: " << board[r][c] << endl;

      if(!isOpen(r,c)){
      bool canMove = isOpen(r,c + 1);
      int i = 0;

      if(!canMove){
          cout << "trying to comvindd " << endl;
           combine(r , c  + i, r, c + 1 + i);
          cout << "DID COMBINE? " << combined << endl;

      }
      //cout << "can move: " << canMove << endl;
      while(canMove){
        move(r,c + i,r,c + 1 + i);
        i++;
        canMove = isOpen(r,c + 1 + i);
        if(!canMove && !combined){
            cout << "trying to comvindd " << endl;

         combined =  combine(r , c  + i, r, c + 1 + i);
            cout << "DID COMBINE? " << combined << endl;

        }
      //  cout << "can move: " << canMove << endl;
        }
      }
  }
  }
}


void Swipe::left(){
    bool combined = false;

  for(int r = 0; r < rows; r++){
    for(int c = 1; c < cols; c++ ){
    //  cout << "checking r: " << r << " c: " << c << endl;
    //  cout << "value is: " << board[r][c] << endl;

      if(!isOpen(r,c)){
        int i = 0;

      bool canMove = isOpen(r,c - 1) ;
      if(!canMove){
          cout << "trying to comvindd " << endl;
          
         combine(r , c  - i, r, c - 1 - i);
          cout << "DID COMBINE? " << combined << endl;

      }
    //  cout << "can move: " << canMove << endl;
      while(canMove){
        move(r,c - i,r,c - 1 - i);
        i++;
        canMove = isOpen(r,c - 1 - i);

        if(!canMove && !combined){
            cout << "trying to comvindd " << endl;
            
            combined = combine(r , c  - i, r, c - 1 - i);
            cout << "DID COMBINE? " << combined << endl;
        }
      //  cout << "can move: " << canMove << endl;
        }
      }
  }
  }
}

void Swipe::up(){
    bool combined = false;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++ ){
    //  cout << "checking r: " << r << " c: " << c << endl;
    //  cout << "value is: " << board[r][c] << endl;

            if(!isOpen(r,c)){
                int i = 0;

      bool canMove = isOpen(r - 1,c);
      if(!canMove ){
          cout << "trying to comvindd " << endl;

        combine(r - i, c, r - i - 1, c);
          cout << "DID COMBINE? " << combined << endl;

      }
    //  cout << "can move: " << canMove << endl;
      while(canMove){
        move(r - i,c,r - 1 - i,c);
        i++;
        canMove = isOpen(r - 1 - i,c );
        if(!canMove && !combined){
             cout << "trying to comvindd " << endl;
            combined = combine(r - i, c, r - i - 1, c);
            cout << "DID COMBINE? " << combined << endl;
        }
      //  cout << "can move: " << canMove << endl;
        }
      }
  }
  }
}

void Swipe::down(){
    bool combined = false;
  for(int r = rows - 1; r >= 0; r--){
    for(int c = 0; c < cols; c++ ){


      if(!isOpen(r,c)){ // we are dealing with a tile!
      bool canMove = isOpen(r + 1,c); // check if it can move down one spot
      int i = 0;
          
          cout << "Can move? " << canMove << endl;
          cout << "At: " << r << "  " << c << endl;

      if(!canMove ) { // if we cant move, check if we can combinde!
          cout << "trying to comvindd " << endl;
           combined =  combine(r + i, c, r + i + 1, c);
          cout << "DID COMBINE? " << combined << endl;
      }
          
      // cout << "can move: " << canMove << endl;
      while(canMove){
        move(r + i,c,r + 1 + i,c);
        i++;
        canMove = isOpen(r + 1 + i,c );
        if(!canMove && !combined){
            cout << "trying to comvindd " << endl;
          combined = combine(r + i, c, r + i + 1, c);
            cout << "DID COMBINE? " << combined << endl;
        }
        //cout << "can move: " << canMove << endl;
        }
      }
  }
  }
}

bool Swipe::combine(int x1, int y1, int x2, int y2){
    bool c = false;
  if(x1 < rows && x2 < rows && y1 < cols && y2 < cols){
    if(x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0){
  //  cout << "COMBINE " << board[x1][y1] << " " << board[x2][y2] << endl;
    if( board[x1][y1] == board[x2][y2] && !c){
      board[x2][y2] += board[x1][y1];
      score += board[x1][y1] * 2;
        cout << "COMBINDED! " << endl;
        c = true;
        if(score > hiscore){
            hiscore = score;
            save();
        }
        

      board[x1][y1] = 0;
      moved = true;
    //  cout << "MOVED SET to true" << endl;
      }
    }
  }
    return c;
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
      int v = rand() % 2;
      if(v == 0){
          v = 2;
      }else{
          v = 4;
      }
  while(!isOpen(x,y)){
    x = rand() % 4;
    y = rand() % 4;
  }
    board[x][y] = v;
     
      if(checkEnd()){
          cout << "Game over, no moves left \n";
          playing = false;
          promptNewRound();
      }
  }else{
    cout << "no tiles moved... cant not spawn" << endl;
      if(checkEnd()){
          cout << "No moves.. play again? clear game board?" << endl;
          playing = false;
          promptNewRound();

      }
  }

  moved = false;

}

void Swipe::promptNewRound(){
    cout << "play new round?" << endl;
}

int Swipe::get(int x, int y){
    if(x < rows && x < rows && x >= 0 && y >= 0){
            return board[x][y];
    }
}

bool Swipe::checkEnd(){
    bool move = false;
    bool open = false;
    
    for(int i = 0; i < rows; i++){
        if(open == false){
        for (int j = 0; j < cols; j++){
            if(isOpen(i, j)){
                open = true;
                break;
                }
            }
        }
    }
    if(!open){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int cur = get(i,j);
            
            if(j <= 2 && !move){ // checks right tile
                int right = get(i, j + 1);
                move = (right == cur);
                cout << "Checking " << i << " " << j << " value: " << get(i,j) << endl;
                cout << "Compare  " << i << " " << j + 1 << "value: " << get(i,j +1) << endl;
        }
            
            if(i <= 2 && !move){ // checks tile below
                int down = get(i + 1, j);
                move = (down == cur);
                cout << "\nChecking " << i << " " << j << " value: " << get(i,j) << endl;
                cout << "Compare  " << i << " " << j + 1 << "value: " << get(i,j +1) << "\n"<< endl;

                }
            }
        }
    }
    
    cout << "open: " << open << " move: " << move << std::endl;
    
    return !open && !move;
    
}
void Swipe::fillTest(){
    int value = 2;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = value;
            if( value < 4096){
                value *= 2;
            }else{
                value = 2;
            }
        }
    }
    
}
void Swipe::fill(int emptySpots){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      board[i][j] = 2;
    }
  }
  board[0][0] = 0;
}

void Swipe::save(){
    cout << "saving..." << endl;
    ofstream file;
    file.open(resourcePath() + "data.txt");

    if(file.is_open()){
        cout << "file loaded" << endl;
    }
    file << hiscore;
    
    file.close();
}

int Swipe::load(){
    cout << "loading..\n";
    ifstream file;
    file.open(resourcePath() + "data.txt");
    if(file.is_open()){
        cout << "file loaded\n";
    }
    int found_score;
    file >> found_score;
    cout << "found hiscore of: " << found_score << endl;
    file.close();
    
    return found_score;
}

void Swipe::saveGame(){
    cout << "saving game state..." << endl;
    ofstream file;
    
    file.open(resourcePath() + "map.txt");
    
    
    if(file.is_open()){
        cout << "file loaded" << endl;
    }
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            file << board[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
    
    cout << "succesfully saved game\n";
}
void Swipe::loadSave(){
    int v;
    string line;
    ifstream file(resourcePath() + "map.txt");
    int j = 0;
    
    int i = 0;
        while( getline(file, line)){
           
            cout << line << endl;
            stringstream ss(line);
            while( ss >> v){
                cout << v << " x: " << i << " y: " << j << endl;
                board[i][j] = v;
                j++;
            }

            i++;
            j = 0;
        }
      
    
    print();
    
}

void Swipe::print(){
  cout << "---------------------------" << endl;
  cout << "Score:   " << score << endl;
  cout <<   "Hiscore: " << hiscore << endl;

  cout << "---------------------------\n" << endl;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      cout << "   " << board[i][j] << "   ";
    }
    cout << "\n\n\n";
  }
}
