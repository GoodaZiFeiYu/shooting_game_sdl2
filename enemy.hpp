/**
  Author:Shikun Lin
  18W CIS330 project
  This is .hpp file for enemy.cpp and main.cpp
**/
#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include <SDL2/SDL.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;


class Enemy{
public:
  //constructor for Enemy
  Enemy( SDL_Renderer* screen );
  ~Enemy(){};

  //copy the rects to renderer
  void draw( SDL_Renderer* screen );
  //setter for Locations
  void setLocations( vector < pair <int,int> > &location );
  //getter for Locations
  void getLocations( vector < pair <int,int> > &location );
  //move every rects on renderer
  void move( vector < SDL_Rect > &bullets );
  //remove the rect from rects if out of window
  void removeRect();
  //add rect with specific size into rects
  void addRect();
  //getter for rects
  void getEnemyRects( vector < SDL_Rect > &rv );
  //getter for credits
  void getCredits( int &credit );
  //setter for numEnemys
  void setNumEnemys( int &num );
  //setter for credits
  void setCredits( int &credit );
  //reset the rects, clear all contents
  void reset();

private:
  SDL_Surface* enemySurface;
  int enemyWidth;
  int enemyHeight;
  int rectSize;     //size for rects
  int speed;    //move speed for enemys
  int credits;  //credits player got
  int numEnemys;    //specific number for every time enmeys' producing
  SDL_Texture* enemyTex;
  vector < SDL_Rect > rects;    //rects holder for all enemys
  vector < pair <int,int> > Locations;    //Locations for initial locations
};


#endif
