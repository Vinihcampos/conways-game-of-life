#include "Field.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <fstream>

using namespace std;

<<<<<<< HEAD
int main(int argsize, char *args[]) {
=======
/*void writeInFile(Field & field, ofstream & outfile, int & generation, string & arg){
	outfile.open(arg, ios::ate);
	if (!outfile.is_open())
		throw ios_base::failure("Unable to open output file.");
	else{
		outfile<<"\nGeneration: "<<generation<<endl;
		for(auto i (1); i < field.getRows() - 1; ++i){
			outfile<<"[";
			for(auto j (1); j < field.getCols() - 1; ++j){
				if(field.getStatePos(i,j))
					outfile<<"•";
				else
					outfile<<" ";
			}
			outfile<<"]"<<endl;	
		}
		outfile.close();	
	}
}*/

int main(int argsize, char *argsi[]) {
>>>>>>> 3da1ae5426c968e6b46b2c0b23d37afc7f4c6704

	int m, n;
	char alive;
	
	//check argument
	if (argsize < 1) 
		throw invalid_argument("Wrong sintaxe!\nUse...");
	
	//if it's ok
	ifstream infile;

	infile.open(argsi[0]);	
	
	if (!infile.is_open())
		throw ios_base::failure("Unable to open input file.");

	//OUTFILE
	//if(argsize == 2){
	//	ofstream outfile;		
	//}

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

	infile.close();

	//finally build the field
	Field life {m, n, aliveCollection};
	
	int generation = 1;
	char userKeep = 'y';

<<<<<<< HEAD
	while (userKeep == 'y' && life.stable() != Field::EXTINCT && life.stable() != Field::STABLE) {
=======
	while (userKeep == 'y' && life.stateField() != Field::STABLE) {
>>>>>>> 3da1ae5426c968e6b46b2c0b23d37afc7f4c6704

		cout << "Generation " << generation << endl;

		life.print();
		
		cout << "Continue? " << endl;

		cin >> userKeep;
		
		if (userKeep == 'y') {
			life.update();
			++generation;
		}
	}	
		
<<<<<<< HEAD
	if (life.isStable() == Field::STABLE) 
		cout << "The game is stable." << endl;
		else if (life.stable() == Field::EXTINCT)
=======
	if (life.stateField() == Field::STABLE) 
		cout << "The game is stable." << endl;
	else if (life.stateField() == Field::EXTINCT)
>>>>>>> 3da1ae5426c968e6b46b2c0b23d37afc7f4c6704
		cout << "Life is extinct." << endl;
	else 
		cout << "User ended the game without stability." << endl;

	return 0;
}
