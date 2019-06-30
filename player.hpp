/**
  Author:Shikun Lin
  18W CIS330 project
  This is player.hpp for player.cpp and main.cpp
  
**/
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <SDL2/SDL.h>
#include <vector>

using namespace std;


class Player{
public:
  Player( SDL_Renderer* screen );	//constructor for player
  ~Player(){};
  //draw the player on window
  void draw( SDL_Renderer* screen );
  //getter for playerHeight and playerWidth
  void getPlayerDem( int &h,int &w );
  //getter for position
  void getPos( int &curx, int &cury );
  //setter for position
  void setPos( int &newx, int &newy );
  //this function can check wether player collision with enemys or not.
  void collisionWithEnemy( vector < SDL_Rect > &enemys, bool &collisionE );
  //getter for life
  void getLifes( int &lifes );
  //reset the position for player
  void reset();

private:
  SDL_Rect position;	//position for player
  SDL_Surface* playerSurface; 	
  int playerWidth;
  int playerHeight;
  int life;		//number of lifes for player
  SDL_Texture* playerTex;
};


#endif
