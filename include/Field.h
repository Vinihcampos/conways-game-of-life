#ifndef _FIELD_
#define _FIELD_

#include <vector>
#include <utility>

using namespace std;

static const int DEFAULT_DIM = 10;

class Field {
	
	private:		
		bool **data;
		int rows, cols;
		int stable;
	
	public:

		enum{
			EXTINCT = 0,
			STABLE,
			NORMAL
		};



		/* Constructor
		 *
		 * Takes the size of the field (rows x cols)
		 * and allocates memory for it.
		 * */
		explicit Field(const int & _rows = DEFAULT_DIM, const int & _cols = DEFAULT_DIM);
		Field(const int & _rows, const int & _cols, const vector< pair< int, int > > & pointsAlive);
		
		/* Set manually a cell to alive.
		 * */
		void setAlive(const vector< pair< int, int > > & pointsAlive );
		void setAlive(const int & _row, const int & _col);
		
		/* Verify the state of the field
		 * */		
		int stateField() const{ return stable; };
		
		/* Count how many neighbors the cell has
		**/
		int countNeighbors(const int & row, const int & col);

		/* Update field's state.
		 * */		
		bool update();
		
		/* Print field.
		 * */
		void print() const;

		/* Destructor of class Field
		**/
		~Field();

		/* Get rows method
		**/
		int getRows() const{ return rows; };

		/* Get cols method
		**/
		int getCols() const{ return cols; };

		/* Get data method
		**/
		bool getStatePos(const int & _row, const int & _col);

};

#endif
