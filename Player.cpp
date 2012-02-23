#include "Player.h"

//con/destructors
Player::Player(b2World *aWorld, sf::Image &image) : world(aWorld) {
	selfImage.LoadFromImage(image);
	//selfimage.SetTexture(lw_assets.img_player);
	//selfimage.SetPosition(x, y);
	offset = gameTime * 0.3f; //?
	right = false;
	down = false;
	left = false; 
	up = false;
	//float xscale = selfimage.GetScale().x;
	//float yscale = selfimage.GetScale().y;
	xpos = 100;
	ypos = 100;
	xorigin = 20;
	yorigin = 40;
	fill = sf::Color(255,0,255,255);
	setSelfBox();
}

//mutators
void Player::setup(b2World &aworld) {
}

//enacse the player with Box2D Dynamics
void Player::setSelfBox() {
	playerBody.RECT = sf::RectangleShape(sf::Vector2f(xorigin*2,yorigin));//100-50? is size?
	playerBody.RECT.SetOrigin(xorigin, yorigin/2);
	//playerBody.RECT.SetFillColor(fill);
	playerBody.RECT.SetTexture(&selfImage);
	playerBody.DEF.position.Set(xpos/RATIO, ypos/RATIO);
	playerBody.DEF.type = b2_dynamicBody;
    playerBody.SHAPE.SetAsBox(xorigin/RATIO,(yorigin/2)/RATIO);
    playerBody.FIX.shape = &playerBody.SHAPE;
	playerBody.FIX.density = 1.f;
	playerBody.FIX.friction = .9f; 
	playerBody.BOD = world->CreateBody(&playerBody.DEF);
    playerBody.BOD->CreateFixture(&playerBody.SHAPE,1.0f);
}

void Player::playerbump() { //bump off wall
}

void Player::input(sf::Event events) { //move bools
	switch (events.Type) {
	case sf::Event::KeyPressed:
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))
			up = true;
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
			right = true;
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
			down = true;
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
			left = true;
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::R)) {
			xpos = 100;
			ypos = 100;
			SetPosition(xpos, ypos);
			//selfimage.SetPosition(x, y);
		} 
		//jump right
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space) && 
			sf::Keyboard::IsKeyPressed(sf::Keyboard::X)) {
			jump(1); 
		}
		//jump left
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space) && 
				 sf::Keyboard::IsKeyPressed(sf::Keyboard::Z)) {
			jump(2);
		}
		//jump up
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space)) {
			jump(3);
		}
	break;
	case sf::Event::KeyReleased:
		if (!sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))
			up = false;
		if (!sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
			right = false;
		if (!sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
			down = false;
		if (!sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
			left = false;
	break;
	}
} 

void Player::draw() {
	//set position for SFML drawing on screen
	App.Draw(playerBody.RECT);
}

void Player::update() {
	xpos = playerBody.BOD->GetPosition().x;
	ypos = playerBody.BOD->GetPosition().y;
	if (right == true && left == false) {
		//xpos += 5;
		//SetPosition(xpos, ypos);
		//playerBody.BOD->SetAngularVelocity(0);
		playerBody.BOD->SetLinearVelocity(b2Vec2(1, 0));
	} else if (right == false && left == true) {
		//xpos -= 5;
		//SetPosition(xpos, ypos);
		//playerBody.BOD->SetAngularVelocity(0);
		playerBody.BOD->SetLinearVelocity(b2Vec2(-1, 0));
	} /*(else if (up == true && down == false) {
		ypos -= offset;
		SetPosition(xpos, ypos);
	} else if (up == false && down == true) {
		ypos += offset;
		SetPosition(xpos, ypos);
	}*/ else {
		playerBody.RECT.SetPosition(xpos*RATIO, ypos*RATIO);
	}
	//playerBody.RECT.SetPosition(playerBody.BOD->GetPosition().x*RATIO, playerBody.BOD->GetPosition().y);
}

void Player::SetPosition(float x, float y) {
	xpos = x;
	ypos = y;
	//update position settings for Box2D
	playerBody.BOD->DestroyFixture(playerBody.BOD->GetFixtureList());
	world->DestroyBody(playerBody.BOD);
	playerBody.DEF.position.Set(xpos/RATIO, ypos/RATIO-1*5/RATIO);
	//playerBody.DEF.angularVelocity = 0;
	//playerBody.DEF.linearVelocity.Set(0, 60);
	playerBody.BOD = world->CreateBody(&playerBody.DEF);
	playerBody.BOD->CreateFixture(&playerBody.FIX); 
	playerBody.RECT.SetPosition(playerBody.BOD->GetPosition().x*RATIO, 
		                                  playerBody.BOD->GetPosition().y*RATIO);
}

void Player::jump(int dir) {
	if (dir == 1) {//left
	  //playerBody.BOD->SetAngularVelocity(30);
	  playerBody.BOD->SetLinearVelocity(b2Vec2(1, -10));
	//playerBody.BOD->SetLinearVelocity(b2Vec2(1, 60));
	} else if (dir == 2) { //right
		//playerBody.BOD->SetAngularVelocity(-30);
		playerBody.BOD->SetLinearVelocity(b2Vec2(-1, -10));
	} else if (dir == 3) { // up
		//playerBody.BOD->SetAngularVelocity(0);
		playerBody.BOD->SetLinearVelocity(b2Vec2(0, -12.5));
	}
}

//accessors

//deconstructor
Player::~Player() {
	playerBody.BOD->DestroyFixture(playerBody.BOD->GetFixtureList());
	world->DestroyBody(playerBody.BOD);
	//world = NULL;
}