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
*	valgrind --leak-check=yes ./bin/gameoflife data/virus.dat
**/

static const int WIDTH = 1000;
static const int HEIGHT = 700;
static const int DISCOUNT = 70;
static const int TITLE_MENU = 0;
static const int GAME_SCREEN_STEP = 1;
static const int GAME_SCREEN_FULLY = 2;
static const int FINAL_GAME = 3;

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

	// Final of file prepare
	/****************************************************************************/
	
	GameOfLife life {m, n, aliveCollection};
	Game game(WIDTH, HEIGHT - DISCOUNT, m, n, table);
	
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game of Life");
	window.setFramerateLimit(60);

	int screen = TITLE_MENU;

	sf::Font font;
	// Load it from a file
	if (!font.loadFromFile("../src/Colleged.ttf"))
		return EXIT_FAILURE;

    sf::Text generation;	
    generation.setFont(font);
	generation.setColor(sf::Color::White);
	generation.setCharacterSize(36);

	sf::Vector2f position = generation.getPosition();
	generation.setPosition(position.x, position.y + HEIGHT - 50);


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
	spriteFully.setPosition(WIDTH/2 - textureFully.getSize().x/2, HEIGHT/2 + textureFully.getSize().y);

	/*************************************************************************************************/
	//Set sprites final game
	
	sf::Texture finalExtinct;
	
	//Load file extinct
	if(!finalExtinct.loadFromFile("../img/extinct.png"))
		return EXIT_FAILURE;
	finalExtinct.setSmooth(true);
	
	sf::Sprite spriteExtinct;
	spriteExtinct.setTexture(finalExtinct);

	//Move the extinct to center;
	spriteExtinct.setPosition(WIDTH/2 - finalExtinct.getSize().x/2, HEIGHT/2 - finalExtinct.getSize().y/2);

	sf::Texture finalStable;

	//Load file stable
	if(!finalStable.loadFromFile("../img/stable.png"))
		return EXIT_FAILURE;
	finalStable.setSmooth(true);

	sf::Sprite spriteStable;
	spriteStable.setTexture(finalStable);

	//Move the stable to center;
	spriteStable.setPosition(WIDTH/2 - finalStable.getSize().x/2, HEIGHT/2 - finalStable.getSize().y/2);	

	/***********************************************************/	

	//	Manually timer to draw matrix.
	int count = 0;
	//	mouse release
	bool press = true;
	//	draw aux
	bool canWrite = true;

	//Run the program while the window is open
	while(window.isOpen()){

        // clear the window with black color
        window.clear(sf::Color::Black);

		// check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
            	//delete field;
				for(auto i (0); i < m; ++i){
					delete [] table[i];
				}
				delete [] table;
				ofs.close();
				window.close();
            }

            //Verifying if the mouse button was pressed 
            if(screen == TITLE_MENU && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
	           	sf::Vector2i pos = sf::Mouse::getPosition();
	           	
	           	if(event.mouseButton.x >= spriteStep.getPosition().x && event.mouseButton.x <= spriteStep.getPosition().x + textureStep.getSize().x 
	               && event.mouseButton.y >= spriteStep.getPosition().y && event.mouseButton.y <= spriteStep.getPosition().y + textureStep.getSize().y){
	           		screen = GAME_SCREEN_STEP;
	            }else if(event.mouseButton.x >= spriteFully.getPosition().x && event.mouseButton.x <= spriteFully.getPosition().x + textureFully.getSize().x 
	               	  && event.mouseButton.y >= spriteFully.getPosition().y && event.mouseButton.y <= spriteFully.getPosition().y + textureFully.getSize().y){
	               	screen = GAME_SCREEN_FULLY;
	            }
            }// Verifying if scree is game screen with steps and if the space is pressed
            else if(screen == GAME_SCREEN_STEP && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && press){
         		
            	if(life.stateField() == GameOfLife::NORMAL){

            		if (ofs.is_open()) {
						ofs << "\nGeneration: " << life.getGeneration() << endl;
						ofs << life.toString();
						ofs << "\n";
					}

	        		life.update();
	        		game.update(life.getField());
	        		if(life.stateField() != GameOfLife::NORMAL){
	        			screen = FINAL_GAME;	        		
	        		}
	        	}
	        	press = false;	
            }

            // If space isn't pressed, the veriable press receive true;
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				press = true;
            }
        }


        if(screen == FINAL_GAME){
        	if(canWrite){
        		canWrite = false;
        		if(life.stateField() == GameOfLife::EXTINCT){
        			if (ofs.is_open()) {
						ofs << "Extinct generation: " << life.getGeneration() << endl;
						ofs << life.toString();
						ofs << "----------------------------------------------\n" << endl;
						ofs << ">>> The game was executed successfully!" << endl; 
						ofs << ">>> Life is extinct." << endl;
						ofs << ">>> The life was extinct at generation " << life.getGeneration() << "." << endl;
						ofs << "\n----------------------------------------------" << endl;
					}
        		}else{
        			if (ofs.is_open()) {
						ofs << "First repeat of generation: " << life.getGeneration() << endl;
						ofs << life.toString();
						ofs << "----------------------------------------------\n" << endl;
						ofs << ">>> The game was successfully executed!" << endl; 
						ofs << ">>> The life is stable." << endl;
						ofs << ">>> The life started to be stable in generation " << life.getLifeStability() << "." << endl;
						ofs << ">>> Started to repeat at generation " << life.getGeneration() << "." << endl;
						ofs << "\n----------------------------------------------" << endl;
					}
        		}
        	}
            if(life.stateField() == GameOfLife::EXTINCT){
				window.draw(spriteExtinct);
				std::ostringstream ss; //string buffer to convert numbers to string
				ss << "Number of generations: " << life.getGeneration();
				generation.setString(ss.str());
	        	window.draw(generation);
            }else{
				window.draw(spriteStable);
				std::ostringstream ss; //string buffer to convert numbers to string
				ss << "Number of generations: " << life.getGeneration() - 1;
				generation.setString(ss.str());
	        	window.draw(generation);
			}
			

	        
        }else if (screen == TITLE_MENU){
           	window.draw(spriteStep);
           	window.draw(spriteFully);
        }else if(screen == GAME_SCREEN_FULLY){
        	for(int i = 0; i < game.getCellsHorizontal(); ++i){
	       		for(int j = 0; j < game.getCellsVertical(); ++j){
	       			window.draw(game.field[i][j].getAvatar());
	       		}
	       	}
	        ++count;
	        if(count >= 15){
	        	if(life.stateField() == GameOfLife::NORMAL){

	        		if (ofs.is_open()) {
						ofs << "\nGeneration: " << life.getGeneration() << endl;
						ofs << life.toString();
						ofs << "\n";
					}

	        		life.update();
	        		game.update(life.getField());
	        	}else{
	        		screen = FINAL_GAME;
	        	}
				count = 0;
	        }
	        std::ostringstream ss; //string buffer to convert numbers to string
			ss << "Generation: " << life.getGeneration();

	        generation.setString(ss.str());
	        window.draw(generation);
        }else{
        	for(int i = 0; i < game.getCellsHorizontal(); ++i){
	       		for(int j = 0; j < game.getCellsVertical(); ++j){
	       			window.draw(game.field[i][j].getAvatar());
	       		}
	       	}
	       	std::ostringstream ss; //string buffer to convert numbers to string
			ss << "Generation: " << life.getGeneration();

	        generation.setString(ss.str());
	       	window.draw(generation);
        }        	

        window.display();

	}

	return 0;
}