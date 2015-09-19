#include "Field.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argsize, char *argsi[]) {

	int m, n;
	char alive;
	
	//check argument
	if (argsize < 1) 
		throw invalid_argument("Wrong sintaxe!\nUse...");
	
	//if it's ok
	ifstream infile;
	infile.open(args[0]);
	
	if (!infile.is_open())
		throw ios_base::failure("Unable to open input file.");

	string line;

	getline(infile, line);
	// takes field size
	m = line[0]; n = line[2];	
	
	getline(infile, line);

	alive = line[0];
	
	vector< pair<int, int> > aliveCollection;

	int i = 0;
	while (true) {
		if(!getline(infile, line)) break;

		for (int j = 0; j < line.length(); ++j)
			if (line[j] == alive)
				aliveCollection.push_back(make_pair(i, j));
		i++;
	}
	//finally build the field
	Field life {m, n, aliveCollection};
	
	int generation = 1;
	char userKeep = 'y';

	while (userKeep == 'y' && !life.stable()) {

		cout << "Generation " << generation << endl;

		life.print();
		
		cout << "Continue? " << endl;

		cin >> userKeep;
		
		if (userKeep == 'y') {
			life.update();
			++generation;
		}
	}	
		
	if (life.stable()) 
		cout << "The game is stable." << endl;
	else if (life.extinct())
		cout << "Life is extinct." << endl;
	else 
		cout << "User ended the game without stability." << endl;

	return 0;
}
