#include "main.h"

sf::RenderWindow App;
bool g_fullscreen;

int main() {
	g_fullscreen = false;
	//create the window
	App.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP), 
		             "An App", !sf::Style::Resize | sf::Style::Close);
	World *game = new World();
	Player player = Player(game->getb2World(), game->getRes(0).img_player);
	Level level1(game->getb2World(), &player, game->getRes(0).img_background);

	//this is the start of the main game loop
	while (App.IsOpen()) {
		game->getb2World()->Step(game->getTimeStep(), game->getVIterations(), game->getPIterations());
		//process any events
		sf::Event events;
		while (App.PollEvent(events)) {
			level1.input(events);
			switch (events.Type) {
			case sf::Event::Closed:
				App.Close(); //close application
				break;				
			case sf::Event::KeyPressed:
				//exit with escape
				if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Escape))
					App.Close();
				//fullscreen wih F11
				if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F11)) {
					if (g_fullscreen == false) {
						App.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP), "An App", sf::Style::Fullscreen);
						g_fullscreen = true;
					} else {
						App.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP), "An App", !sf::Style::Resize | sf::Style::Close);
						g_fullscreen = false;
					}
				}
			}
		}
		App.Clear(sf::Color(000,200,200));  //no color = black
		level1.update();
		level1.draw();
		//level1.update();
		App.Display();//display window contents
	}
	delete game;
	return 0;
}
