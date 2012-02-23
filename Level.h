#ifndef LEVEL_H
#define LEVEL_H

#include "World.h"
#include "Player.h"
#include "main.h"

//forward declaration
class Player;

class Level {
private:
	//sf::Sprite background; //load from World
	aBody wallsFloorCeiling[4]; //place holder for walls floor and ceiling
	aBody platforms[7]; //place holder for platforms
	b2World *world;
	Player *thePlayer;
	sf::Texture backgTexture;
	sf::RectangleShape background; 
public:
	//con/destructor
	Level(b2World *aWorld, Player *player, sf::Image &image);
	~Level(); 
	//mutators
	void input(sf::Event events);
	void createWallsFloorCeiling(); //to create walls floor and ceiling
	//these are generaic functions i will use to create the walls and floor; 
	void createHBorder(aBody &body, float xpos, float ypos, 
		              float xorigin, float yorigin, sf::Color fill);
	void createVBorder(aBody &body, float xpos, float ypos, 
		              float xorigin, float yorigin, sf::Color fill);
	//create things to step on. idealy could combine these two with the upper two
	//but i figure platforms could be seperated based on functionality, so
	//the properties could be different, or at some point i may pass different
	//types of properties to platforms.
	void createPlatforms();
	void createHPlatform(aBody &body, float xpos, float ypos, 
		              float xorigin, float yorigin, sf::Color fill);
	void createVPlatform(aBody &body, float xpos, float ypos, 
		              float xorigin, float yorigin, sf::Color fill);
	//not used
	void addPlayer(Player *aPlayer);	   
	//draw and update everything
	void draw();
	void update();
	//accessors 
};

#endif