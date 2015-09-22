#include <SFML/Graphics.hpp>
#include <iostream>

int main(){
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Conway's Game of Life");
	sf::Texture texture;
	if (!texture.loadFromFile("../img/icons.png"));
	sf::Sprite sprite;
	sprite.setTexture(texture);

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
        window.draw(sprite);

        window.display();

	}

	return 0;
}