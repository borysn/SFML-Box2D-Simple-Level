#include "Level.h"

//constructor
Level::Level(b2World *aWorld, Player *player, sf::Image &image) : world(aWorld), thePlayer(player) { 
	//	res = aRes;
	//backgTexture.LoadFromImage(res.img_background);
	//backgTexture.LoadFromFile("../res/back.jpg");
	backgTexture.LoadFromImage(image);
	background = sf::RectangleShape(sf::Vector2f((float)backgTexture.GetWidth(), (float)backgTexture.GetHeight()));
	background.SetTexture(&backgTexture);
	createWallsFloorCeiling();
	createPlatforms();
}

//mutators
void Level::input(sf::Event events) {
	thePlayer->input(events);
}

void Level::createWallsFloorCeiling() {
	//floor
	createHBorder(wallsFloorCeiling[0], (float)450, (float)600, (float)500, (float)25, 
		                                           sf::Color(200,75,20,255));
	//left wall
	createVBorder(wallsFloorCeiling[1], (float)12.5, (float)200, (float)25, (float)400, 
		                                           sf::Color(200,75,200,255));
	//right wall
	createVBorder(wallsFloorCeiling[2], (float)887.5, (float)200, (float)25, (float)400, 
		                                           sf::Color(100,205,20,255));
} 

//to create floor and ceiling
void Level::createHBorder(aBody &body, float xpos, float ypos, float xorigin, 
		                float yorigin, sf::Color fill) {
	body.DEF.position.Set(xpos/RATIO, ypos/RATIO);
	body.DEF.type = b2_staticBody;
	body.RECT = sf::RectangleShape(sf::Vector2f(xorigin*2,yorigin));
	body.RECT.SetOrigin(xorigin, yorigin/2);
	body.RECT.SetFillColor(fill);
    body.SHAPE.SetAsBox(xorigin/RATIO, (yorigin/2)/RATIO);
    body.FIX.shape = &body.SHAPE;
	body.FIX.density = .7f; 
	body.FIX.friction = .9f;
	body.BOD = world->CreateBody(&body.DEF);
    body.BOD->CreateFixture(&body.SHAPE,1.0f);
	//set position
	body.RECT.SetPosition(body.BOD->GetPosition().x*RATIO, body.BOD->GetPosition().y*RATIO);
}	   

//to create walls                  //300 800
void Level::createVBorder(aBody &body, float xpos, float ypos, float xorigin, 
		                float yorigin, sf::Color fill) {
	body.DEF.position.Set(xpos/RATIO, ypos/RATIO);
	body.DEF.type = b2_staticBody;
	body.RECT = sf::RectangleShape(sf::Vector2f(xorigin,yorigin*2));
	body.RECT.SetOrigin(xorigin/2, yorigin); 
	body.RECT.SetFillColor(fill);
    body.SHAPE.SetAsBox((xorigin/2)/RATIO,yorigin/RATIO);
    body.FIX.shape = &body.SHAPE;
	body.FIX.density = .7f;
	body.FIX.friction = .9f; 
	body.BOD = world->CreateBody(&body.DEF);
    body.BOD->CreateFixture(&body.SHAPE,1.0f);
	//set position 
	body.RECT.SetPosition(body.BOD->GetPosition().x*RATIO, body.BOD->GetPosition().y*RATIO);
}	

//to create platforms 
void Level::createPlatforms() {
	createHPlatform(platforms[0], (float)450, (float)425, (float)75, (float)25, 
		                                           sf::Color(250,75,20,255));
	createHPlatform(platforms[1], (float)600, (float)375, (float)75, (float)25, 
		                                           sf::Color(150,75,20,255));
	createHPlatform(platforms[2], (float)700, (float)100, (float)75, (float)25, 
		                                           sf::Color(200,75,200,255));
	createHPlatform(platforms[3], (float)250, (float)200, (float)75, (float)25, 
		                                           sf::Color(200,250,20,255));
	createVPlatform(platforms[4], (float)100, (float)600, (float)25, (float)75, 
		                                           sf::Color(200,75,150,255));
	createVPlatform(platforms[5], (float)200, (float)550, (float)25, (float)75, 
		                                           sf::Color(100,250,20,255));
	createVPlatform(platforms[6], (float)300, (float)450, (float)25, (float)75, 
		                                           sf::Color(100,75,100,255));
}

void Level::createHPlatform(aBody &body, float xpos, float ypos, float xorigin, 
		                float yorigin, sf::Color fill) {
	body.DEF.position.Set(xpos/RATIO, ypos/RATIO);
	body.DEF.type = b2_staticBody;
	body.RECT = sf::RectangleShape(sf::Vector2f(xorigin*2,yorigin));
	body.RECT.SetOrigin(xorigin, yorigin/2);
	body.RECT.SetFillColor(fill);
    body.SHAPE.SetAsBox(xorigin/RATIO,(yorigin/2)/RATIO);
    body.FIX.shape = &body.SHAPE;
	body.FIX.density = .5f;
	body.FIX.friction = 1.f; 
	body.BOD = world->CreateBody(&body.DEF);
    body.BOD->CreateFixture(&body.SHAPE,1.0f);
	//set position
	body.RECT.SetPosition(body.BOD->GetPosition().x*RATIO, body.BOD->GetPosition().y*RATIO);
}	   

//to create walls 
void Level::createVPlatform(aBody &body, float xpos, float ypos, float xorigin, 
		                float yorigin, sf::Color fill) {
	body.DEF.position.Set(xpos/RATIO, ypos/RATIO);
	body.DEF.type = b2_staticBody;
	body.RECT = sf::RectangleShape(sf::Vector2f(xorigin,yorigin*2));
	body.RECT.SetOrigin(xorigin/2, yorigin); 
	body.RECT.SetFillColor(fill);
    body.SHAPE.SetAsBox((xorigin/2)/RATIO,yorigin/RATIO);
    body.FIX.shape = &body.SHAPE;
	body.FIX.density = .5f;
	body.FIX.friction = 1.f; 
	body.BOD = world->CreateBody(&body.DEF);
    body.BOD->CreateFixture(&body.SHAPE,1.0f);
	//set position
	body.RECT.SetPosition(body.BOD->GetPosition().x*RATIO, body.BOD->GetPosition().y*RATIO);
}	

void Level::draw() {
	App.Draw(background);
	//draw floor and walls
	for (int i = 0; i < 7; i++) 
		App.Draw(platforms[i].RECT);
	for (int i = 0; i < 3; i++) 
		App.Draw(wallsFloorCeiling[i].RECT);
	thePlayer->draw();
}

void Level::addPlayer(Player *aPlayer) {
}

void Level::update() {
	thePlayer->update();
}

//accessors

//destructor
Level::~Level() {
	for (int i = 0; i < 7; i++) {
		platforms[i].BOD->DestroyFixture(platforms[i].BOD->GetFixtureList());
		world->DestroyBody(platforms[i].BOD);
	} for (int i = 0; i < 3; i++) { 
		wallsFloorCeiling[i].BOD->DestroyFixture(wallsFloorCeiling[i].BOD->GetFixtureList());
		world->DestroyBody(wallsFloorCeiling[i].BOD);
	}/**/
	//thePlayer = NULL;
	//world = NULL;
	//res = NULL;
	//delete res;
	//delete thePlayer;
	//delete world;
}
