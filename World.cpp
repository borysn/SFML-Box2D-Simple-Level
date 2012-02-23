#include "World.h"

//constructor
World::World() {
	gravity = b2Vec2(0.f, 9.8f);
	world = new b2World(gravity);
	timeStep = 1.0f / 180.0f;
    velocityIterations = 8;
    positionIterations = 3;
	//set resources
	res[0].img_background.LoadFromFile("../res/hmm.jpg");
	res[0].img_player.LoadFromFile("../res/player.png");
}

//mutators
void World::setWorld(b2World aWorld) {
//	world = aWorld;
}

//accessors
b2World *World::getb2World() {
	return world;
}

float World::getTimeStep() {
	return timeStep;
}

int World::getVIterations() {
	return velocityIterations;
}

int World::getPIterations() {
	return positionIterations;
}

LevelResources &World::getRes(int index) {
	return res[index];
}

//destructor
World::~World() {
	world = NULL;
	delete world;
	//delete res;
}
