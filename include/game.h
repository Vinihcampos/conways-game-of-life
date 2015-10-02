#ifndef _GAME_
#define _GAME_

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

/** 
 *  \brief Class that represents a cell graphically.
 *  \version 1.0
 *  \date 2015
 *  \copyright Open Source
 *  \authors Vinicius Campos Tinoco Ribeiro, Vitor Rodrigues Greati
 */
class Avatar{
	
	private:
		sf::Sprite avatars; /**< The sprite.  */
		int actual; /**<Current generation.  */
		float proportion; /**< For resizing the cell. */
	
		/**
		 * Set size of the sprite, based on a given size and the texture.
		 * */
		void setSize(float & size, sf::Texture texture){
			sf::Vector2f scale = avatars.getScale();
			proportion = size/texture.getSize().y;
			avatars.setScale(proportion, proportion);
		}

		/**
		 * Moves the cell.
		 * */
		void move(float startX, float startY, int & posx, int & posy, float & size){
			avatars.setPosition(startX + size * posy, startY + size * posx);
			//cout<<"["<<posx<<"]["<<posy<<"]: "<<avatars.getPosition().x<<", "<<avatars.getPosition().y<<endl;			
		}

	public:
		/**
		 * Basic constructor.
		 * */
		explicit Avatar(){}

		/**
		 * Set initial configurations for the graphical object.
		 * */
		int initializeAvatar(sf::Texture & texture, float size, int posx, int posy, int _actual, float startX, float startY){

			avatars.setTexture(texture);

			setSize(size,texture);
			move(startX, startY, posx, posy, size);

			actual = _actual;

			avatars.setTextureRect(sf::IntRect(129 * actual, 0, 128, 128));

			return 0;
		}

		void setAvatar(int _actual, int _size){
			actual = _actual;
			avatars.setTextureRect(sf::IntRect(129 * actual, 0, 128, 128));
		}

		sf::Sprite getAvatar(){
			return avatars;
		}

		int getActual(){ return actual; }
		
};

/** 
 *  \brief Class that represents the game.
 *  \version 1.0
 *  \date 2015
 *  \copyright Open Source
 *  \authors Vinicius Campos Tinoco Ribeiro, Vitor Rodrigues Greati
 */
class Game{

	private:
		int width; /**< Window width. */
		int height; /**< Window height. */
		float sizeCell; /**< Size of a cell. */
		sf::Texture texture; /**< The texture of the game. */
		int cellsHorizontal; /**< Number of horizontal cells. */
		int cellsVertical; /**< Number of vertical cells. */
		

		/** \brief Stores two types of cells. */
		enum typeCells{
			BACTERIA = 0, /**< Indicates a bacteria. */
			BLANK /**< Indicates nothing there. */
		};

	public:
		Avatar ** field; /**< The field of cells (matrix). */

		/**
		 * Constructor that sets all configurations for the game.
		 * */
		Game(int _width, int _height, int _cellsHorizontal, int _cellsVertical, bool ** const _field) : 
		width {_width}, height {_height}, cellsHorizontal {_cellsHorizontal}, cellsVertical {_cellsVertical}{

			//Set avatars[zombie | vinicius | vitor ]
			if (!texture.loadFromFile("../img/bacteria_sprite.png"));
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
			//cout<<sizeCell<<endl;
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
		
		/**
		 * Updates the game.
		 * */
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
