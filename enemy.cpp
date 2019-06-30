/**
  Author:Shikun Lin
  18W CIS330 project
  This is enemy.cpp it contains all functions for Enemy
  class

**/
#include "enemy.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <time.h>
#include <stdlib.h>


using namespace std;

//constructor for Enemy. It sets image for enmeys, and width height and
//speed.
Enemy::Enemy( SDL_Renderer* screen ){
  enemySurface = SDL_LoadBMP("enemy.bmp");
  enemyTex = SDL_CreateTextureFromSurface( screen,enemySurface );
  enemyWidth = 30;
  enemyHeight = 30;
  speed = 2;
  rectSize = 0;
  numEnemys = 2;


}

//add rects with number of numEnemys
void Enemy::addRect(){
  vector < pair <int,int> > locas;
  locas = Locations;
  bool go = true;
  int count = 0;
  while ( go ){
    if ( count > numEnemys ){
      go = false;
      break;
    }
    int s = locas.size();
    int random = rand() % s;    //get random position for initial place
    SDL_Rect rect;
    rect.x = locas[random].first;
    rect.y = locas[random].second;
    rect.w =  enemyWidth;
    rect.h  = enemyHeight;
    locas.erase( locas.begin() + random );
    rects.push_back( rect );
    rectSize = rects.size();
    count++;
  }

}

//setter for numEnemys
void Enemy::setNumEnemys( int &num ){
  this->numEnemys = num;


}

//setter for Locations
void Enemy::setLocations( vector < pair <int,int> > &location ){
  this->Locations = location;
}
//getter for Locations
void Enemy::getLocations( vector < pair <int,int> > &location ){
  location = this->Locations;
}

//draw the rects on screen
void Enemy::draw( SDL_Renderer* screen ){
  int i;
  int size = rectSize;
  for ( i = 0; i < size; i++){
    SDL_RenderCopy( screen, enemyTex, NULL, &rects[i] );
  }
}

//remove the rect if out of window(screen)
void Enemy::removeRect(){
  int i;
  for ( i = 0; i < rectSize; i++){
    if ( rects[i].y > 820 ){
      rects.erase(rects.begin() + i );
    }
    rectSize = rects.size();
  }
}

//getter for rects
void Enemy::getEnemyRects( vector < SDL_Rect > &rv ){
  rv = this->rects;

}
//getter for credits
void Enemy::getCredits( int &credit ){
  credit = this->credits;
}

//setter for credits
void Enemy::setCredits( int &credit ){
  this->credits = credit;
}

//reset the rects by clear contents
void Enemy::reset(){
  rects.clear();
  rectSize = rects.size();
}

//move every rect in rects. Also, determine enemy collision
//with bullets
void Enemy::move( vector < SDL_Rect > &bullets ){
  int i;
  int j;
  int sizej = bullets.size();
  for ( i = 0; i < rectSize; i++){
    for ( j = 0; j < sizej; j++ ){
      SDL_bool collision = SDL_HasIntersection(&rects[i], &bullets[j]);
      if (collision){
          rects.erase(rects.begin() + i );
          rectSize = rects.size();
          credits++;
        }
    }
    rects[i].y += speed;
  }
}
