#ifndef _GAME_
#define _GAME_
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Avatar{
	
	private:
		sf::Texture texture;
		sf::Sprite avatars;
		sf::IntRect subRect;
		int actual;

		void setSize(float & size){
			sf::Vector2f scale = avatars.getScale();
			auto sizeInX = size * 512 / 128; 
			avatars.setScale((sizeInX/512), size/128);
		}

		void move(float startX, float startY, int & posx, int & posy, float & size){
			avatars.setPosition(startX + size * posy, startY + size * posx);
			//cout<<"["<<posx<<"]["<<posy<<"]: "<<avatars.getPosition().x<<", "<<avatars.getPosition().y<<endl;			
		}

	public:
		explicit Avatar(){}

		int initializeAvatar(float size, int posx, int posy, int _actual, float startX, float startY){

			//Set avatars[zombie | vinicius | vitor ]
			if (!texture.loadFromFile("../img/sprites_final.png"))
				cout<<"fuuu";
			texture.setSmooth(true);
			avatars.setTexture(texture);

			setSize(size);
			move(startX, startY, posx, posy, size);

			actual = _actual;
			//cout<<texture.getSize().x<<","<<texture.getSize().y<<endl;
			
			subRect.left = size * actual;
			subRect.top = 0;
			subRect.width = size;
			subRect.height = size;

			avatars.setTextureRect(subRect);

			return 0;
		}

		void setAvatar(int _actual, int _size){
			actual = _actual;

			subRect.left = _size * actual;

			avatars.setTextureRect(subRect);
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
		int cellsHorizontal;
		int cellsVertical;

		enum typeCells{
			ZOMBIE = 0,
			VINICIUS,
			VITOR,
			BLANK
		};

	public:
		Avatar ** field;
		Game(int _width, int _height, int _cellsVertical, int _cellsHorizontal, bool ** const _field) : 
		width {_width}, height {_height}, cellsHorizontal {_cellsHorizontal}, cellsVertical {_cellsVertical}{

			field = new Avatar * [cellsHorizontal];
			for(int i = 0; i < cellsHorizontal; ++i){
				field[i] = new Avatar [cellsVertical];
			}

			sizeCell = width/cellsHorizontal <= height/cellsVertical ? (width/cellsHorizontal) : (height/cellsVertical);
			cout<<sizeCell<<endl;
			float startX = (float)(width - sizeCell * cellsHorizontal)/2; 
			float startY = (float)(height - sizeCell * cellsVertical)/2;
			for(int i = 0; i < cellsHorizontal; ++i){
				for(int j = 0; j < cellsVertical; ++j){
					if(_field[i][j]){
						field[i][j].initializeAvatar(sizeCell, i, j, VITOR, startX, startY);
					}else{
						field[i][j].initializeAvatar(sizeCell, i, j, BLANK, startX, startY);
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
			for(int i = 0; i < cellsHorizontal; ++i){
				for(int j = 0; j < cellsVertical; ++j){
					bool state = _field[i][j];
					if(state){
						if(field[i][j].getActual() == VITOR)
							field[i][j].setAvatar(VINICIUS, sizeCell);
						else
							field[i][j].setAvatar(VITOR, sizeCell);
					}else{
						if(field[i][j].getActual() != BLANK)
							field[i][j].setAvatar(ZOMBIE, sizeCell);
					}
				}
			}
		}

};



#endif