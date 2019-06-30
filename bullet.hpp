/**
  Author:Shikun Lin
  18W CIS330 project
  This is bullet.hpp for bullet.cpp and main.cpp

**/
#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
using namespace std;

class Bullet{
public:
  //constructor for Bullet class
  Bullet( SDL_Renderer* screen );
  ~Bullet(){};
  //draw the bullets on window
  void draw( SDL_Renderer* screen );
  //add rect to rects
  void addRect( int &cx, int &cy );
  //move every rect from rects
  void move();
  //remove the rect which out of window
  void removeRect();
  //getter for rects
  void getBulletRects( vector < SDL_Rect > &rv );
  //reset rects by clearing contents
  void reset();


private:
  SDL_Surface* bulletSurface;
  int bulletWidth;
  int bulletHeight;
  int rectSize;
  SDL_Texture* bulletTex;
  vector < SDL_Rect > rects;
};




#endif
