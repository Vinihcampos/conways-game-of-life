#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "game.h"

/**	
*	cd conwaygameoflife/game/lib
*	g++ -I ../../include/ ../src/drive.cpp -c -std=c++11 -g
*	g++ drive.o -o ../bin/drive -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
*	../bin/drive
**/

static const int WIDTH = 1000;
static const int HEIGHT = 700;
static const int DISCOUNT = 90;

int main(){
	
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game of Life");
	bool ** table;
	table = new bool * [10];
		for(int i = 0; i < 10; ++i){
			table[i] = new bool [10];
	}

	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){
			table[i][j] = true;
		}
	}

	Game game(WIDTH, HEIGHT - DISCOUNT, 10, 10, table);

	/**
	*	Menu
	**/ 
	// Load a texture to menu
	sf::Texture textureMenu;
	if (!textureMenu.loadFromFile("../img/menu_player.png"))
		return EXIT_FAILURE;
	textureMenu.setSmooth(true);

	//Using the textureMenu to use like a sprite
	sf::Sprite menu;
	menu.setTexture(textureMenu);

	//Resizing the object
	sf::Vector2f scale = menu.getScale();
	menu.setScale(scale.x * 0.35, scale.y * 0.35);

	//Moving the object
	sf::Vector2f pos = menu.getPosition();
	menu.setPosition(WIDTH/2 - (textureMenu.getSize().x * 0.35)/2, HEIGHT - (textureMenu.getSize().y * 0.35));

	

	//Run the program while the window is open
	while(window.isOpen()){

		// check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            	window.close();
            else if(event.type == sf::Event::MouseButtonPressed){
            	if(event.mouseButton.button == sf::Mouse::Left){
            		std::cout << "the right button was pressed" << std::endl;
			        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
            	}
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        window.draw(menu);
        
       	for(int i = 0; i < game.getCellsHorizontal(); ++i){
       		for(int j = 0; j < game.getCellsVertical(); ++j){
       			window.draw(game.field[i][j].getAvatar());
       			//std::cout<<game.field[i][j].getActual()<<std::endl;
       		}
       	}
        
        window.display();

	}

	return 0;
}