/**
  Author:Shikun Lin
  18W CIS330 project

  This is main.cpp,  and it contain main() function for the
  project. It include bullet.hpp, player.hpp and enemy.hpp.
  And it will create a window for the game. Also, geting inputs
  from users.

**/
#include "bullet.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;


#define fps 60    //this is frame per second for the game
int main( int argc, char* argv[] ){
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Window* window = SDL_CreateWindow( "Plane Master", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,600,800,
                            SDL_WINDOW_SHOWN ); //make the game run as window

  SDL_Renderer* screen = SDL_CreateRenderer( window,-1,SDL_RENDERER_ACCELERATED );
  srand( time( NULL ) );

  SDL_Surface* overSurface = SDL_LoadBMP("gameover.bmp");
  SDL_Texture* overTex = SDL_CreateTextureFromSurface( screen, overSurface );
  SDL_Rect overRect;
  overRect.x = 100;
  overRect.y = 200;
  overRect.w =  400;
  overRect.h  = 400;


  int playerw;    //holder for player's plane width
  int playerh;    //holder for player's plane height
  int playerCurx; //holder for player's current x on window
  int playerCury; //holder for player's current y on windwo
  int lifes;    //holder for player's chances
  int i;
  int lo = 0;
  int timer = 100;
  int period = 2000;    //holder for add new enemys
  int increLevel = 0;
  int num = 4;
  int credits;   //holder for credits which player got
  bool collisionE = false;
  vector < pair <int,int> > initLocation;   //holder for initial location for enmeys
  vector < SDL_Rect > EnemyRects; //holder for enemys' rects
  vector < SDL_Rect > BulletRects;  //holder for bullets' rect

  //initialize the value for initLocation
  for ( i = 0; i < 20; i++ ){
    pair <int,int> pas;
    pas.first = lo;
    pas.second = 0;
    initLocation.push_back(pas);
    lo += 30;
  }


  Enemy enemys( screen );
  enemys.setLocations( initLocation );
  Player player( screen );
  Bullet bullets( screen );
  Uint32 starting_tick;
  Uint32 tick;
  SDL_RenderClear( screen );

  SDL_Event event;    //event for users
  bool running = true;
  tick = SDL_GetTicks();

  while( running ){
    starting_tick = SDL_GetTicks();

    if (SDL_PollEvent( &event )){
      if(event.type == SDL_QUIT){
        running = false;
        break;
      }
      //get users input and change the location for player on window
      else if ( event.type == SDL_KEYDOWN ){
        player.getPos( playerCurx,playerCury );
        player.getPlayerDem( playerh,playerw );
        if ( event.key.keysym.sym == SDLK_w ){
          if( playerCury > 19 ){
            playerCury -= 20;
            player.setPos(playerCurx,playerCury);
          }

        }
        if ( event.key.keysym.sym == SDLK_s ){
          if( ( playerCury + playerh ) < 781 ){
            playerCury += 20;
            player.setPos(playerCurx,playerCury);
          }
        }
        if ( event.key.keysym.sym == SDLK_a ){
          if ( playerCurx > 19 ){
            playerCurx -= 20;
            player.setPos(playerCurx,playerCury);
          }

        }
        if ( event.key.keysym.sym == SDLK_d ){
          if( (playerCurx + playerw) < 581 ){
            playerCurx += 20;
            player.setPos(playerCurx,playerCury);
          }

        }
        if( event.key.keysym.sym == SDLK_SPACE ){
          int cx = playerCurx + 15;
          int cy = playerCury;
          bullets.addRect( cx, cy );
          bullets.getBulletRects( BulletRects );
        }
      }
    }
    //set the delay
    if((1000/fps)>SDL_GetTicks()-starting_tick){
      SDL_Delay(1000/fps - ( SDL_GetTicks() - starting_tick ));

    }

    //for specific time, the hard level of game will increase by
    //increasing the number of enemys and decresing the period
    if ( SDL_GetTicks()-tick > timer ){
      enemys.addRect();
      timer+= period;
      increLevel++;
      if ( increLevel % 11 == 0 ){
        enemys.setNumEnemys(num);
        credits = 0;
        enemys.setCredits( credits );
        if ( num < 10 ){
          num++;
        }
        if ( period > 800 ){
          period = period - 100;
        }
      }
    }

    //get the enemys's rects and check whether player collision
    //with enemys or not
    enemys.getEnemyRects( EnemyRects );
    player.collisionWithEnemy( EnemyRects, collisionE );
    player.getLifes(lifes);

    //if collision with enmeys, reset the clear everthing on window and
    //reset the player to original position and make the hard level back
    //to first level
    if ( collisionE ){
      if ( lifes > 0 ){
        player.reset();
        enemys.reset();
        bullets.reset();
        num = 4;
        period = 2000;
        enemys.setNumEnemys(num);
        collisionE = false;
      }else{
        player.reset();
        enemys.reset();
        bullets.reset();
        SDL_RenderClear( screen );
        SDL_RenderCopy( screen, overTex, NULL, &overRect );
        SDL_RenderPresent( screen );
        SDL_Delay(5000);
        running = false;
        break;

      }

    }

    bullets.move();
    bullets.getBulletRects( BulletRects );
    bullets.removeRect();
    enemys.getCredits( credits );

    //check the credits player got, if over 25 increse the hard level
    if ( credits % 25 == 0 && credits != 0 ){
      if ( num < 10 ){
        num++;
      }
      if ( period > 800 ){
        period = period - 100;
      }
      increLevel = 1;
      enemys.setNumEnemys(num);
      credits = 0;
      enemys.setCredits( credits );
    }
    enemys.move( BulletRects );
    enemys.removeRect();


    SDL_RenderClear( screen );
    player.draw( screen );
    enemys.draw( screen );
    bullets.draw( screen );
    SDL_RenderPresent( screen );


  }

  SDL_DestroyWindow( window );

  SDL_Quit();

  return 0;


}
