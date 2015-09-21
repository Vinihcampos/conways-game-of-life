#include "Field.h"
#include <stdexcept> 
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <functional>

/*
*	Compilation: g++ -Wall -std=c++11 -I include/ src/Field.cpp -o bin/test
*/

using namespace std; 

/* Constructor
*
* Takes the size of the field (rows x cols)
* and allocates memory for it.
* */
Field::Field( const int & _rows, const int & _cols ) : rows { _rows}, cols { _cols}, 
		 	  stable { Field::NORMAL }, generation { 1 } {
	if(_cols < 0 || _rows < 0){
		throw out_of_range( "Index provided out of valid range!" );
	}else{
		rows += 2; // Increment 2 rows to apply fence technique 
		cols += 2; // Increment 2 cols to apply fence technique
		string matrixCode = "";

		// Aloccate memory for data (rows x cols)
		data = new bool * [rows];
		for(auto i (0); i < rows; ++i){
			data[i] = new bool[cols];
		}

		// Set each position of data with 'false'
		for(auto i (0); i < rows; ++i)
			for(auto j (0); j < cols; ++j)
				data[i][j] = false;

		for(auto i (1); i < rows - 1; ++i)
			for(auto j (1); j < cols - 1; ++j)
				matrixCode += data[i][j] ? "V" : "M";

		size_t pivot = hash<string>()(matrixCode);
		historical.insert({pivot, generation});
	}
}

Field::Field( const int & _rows, const int & _cols, const vector< pair< int, int > > & pointsAlive ) : 
			  stable { Field::NORMAL }, generation { 1 } {

	if(_cols < 0 || _rows < 0){
		throw out_of_range( "Index provided out of valid range!" );
	}else{
		rows = _rows + 2; // Increment 2 rows to apply fence technique 
		cols = _cols + 2; // Increment 2 cols to apply fence technique
		string matrixCode = "";

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

		for(auto i (1); i < rows - 1; ++i)
			for(auto j (1); j < cols - 1; ++j)
				matrixCode += data[i][j] ? "V" : "M";

		size_t pivot = hash<string>()(matrixCode);
		historical.insert({pivot, generation});
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
	for(auto i(0ul); i < pointsAlive.size(); ++i){
		if(pointsAlive[i].first < 0 || pointsAlive[i].first > rows - 2 || 
		   pointsAlive[i].second < 0 || pointsAlive[i].second > cols - 2){
			throw out_of_range( "Index provided out of valid range!" );
		}else{
			data[pointsAlive[i].first + 1][pointsAlive[i].second + 1] = true;
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
		data[_row + 1][_col + 1] = true;
	}
}

/* Count how many neighbors the cell has
**/
int Field::countNeighbors(const int & _row, const int & _col){
	int _neighbors = 0;

	int d[8][2] = {{1, 1}, {1, 0}, {0, 1}, {-1, -1}, 
		         {-1, 0}, {0, -1}, {1, -1}, {-1, 1}};
	
	for (auto i(0); i < 8; ++i) {
		int rr = _row + d[i][0];
		int cc = _col + d[i][1];
		_neighbors += data[rr][cc] ? 1 : 0;
	}

	return _neighbors;
}

/* Update field's state.
* */		
void Field::update(){
	bool **aux_field = new bool *[rows];
	for(auto i (0); i < rows; ++i){
		aux_field[i] = new bool[cols];
	}

	//Fill fence field with 'false'
	for(auto i (0); i < rows; ++i){
		if(i == 0 || i == rows - 1){
			for(auto j (0); j < cols; ++j)
				aux_field[i][j] = false;
		}else{
			aux_field[i][0] = false;
			aux_field[i][cols - 1] = false;
		}
		
	}


	bool hasLife = false;
	string matrixCode = "";

	for(auto i (1); i < rows - 1; ++i){
		for(auto j (1); j < cols - 1; ++j){
			int neighbors = Field::countNeighbors(i, j);
			if(data[i][j] && neighbors <= 1){ //Applying rule 1
				aux_field[i][j] = false;
			}else if(data[i][j] && neighbors >= 4){ // Applying rule 2
				aux_field[i][j] = false;
			}else if(data[i][j]){ // Applying rule 3
				aux_field[i][j] = true;
				hasLife = true;
			}else if(!data[i][j] && neighbors == 3){ //Applying rule 4 (Part 1 - Doing a cell live)
				aux_field[i][j] = true;
				hasLife = true;
			}else{ //Applying rule 4 (Part 2 - Keeping state of cell)
				aux_field[i][j] = false;
			}
			matrixCode += aux_field[i][j] ? "V" : "M";
		}
	}

	for(auto i (0); i < rows; ++i){
		delete [] data[i];
	}
	delete [] data;

	data = aux_field;

	size_t pivot = hash<string>()(matrixCode);
	if(Field::isInside(pivot)){
		stable = Field::STABLE;
	}else{
		if(hasLife){
			historical.insert({pivot, ++generation});
			stable = Field::NORMAL;
		}else{
			stable = Field::EXTINCT;
		}		
	}
}

/* Verify if an array had been created before
**/
bool Field::isInside(size_t pivot){
	return (historical.find(pivot) != historical.end()); 
}

/* Get data method
**/
bool Field::getStatePos(const int & _row, const int & _col){
	if(_row < 0 || _row > rows - 2 || 
	   _col < 0 || _col > cols - 2){
			throw out_of_range( "Index provided out of valid range!" );
	}else{
		return data[_row + 1][_col + 1];
	}
}

/* Print field.
* */
void Field::print() const{
	for(auto i (1); i < rows - 1; ++i){
		cout<<"[ ";
		for(auto j (1); j < cols - 1; ++j){
			if(data[i][j])
				cout<<"• ";
			else
				cout<<"  ";
		}
		cout<<"]"<<endl;
	}
}

/*MAIN ONLY FOR TESTS
int main(){
	
	// Test 1
	Field f(8,8);
	f.setAlive(2,3);
	f.setAlive(2,5);
	f.setAlive(3,3);
	f.setAlive(3,4);
	f.setAlive(3,5);
	f.setAlive(4,3);
	f.setAlive(4,5);
	int count = 0;
	f.print();

	//Test 2
	Field f(10,10);
	f.setAlive(3,3);
	f.setAlive(4,5);
	f.setAlive(5,2);
	f.setAlive(5,3);
	f.setAlive(5,6);
	f.setAlive(5,7);
	f.setAlive(5,8);

	int count = 0;
	f.print();

	while(f.update()){
		//int x;
		//cin>>x;
		cout<<endl;
		f.print();
		cout<<"\n\n";
		count++;
	}
	cout<<"Number of iterations: "<<count<<endl;
	return 0;
}*/
