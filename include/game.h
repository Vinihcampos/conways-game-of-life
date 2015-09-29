#ifndef _GAME_
#define _GAME_

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Avatar{
	
	private:
		sf::Sprite avatars;
		int actual;
		float proportion;

		void setSize(float & size, sf::Texture texture){
			sf::Vector2f scale = avatars.getScale();
			proportion = size/texture.getSize().y;
			avatars.setScale(proportion, proportion);
		}

		void move(float startX, float startY, int & posx, int & posy, float & size){
			avatars.setPosition(startX + size * posy, startY + size * posx);
			//cout<<"["<<posx<<"]["<<posy<<"]: "<<avatars.getPosition().x<<", "<<avatars.getPosition().y<<endl;			
		}

	public:
		explicit Avatar(){}

		int initializeAvatar(sf::Texture & texture, float size, int posx, int posy, int _actual, float startX, float startY){

			avatars.setTexture(texture);

			setSize(size,texture);
			move(startX, startY, posx, posy, size);

			actual = _actual;

			avatars.setTextureRect(sf::IntRect(128 * actual, 0, 128, 128));

			return 0;
		}

		void setAvatar(int _actual, int _size){
			actual = _actual;
			avatars.setTextureRect(sf::IntRect(128 * actual, 0, 128, 128));
		}

		sf::Sprite getAvatar(){
			return avatars;
		}

		int getActual(){ return actual; }
		
};

class Game{

	private:
		int width;
		int height;
		float sizeCell;
		sf::Texture texture;
		int cellsHorizontal;
		int cellsVertical;

		enum typeCells{
			BACTERIA = 0,
			BLANK
		};

	public:
		Avatar ** field;

		Game(int _width, int _height, int _cellsHorizontal, int _cellsVertical, bool ** const _field) : 
		width {_width}, height {_height}, cellsHorizontal {_cellsHorizontal}, cellsVertical {_cellsVertical}{

			//Set avatars[zombie | vinicius | vitor ]
			if (!texture.loadFromFile("../img/bacteria_sprite.png"))
				cout<<"fuuu";
			texture.setSmooth(true);

			field = new Avatar * [cellsHorizontal];
			for(int i = 0; i < cellsHorizontal; ++i){
				field[i] = new Avatar [cellsVertical];
			}

			if((float) width/cellsVertical < (float) height/cellsHorizontal){
				sizeCell = (float) width/cellsVertical;
			}else{
				sizeCell = (float) height/cellsHorizontal;
			}

			//sizeCell = width/cellsVertical <= height/cellsHorizontal ? (width/cellsVertical) : (height/cellsHorizontal);
			cout<<sizeCell<<endl;
			float startX = (float) width /  2 - (sizeCell * cellsVertical)/2; 
			float startY = (float) height / 2 - (sizeCell * cellsHorizontal)  /2;
			for(int i = 0; i < cellsHorizontal; ++i){
				for(int j = 0; j < cellsVertical; ++j){
					if(_field[i][j]){
						field[i][j].initializeAvatar(texture, sizeCell, i, j, BACTERIA, startX, startY);
					}else{
						field[i][j].initializeAvatar(texture, sizeCell, i, j, BLANK, startX, startY);
					}
				}
			}
		}

		~Game(){
			for(int i = 0; i < cellsHorizontal; ++i){
				delete [] field[i];
			}
			delete [] field;
		}

		int getCellsHorizontal(){ return cellsHorizontal; }
		int getCellsVertical(){ return cellsVertical; }


		void update(bool ** _field){
			for(int i = 1; i <= cellsHorizontal; ++i){
				for(int j = 1; j <= cellsVertical; ++j){
					bool state = _field[i][j];
					if(state)
						field[i-1][j-1].setAvatar(BACTERIA, sizeCell);
					else
						field[i-1][j-1].setAvatar(BLANK, sizeCell);
				}
			}
		}

};



#endif