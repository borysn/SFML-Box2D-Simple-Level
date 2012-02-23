#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"

//namespace Game {
class Player {
private:
	bool right, left, down, up;
	float offset;
	aBody playerBody;
	b2World *world; 
	sf::Texture selfImage; //load from World
	float xpos;
	float ypos;
	float xorigin;
	float yorigin;
	sf::Color fill;
public:
	//con/destructors
	Player(b2World *aWorld, sf::Image &image); 
	~Player(); 
	//mutators
	void setup(b2World &aworld);
	//enacse the player with Box2D Dynamics
	void setSelfBox();
	void playerbump(); //bump off wall
	void input(sf::Event events); //move
	void draw();
	void SetPosition(float x, float y);
	void update();
	void jump(int dir);
	//accessors
};
//}

#endif