/**
  Author:Shikun Lin
  18W CIS330 project
  This is player.cpp which contain all functions
  for the player class.
  

**/
#include "player.hpp"
#include <SDL2/SDL.h>

using namespace std;

//constructor for Player class. It set the orignail position for 
//player's plane and default width and height. And set the life
//to 3. Loading image for player.
Player::Player( SDL_Renderer* screen ){
  playerSurface = SDL_LoadBMP("player.bmp");
  playerTex = SDL_CreateTextureFromSurface( screen,playerSurface );
  playerWidth = 40;
  playerHeight = 40;
  life = 3;
  position.x = 300 - playerWidth/2;
  position.y = 800 - playerHeight;
  position.w =  playerWidth;
  position.h  = playerHeight;

}

//draw function can draw the player's plane on window
void Player::draw( SDL_Renderer* screen ){
  SDL_RenderCopy( screen, playerTex, NULL, &position );


}

//this function can check wether player collision with enemys or not.
void Player::collisionWithEnemy( vector < SDL_Rect > &enemys, bool &collisionE ){
  int i;
  int size = enemys.size();
  for ( i = 0; i < size; i++ ){
    SDL_bool collision = SDL_HasIntersection(&enemys[i], &position);
    if (collision){
        life--;
        collisionE = true;
      }
  }
}

//reset player to orginal position
void Player::reset(){
  position.x = 300 - playerWidth/2;
  position.y = 800 - playerHeight;
}

//getter for life
void Player::getLifes( int &lifes ){
  lifes = this->life;
}

//setter for position
void Player::setPos( int &newx, int &newy ){
  this->position.x = newx;
  this->position.y = newy;
}

//getter for playerHeight and playerWidth
void Player::getPlayerDem( int &h, int &w ){
  h = this->playerHeight;
  w = this->playerWidth;
}

//getter for position
void Player::getPos( int &curx, int &cury ){
  curx = this->position.x;
  cury = this->position.y;
};
