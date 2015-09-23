#include "Field.h"
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
	
	//check argument
	if (argsize < 2) {
		cerr << "Wrong sintaxe: please provide an input file." << endl;	
		return 0;
	}
	
	ifstream infile;

	infile.open(argsi[1]); // open input file	
	
	if (!infile.is_open()) {
		throw ios_base::failure("Unable to open input file.");
		return 0;
	}

	string line; // get each line of input

	getline(infile, line);

	std::stringstream stm1 (line); // stringstream to read each number

	stm1 >> m;
	stm1 >> n;

	getline(infile, line);

	std::stringstream stm2 (line); // stringtream to read the character
	
	stm2 >> alive;

	vector< pair<int, int> > aliveCollection;

	// seek for living cells	
	int i = 0;
	while (true) {
		if(!getline(infile, line)) break;

		for (auto j (0ul); j < line.length(); ++j)
			if (line[j] == alive)
				aliveCollection.push_back(make_pair(i, j));
		i++;
	}

	infile.close();

	//finally build the field
	Field life {m, n, aliveCollection};


	ofstream ofs;
	if (argsize == 3) {
		ofs.open(argsi[2]);
	
		if (!ofs.is_open())
			cerr << "Error on opening output file.";
	}

	char userKeep = 'y';

	// keeping track of game's state
	while (userKeep == 'y' && life.stateField() == Field::NORMAL) {

		cout << "Generation " << life.getGeneration() << endl;

		life.print();

		if (ofs.is_open()) {
			ofs << "Generation " << life.getGeneration() << endl;
			ofs << life.toString();
			ofs << "\n";
		}
		
		cout << "Continue? " << endl;

		cin >> userKeep;
		
		if (userKeep == 'y') {
			life.update();
		}
	}	

	cout << "Generation " << life.getGeneration() + 1 << endl;
	life.print();
	ofs.close();

	// tells whether the game ended
	if (life.stateField() == Field::STABLE) 
		cout << "The game is stable." << endl;
	else if (life.stateField() == Field::EXTINCT)
		cout << "Life is extinct." << endl;
	else 
		cout << "User ended the game without stability." << endl;

	return 0;
}
