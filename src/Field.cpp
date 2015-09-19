#include "Field.h"
#include <stdexcept> 
#include <utility>
#include <vector>
#include <iostream>

using namespace std; 

/* Constructor
*
* Takes the size of the field (rows x cols)
* and allocates memory for it.
* */
Field::Field( const int & _rows, const int & _cols ) : rows { _rows}, cols { _cols}, _stable { Field::NORMAL }{
	if(_cols < 0 || _rows < 0){
		throw out_of_range( "Index provided out of valid range!" );
	}else{
		rows += 2; // Increment 2 rows to apply fence technique 
		cols += 2; // Increment 2 cols to apply fence technique

		// Aloccate memory for data (rows x cols)
		data = new bool * [rows];
		for(auto i (0); i < rows; ++i){
			data[i] = new bool[cols];
		}


		// Set each position of data with 'false'
		for(auto i (0); i < rows; ++i)
		for(auto j (0); j < cols; ++j)
			data[i][j] = false;
	}
}

Field::Field( const int & _rows, const int & _cols, const vector< pair< int, int > > & pointsAlive ) : _stable { Field::NORMAL }{

	if(_cols < 0 || _rows < 0){
		throw out_of_range( "Index provided out of valid range!" );
	}else{
		_stable = false;
		rows += 2; // Increment 2 rows to apply fence technique 
		cols += 2; // Increment 2 cols to apply fence technique

		// Aloccate memory for data (rows x cols)
		data = new bool * [rows];
		for(auto i (0); i < rows; ++i){
			data[i] = new bool[cols];
		}


		// Set each position of data with 'false'
		for(auto i (0); i < rows; ++i)
		for(auto j (0); j < cols; ++j)
			data[i][j] = false;

		Field::setAlive(pointsAlive);
	}
}

/* Destructor of data
**/
Field::~Field(){
	for(auto i (0); i < rows; ++i){
		delete [] data[i];
	}
	delete [] data;
}

/* Pass a vector of pair with points to set each cell alive
*/
void Field::setAlive(const vector< pair< int, int > > & pointsAlive){
	for(pair<int,int> v : pointsAlive){
		if(v.first < 0 || v.first > rows - 2 || 
		   v.second < 0 || v.second > cols - 2){
			throw out_of_range( "Index provided out of valid range!" );
		}else{
			data[v.first][v.second] = true;
		}
	}
}

/* Set manually a cell to alive.
* */
void Field::setAlive(const int & _row, const int & _col){
	if(_row < 0 || _row > rows - 2 || 
	   _col < 0 || _col > cols - 2){
			throw out_of_range( "Index provided out of valid range!" );
	}else{
		data[_row][_col] = true;
	}
}

/* Print field.
* */
void Field::print() const{
	for(auto i (1); i < rows - 1; ++i){
		cout<<"[ ";
		for(auto j (1); j < cols - 1; ++j){
			if(data[i][j])
				cout<<"V ";
			else
				cout<<"M ";
		}
		cout<<"]"<<endl;
	}
}

/*MAIN ONLY FOR TESTS
int main(){

	Field f(5,2);
	f.print();

	return 0;
}*/