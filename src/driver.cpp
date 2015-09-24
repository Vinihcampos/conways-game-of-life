#include "GameOfLife.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;

int main(int argsize, char *argsi[]) {

	int m, n;	// field's dimensions
	char alive;	// char to indicate an living cell
	
	/*-------------------------------------
	 * Preparing for reading the input file.
	 * ------------------------------------*/	
	// check execution
	if (argsize == 1) {
		cerr << "Wrong sintaxe: please provide an input file." << endl;	
		return 0;
	}
	// declaring input stream
	ifstream ifs;
	// opening input file
	ifs.open(argsi[1]); 
	if (!ifs.is_open()) {
		cerr << "Unable to open input file." << endl;
		return 0;
	}
	cout << ">>> Input file opened!" << endl;
	
	/*-------------------------------------
	 * Preparing for writing an output file
	 * with the history of the game.
	 * ------------------------------------*/
	// output stream
	ofstream ofs; 		
	// if user wants an output file
	if (argsize == 3) {
		ofs.open(argsi[2]);
		if (!ofs.is_open()) {
			cerr << "Error on opening output file." << endl;
			return 0;
		}
	}
	
	/* ------------------------------------
	 * Preparing the game.
	 * ------------------------------------
	 * */

	string line; 

	// get each line of input
	getline(ifs, line);

	std::stringstream stm1 (line); // stringstream to read each number

	stm1 >> m;
	stm1 >> n;

	getline(ifs, line);

	std::stringstream stm2 (line); // stringtream to read the character
	
	stm2 >> alive;

	vector< pair<int, int> > aliveCollection;

	// reading living cells	
	int i = 0;
	while (true) {
		if(!getline(ifs, line)) break;

		for (auto j (0ul); j < line.length(); ++j)
			if (line[j] == alive)
				aliveCollection.push_back(make_pair(i, j));
		i++;
	}

	ifs.close(); // close input stream

	//end of input, finally build the game
	GameOfLife life {m, n, aliveCollection};

	cout << ">>> Data processed." << endl;
	cout << ">>> Size of the game: " << m << " x " << n << endl;
	cout << ">>> Character " << alive << " indicates a living cell." << endl;
	
	/*------------------------------------
	 * Treating user's control.
	 * ----------------------------------*/
	char userKeep = 'y';

	// keeping track of game's state
	while (userKeep == 'y' && life.stateField() == GameOfLife::NORMAL) {

		cout << "Generation " << life.getGeneration() << endl;

		life.print();

		if (ofs.is_open()) {
			ofs << "Generation " << life.getGeneration() << endl;
			ofs << life.toString();
			ofs << "\n";
		}
		
		cout << "Continue? (y/n)  " << endl;

		cin >> userKeep;
		
		if (userKeep == 'y') {
			life.update();
		}
	}	

	//cout << "Generation " << life.getGeneration() + 1 << endl;
	//life.print();
	ofs.close();

	// tells why the game ended
	if (life.stateField() == GameOfLife::STABLE) { 
		cout << "The game is stable." << endl;
		cout << "The game started to be stable in generation " << life.getGeneration() << endl;
	} else if (life.stateField() == GameOfLife::EXTINCT)
		cout << "Life is extinct." << endl;
	else 
		cout << "User ended the game without stability." << endl;

	return 0;
}
