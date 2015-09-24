#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

static const int WIDTH = 800;
static const int HEIGHT = 600;

int loadCharacter(sf::Texture * texture, sf::Sprite * boys, std::string caminho, int size){
	for(int i = 1; i < size; ++i){
		std::stringstream sstm;
		sstm << caminho << i << ".png";
		std::string url = sstm.str();
		if (!texture[i-1].loadFromFile(url))
			return EXIT_FAILURE;

		boys[i-1].setTexture(texture[i-1]);
	}

	return 0;
}

int main(){
	
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game of Life");

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
	menu.setPosition((WIDTH - textureMenu.getSize().x * 0.35)/2 , HEIGHT - (textureMenu.getSize().y * 0.35));

	//Sprites boy
	sf::Texture textureBoy[9];
	sf::Sprite boys[9];
	loadCharacter(textureBoy, boys, "../img/boy_menor/boy", 9); 
	float timerBoy = 0.f;


	//Sprites zombie
	sf::Texture textureZombie[16];
	sf::Sprite zombies[16];
	loadCharacter(textureZombie, zombies, "../img/zombie_menor/zombie", 16);
	float timerZombie = 0.f;
	

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
        
        //Draw boy
        window.draw(boys[(int)timerBoy/9]);
        timerBoy += 1;
        if(timerBoy >= 81)
        	timerBoy = 1;

        /*Draw zombie
        window.draw(zombies[(int)timerZombie/16]);
        timerZombie += 2;
        if(timerZombie >= 256)
        	timerZombie = 0;*/
        
        window.display();

	}

	return 0;
}