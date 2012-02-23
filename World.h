#ifndef WORLD_H
#define WORLD_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

//world object
struct aBody {
    b2BodyDef DEF;
    b2PolygonShape SHAPE;
    b2FixtureDef FIX;
    b2Body * BOD;
	sf::RectangleShape RECT;
};

//place holders for picture files
//SFML Stuff
struct LevelResources {
	sf::Image img_background;
	sf::Image img_player;
};

class World {
private:
	LevelResources res[1]; //only one "level"
	//Box2D stuff
	b2World *world;
	b2Vec2 gravity;
	float timeStep;
    int velocityIterations;
    int positionIterations;
public:
	//con/destructors
	World();
	~World();
	//mutators
	void setWorld(b2World aWorld);
	//accessors
	b2World *getb2World(); 
	float getTimeStep();
	int getVIterations();
	int getPIterations();
	LevelResources &getRes(int index); //return res[index]
};

#endif