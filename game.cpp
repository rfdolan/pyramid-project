//
// PYRAMID - solve the maze to escape the mummy guardians!
//
// v2.1
// 

// System includes.
#include <stdlib.h>		// for rand()

// Engine includes.
#include "DisplayManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Vector.h"
#include "WorldManager.h"

// Game includes.
#include "Ankh.h"
#include "Exit.h"
#include "Health.h"
#include "Hero.h"
#include "Mummy.h"
#include "Timer.h"
#include "Wall.h"

// Function prototypes.
void loadResources();
void populateWorld();
void placeObject(df::Object *p_o);

int main(void){ 

  // Seed random number generator in case engine does not.
  srand((unsigned int)time(NULL));

  // Start up Dragonfly.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    exit(1);
  }

  // Turn on flush while debugging.
  LM.setFlush();

  // Load resources.
  loadResources();

  // Populate world.
  populateWorld();

  // Setup HUD.
  new Timer;
  new Health;

  // Run game.
  GM.run();

  // Shut everything down.
  GM.shutDown();
}

// Load game resources.
void loadResources() {
  RM.loadSprite("sprites/mummy-cower-spr.txt", "mummy-cower");
  RM.loadSprite("sprites/mummy-white-spr.txt", "mummy-white");
  RM.loadSprite("sprites/mummy-yellow-spr.txt", "mummy-yellow");
  RM.loadSprite("sprites/mummy-red-spr.txt", "mummy-red");
  RM.loadSprite("sprites/ankh-spr.txt", "ankh");
  RM.loadSprite("sprites/walk-spr.txt", "walk");
  RM.loadSprite("sprites/exit-spr.txt", "exit");
}

// Populate world with game objects.
void populateWorld() {

  // World dimensions (X,Y).
  float X = WM.getBoundary().getHorizontal();
  float Y = WM.getBoundary().getVertical();

  // Place outer Walls.
  Wall *p_wall;
  p_wall = new Wall((int) X, 1);
  p_wall -> setPosition(df::Vector(X/2.0f,1));
  p_wall = new Wall((int) X, 1);
  p_wall -> setPosition(df::Vector(X/2.0f,Y-1));
  p_wall = new Wall(1, (int) Y-1);
  p_wall -> setPosition(df::Vector(0,Y/2.0f));
  p_wall = new Wall(1, (int) Y-1);
  p_wall -> setPosition(df::Vector(X-1,Y/2.0f));

  // Place random Walls.
  for (int i=0; i<WALL_COUNT; i++)
    placeObject(new Wall(2,2));
  for (int i=0; i<WALL_COUNT/2; i++)
    placeObject(new Wall(3,3));
  for (int i=0; i<WALL_COUNT/4; i++)
    placeObject(new Wall(4,4));
  
  // Place Exit.
  Exit *p_exit = new Exit;
  df::Vector exit_pos(X-4, Y-3);	// Bottom right corner.
  p_exit -> setPosition(exit_pos);

  // Place Ankhs.
  for (int i=0; i<ANKH_COUNT; i++)
    placeObject(new Ankh);

  // Place Hero.
  Hero *p_hero = new Hero;
  df::Vector hero_pos(4, 4);	// Top left corner.
  p_hero -> setPosition(hero_pos);

  // Place Mummies.
  for (int i=0; i<MUMMY_COUNT; i++)
    placeObject(new Mummy(p_hero));
}

// Randomly place Object, making sure no collision.
void placeObject(df::Object *p_o) {

  // World dimensions (X,Y).
  int X = (int) WM.getBoundary().getHorizontal();
  int Y = (int) WM.getBoundary().getVertical();

  // Repeat until random (x,y) doesn't have collision for Object.
#ifdef USE_STL
  std::vector<Object *> collision_list;
  df::Vector pos;
  do {
    float x = (float) (rand() % (X-8) + 4);
    float y = (float) (rand() % (Y-4) + 2 + 1);
    pos.setXY(x, y);
    collision_list = WM.getCollisions(this, temp_pos);
  } while (!collision_list.empty);
#else
  df::ObjectList collision_list;
  df::Vector pos;
  do {
    float x = (float) (rand() % (X-8) + 4);
    float y = (float) (rand() % (Y-4) + 2 + 1);
    pos.setXY(x, y);
    collision_list = WM.getCollisions(p_o, pos);
  } while (!collision_list.isEmpty());
#endif
  
  // Set position.
  p_o->setPosition(pos);
}
