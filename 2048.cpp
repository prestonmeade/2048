//Preston Meade
// October 24th 2017
#include<iostream>
#include "Swipe.h"

using namespace std;

int main(){

  Swipe game;

  game.print();


  string cmd;
  while(cmd != "q"){
    getline(cin, cmd);
    if(cmd == "s"){
      game.down();
      game.spawn();

      game.print();
    }else if(cmd == "w"){
      game.up();
      game.spawn();

      game.print();
    }else if(cmd == "a"){
      game.left();
      game.spawn();

      game.print();
    }else if(cmd == "d"){
      game.right();
      game.spawn();

      game.print();
    }

  }

  return 0;
}
