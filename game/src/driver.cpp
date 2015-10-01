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
static const int TITLE_MENU = 0;
static const int GAME_SCREEN = 1;

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
	Game game(WIDTH, HEIGHT - DISCOUNT, m, n, table);
	
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game of Life");

	int screen = TITLE_MENU;

	/*sf::Font font;
	// Load it from a file
	if (!font.loadFromFile("Roboto-Italic.ttf"))
		return EXIT_FAILURE;

	sf::Text introduction(font, "Choose of the options to play the game");
	introduction.setColor(sf::Color::Red);
	introduction.setCharacterSize(24);*/
	

	/*****************************************************
	* Menus iniciais
	*****************************************************/
	sf::Texture textureStep;
	if (!textureStep.loadFromFile("../img/step_by_step.png"))
		return EXIT_FAILURE;
	textureStep.setSmooth(true);

	sf::Sprite spriteStep;
	spriteStep.setTexture(textureStep);

	//Moving the step
	sf::Vector2f pos_ = spriteStep.getPosition();
	spriteStep.setPosition(WIDTH/2 - textureStep.getSize().x/2, HEIGHT/2 - textureStep.getSize().y);

	sf::Texture textureFully;
	if (!textureFully.loadFromFile("../img/fully.png"))
		return EXIT_FAILURE;
	textureFully.setSmooth(true);

	sf::Sprite spriteFully;
	spriteFully.setTexture(textureFully);

	//Moving the step
	pos_ = spriteFully.getPosition();
	spriteFully.setPosition(WIDTH/2 - textureFully.getSize().x/2, HEIGHT/2 + textureFully.getSize().y);

	/***********************************************************/	

	//Run the program while the window is open
	while(window.isOpen()){

        // clear the window with black color
        window.clear(sf::Color::Black);

		// check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
            	window.close();
            }

            //Verifying if the mouse button was pressed 
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
	           	sf::Vector2i pos = sf::Mouse::getPosition();
	           	
	           	if(event.mouseButton.x >= spriteStep.getPosition().x && event.mouseButton.x <= spriteStep.getPosition().x + textureStep.getSize().x 
	               && event.mouseButton.y >= spriteStep.getPosition().y && event.mouseButton.y <= spriteStep.getPosition().y + textureStep.getSize().y){
	           		std::cout << "Buttom step by step was pressed!" << std::endl;
				    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	            }else if(event.mouseButton.x >= spriteFully.getPosition().x && event.mouseButton.x <= spriteFully.getPosition().x + textureFully.getSize().x 
	               	  && event.mouseButton.y >= spriteFully.getPosition().y && event.mouseButton.y <= spriteFully.getPosition().y + textureFully.getSize().y){
	               	std::cout << "Buttom fully was pressed!" << std::endl;
				    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	            }
            }
        }


        if (screen == TITLE_MENU){
        	//window.draw(introduction);
           	window.draw(spriteStep);
           	window.draw(spriteFully);
        }
        window.display();

	}

	return 0;
}