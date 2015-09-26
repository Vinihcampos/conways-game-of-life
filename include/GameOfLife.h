#ifndef _LIFE_
#define _LIFE_

#include <vector>
#include <utility>
#include <map>
#include <functional>
#include <string>

using namespace std;

/** 
 *  \brief Class that represents the Game of Life.
 *  \details It contains a bidimentional array of booleans,
 *  where each position represents a cell, that
 *  can be alive (true) or dead (false). Besides that,
 *  the class encapsulates all actions related to
 *  the game, including update, history storage
 *  and print methods.
 *  \version 1.0
 *  \date 2015
 *  \copyright Open Source
 *  \authors Vinicius Campos Tinoco Ribeiro, Vitor Rodrigues Greati
 */
class GameOfLife {
	
	private:		
		bool **data; /**< Represents the matrix of cells, which can have values true or false (alive or dead). */
		int rows; /**< Number of rows of the field. */
		int cols; /**< Number of columns of the field. */
		int stable; /**< Store the game state. */
		int generation; /**< Current generation. */
		int lifeStability; /**< Stability generation. */
		multimap<size_t, pair< int, string > > historical; /**< Keep the game history in terms of generations and fields. */
		static const int DEFAULT_DIM = 10; /**< If the size is not passed to the constructor, field is built from this size.*/

	public:

		/** 
		*  \brief This enum stores the three possible states of the game.
		*/
		enum{
			EXTINCT = 0, /**< Every cell died.  */
			STABLE,	    /**< The game doesn't change for a given frequency of updates. */
			NORMAL	   /**< The game keeps going. */
		};

		/**Takes the size of the field (rows and columns)
		 * and allocates memory for it, setting all cells
		 * to dead (false).
		 * */
		explicit GameOfLife(const int & _rows = DEFAULT_DIM, const int & _cols = DEFAULT_DIM);
		
		/** Takes the size of the field (rows and columns) and a list of
		 *  cells to be setted as alive. 
		 * */
		GameOfLife(const int & _rows, const int & _cols, const vector< pair< int, int > > & pointsAlive);
		
		/** Destroys the allocated memory for the game.
		*/
		~GameOfLife();
		
		/** Set manually a cell to alive, taking
		 * a list of cells from a vector of pairs, where
		 * 'pair.first' is the x value and 'pair.second'
		 * is the y value.
		 * */
		void setAlive(const vector< pair< int, int > > & pointsAlive );
		
		/** Set manually a cell to alive,
		 *  simply taking the row and the column value
		 *  of the cell.
		 * */
		void setAlive(const int & _row, const int & _col);
		
		/** Verify the state of the field.
		 *  \return A state: STABLE, EXTINCT, NORMAL
		 * */		
		int stateField() const{ return stable; };

		/** Visits the history to check the stability of the game.
		*   \return If that state has already been reached.
		*/
		bool isInside(size_t & pivot /** A number (by hash) that represents the current game. */, 
			      string & matrixCode /** The configuration of the field to be checked.  */);
		
		/** Count how many alive cells is around the
		*   cell located at the position passed as arguments.
		*   
		*   \return The number of alive cells around data[row][col].
		*/
		int countNeighbors(const int & row, const int & col);

		/** Update the field's state, based on
		 *  Game of Life's rules:
		 *  
		 *  - if a cell is alive, but the number of living neighbors is less than or equal to one,
		 *  this cell will die in the next generation;
		 *  - if a cell is alive and has four os more living neighbors, this cell will die in the
		 *  next generation due to overpopulation;
		 *  - if a cell is alive with two or three neighbors, it will keep alive in the next generation;
		 *  - if a cell is dead, so, in the next generation, it will become alive if it has three neighbors
		 *  exactly. If it has a number of neighbors different of three, it will keep dead;
		 *  - All births and deads happen exactly at the same time, so cells that are dying can help other
		 *  to become alive, but can't prevent the dead of others due to overpopulation reduction; in the
		 *  same way, cells that are dawning can't preserve or kill living cells at the previous generation.
		 * */		
		void update();
		
		/** Prints the field.
		 * */
		void print() const;

		/** Makes a string representation of the game.
		 * \returns String that represents the game.
		**/
		string toString();

		/** \return Number of rows.
		*/
		int getRows() const{ return rows; };

		/** \return Number of columns.
		**/
		int getCols() const{ return cols; };

		/** \return The current generation.
		**/
		int getGeneration() const { return generation; };

		/** \return The generation of stability.
		**/
		int getLifeStability() const { return lifeStability; };

		/** \return True if the cell is alive, false if it's dead.
		**/
		bool getStatePos(const int & _row, const int & _col);

		bool ** getField(){ return data; }

};

#include "../src/GameOfLife.cpp"
#endif
