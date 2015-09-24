#ifndef _GAME_
#define _GAME_
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Avatar{
	
	private:
		sf::Texture * textures;
		sf::Sprite * avatars;
		int actual;

		void setSize(float & size){
			sf::Vector2f scale;
			for(int i = 0; i < 3; ++i){
				scale = avatars[i].getScale();
				avatars[i].setScale(scale.x * (size/128), scale.y * (size/128));
			}
		}

		void move(float startX, float startY, int & posx, int & posy, float & size){
			for(int i = 0; i < 3; ++i)
				avatars[i].setPosition(startX + size * posy, startY + size * posx);

				//cout<<"["<<posx<<"]["<<posy<<"]: "<<avatars[0].getPosition().x<<", "<<avatars[0].getPosition().y<<endl;			
		}

	public:
		explicit Avatar(){}
		int setAvatar(float size, int posx, int posy, int _actual, float startX, float startY){
			textures = new sf::Texture[3];
			avatars = new sf::Sprite[3];

			//Set avatar zombie
			if (!textures[0].loadFromFile("../img/zombie.png"))
				return EXIT_FAILURE;
			textures[0].setSmooth(true);
			avatars[0].setTexture(textures[0]);

			//Set avatar vinicius
			if (!textures[1].loadFromFile("../img/vinicius.png"))
				return EXIT_FAILURE;
			textures[1].setSmooth(true);
			avatars[1].setTexture(textures[1]);

			//Set avatar vitor
			if (!textures[2].loadFromFile("../img/vitor.png"))
				return EXIT_FAILURE;
			textures[2].setSmooth(true);
			avatars[2].setTexture(textures[2]);

			setSize(size);
			move(startX, startY, posx, posy, size);
			actual = _actual;

			return 0;
		}
		~Avatar(){
			delete [] avatars;
			delete [] textures;
		}

		void setActual(int _actual){ actual = _actual;}
		int getActual(){ return actual; }

		sf::Sprite getAvatar(){
			return avatars[actual];
		}
		
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
						field[i][j].setAvatar(sizeCell, i, j, VITOR, startX, startY);
					}else{
						field[i][j].setAvatar(sizeCell, i, j, BLANK, startX, startY);
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
							field[i][j].setActual(VINICIUS);
						else
							field[i][j].setActual(VITOR);
					}else{
						if(field[i][j].getActual() != BLANK)
							field[i][j].setActual(ZOMBIE);
					}
				}
			}
		}

};



#endif