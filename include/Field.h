#ifndef _FIELD_
#define _FIELD_

#include <vector>
#include <utility>
#include <unordered_map>
#include <functional>

using namespace std;

/** 
 *  Class that represents the Game of Life.
 */
class Field {
	
	private:		
		bool **data; /**< Represents the matrix of cells, which can have values true or false (alive or dead). */
		int rows; /**< Number of rows of the field. */
		int cols; /**< Number of columns of the field. */
		int stable; /**< Store the game state. */
		int generation; /**< Current generation. */
		unordered_map<size_t, int> historical; /**< Keep the game history in terms of generations and fields. */
		static const int DEFAULT_DIM = 10; /**< If the size is not passed to the constructor, field is built from this size.*/

	public:

		/** 
		*  This enum stores the three possible states of the game.
		*/
		enum{
			EXTINCT = 0, /**< Every cell died.  */
			STABLE,	    /**< The game doesn't change for a given frequency of updates. */
			NORMAL	   /**< The game keeps going. */
		};

		/** That takes the size of the field (rows x cols)
		 * and allocates memory for it.
		 * */
		explicit Field(const int & _rows = DEFAULT_DIM, const int & _cols = DEFAULT_DIM);
		Field(const int & _rows, const int & _cols, const vector< pair< int, int > > & pointsAlive);
		
		/** Set manually a cell to alive.
		 * */
		void setAlive(const vector< pair< int, int > > & pointsAlive );
		void setAlive(const int & _row, const int & _col);
		
		/* Verify the state of the field
		 * */		
		int stateField() const{ return stable; };

		/* Verify if an array had been created before
		**/
		bool isInside(size_t pivot);
		
		/* Count how many neighbors the cell has
		**/
		int countNeighbors(const int & row, const int & col);

		/* Update field's state.
		 * */		
		void update();
		
		/* Print field.
		 * */
		void print() const;

		/* Return a string with the configution of matrix
		**/
		string toString();

		/** Destroy the field.
		*/
		~Field();

		/* Get rows method
		**/
		int getRows() const{ return rows; };

		/* Get cols method
		**/
		int getCols() const{ return cols; };

		/* Get generation
		**/
		int getGeneration() const { return generation; };

		/* Get data method
		**/
		bool getStatePos(const int & _row, const int & _col);



};

#endif
