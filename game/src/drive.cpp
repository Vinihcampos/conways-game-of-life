#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include "GameOfLife.h"
#include "game.h"

/**	
*	cd conwaygameoflife/game/lib
*	g++ -I ../../include/ ../src/drive.cpp -c -std=c++11 -g
*	g++ drive.o -o ../bin/drive -lsfml-graphics -lsfml-window -lsfml-system -std=c++11 -g
*	../bin/drive
**/

static const int WIDTH = 1000;
static const int HEIGHT = 700;
static const int DISCOUNT = 90;

int main(int argsize, char *argsi[]){

	int m, n;	// field's dimensions
	char alive;	// char to indicate an living cell
	bool ** table;
	
	/*-------------------------------------
	 * Preparing for reading the input file.
	 * ------------------------------------*/	
	// check execution
	if (argsize == 1) {
		cerr << "Wrong sintaxe: please provide an input file." << endl;	
		return 0;
	}
	// declaring input stream
	ifstream ifs;
	// opening input file
	ifs.open(argsi[1]); 
	if (!ifs.is_open()) {
		cerr << "Unable to open input file." << endl;
		return 0;
	}
	cout << ">>> Input file (" << argsi[1] << ") opened!" << endl;
	
	/*-------------------------------------
	 * Preparing for writing an output file
	 * with the history of the game.
	 * ------------------------------------*/
	// output stream
	ofstream ofs; 		
	// if user wants an output file
	if (argsize == 3) {
		ofs.open(argsi[2]);
		if (!ofs.is_open()) {
			cerr << "Error on opening output file." << endl;
			return 0;
		}
	}

	
	/* ------------------------------------
	 * Preparing the game.
	 * ------------------------------------
	 * */

	string line; 

	// get each line of input
	getline(ifs, line);

	std::stringstream stm1 (line); // stringstream to read each number

	stm1 >> m;
	stm1 >> n;

	getline(ifs, line);

	std::stringstream stm2 (line); // stringtream to read the character
	
	stm2 >> alive;

	vector< pair<int, int> > aliveCollection;

	//Initializing table drawing
	table = new bool *[m];
	for(auto i (0); i < m; ++i)
		table[i] = new bool[n];

	for(auto i (0); i < m; ++i){
		for(auto j (0); j < n; ++j){
			table[i][j] = false;
		}
	}

	// reading living cells	
	int i = 0;
	while (true) {
		if(!getline(ifs, line)) break;

		for (auto j (0ul); j < line.length(); ++j)
			if (line[j] == alive){
				aliveCollection.push_back(make_pair(i, j));
				table[i][j] = true;
			}
		i++;
	}

	ifs.close(); // close input stream

	//end of input, finally build the game
	GameOfLife life {m, n, aliveCollection};
	
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game of Life");

	Game game(WIDTH, HEIGHT - DISCOUNT, m, n, table);

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

	int count = 0;	

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

        window.draw(menu);
       	for(int i = 0; i < game.getCellsHorizontal(); ++i){
       		for(int j = 0; j < game.getCellsVertical(); ++j){
       			window.draw(game.field[i][j].getAvatar());
       			//std::cout<<game.field[i][j].getActual()<<std::endl;
       		}
       	}

        window.display();
        ++count;
        if(count >= 15){
        	if(life.stateField() == GameOfLife::NORMAL){
        		life.update();
        		game.update(life.getField());
        	}
			count = 0;
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

	}

	return 0;
}