/**
  Author:Shikun Lin
  18W CIS330 project

  This is bullet.cpp for the project. And it contain all
  function for bullet class.

**/
#include "bullet.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
using namespace std;

//This is constructor for Bullet class
Bullet::Bullet( SDL_Renderer* screen ){
  bulletSurface = SDL_LoadBMP("bullet.bmp");
  bulletTex = SDL_CreateTextureFromSurface( screen,bulletSurface );
  bulletWidth = 10;
  bulletHeight = 10;
  rectSize = 0;

}
//This function can add rect to rects
void Bullet::addRect( int &cx, int &cy ){
  SDL_Rect rect;
  rect.x = cx;
  rect.y = cy;
  rect.w = bulletWidth;
  rect.h = bulletHeight;
  rects.push_back( rect );
  rectSize = rects.size();

}
//It can draw the bullets on window
void Bullet::draw( SDL_Renderer* screen ){
  if ( rectSize != 0 ){
    int i;
    int size = rectSize;
    for ( i = 0; i < size; i++){
      SDL_RenderCopy( screen, bulletTex, NULL, &rects[i] );
    }
  }

}

//getter for rects
void Bullet::getBulletRects( vector < SDL_Rect > &rv ){
  rv = this->rects;


}
//reset by clearing the contents of rects
void Bullet::reset(){
  rects.clear();
  rectSize = rects.size();


}

//move every rect from rects
void Bullet::move(){
  if ( rectSize != 0 ){
    int i;
    int size = rectSize;
    for ( i = 0; i < size; i++){
      rects[i].y = rects[i].y - 5;
    }
  }
}

//erase the rect from rects if the rect out
//of the window, and update the rectSize
void Bullet::removeRect(){
  if (rectSize != 0){
    int i;
    int size = rectSize;
    for ( i = 0; i < size; i++){
      if ( rects[i].y < 0 ){
        rects.erase(rects.begin() + i );
      }
    }
    rectSize = rects.size();

  }
}
