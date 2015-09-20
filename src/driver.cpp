#include "Field.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;

	//int main(int argsize, char *args[]) {
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

	cout << "oi";

	int m, n;
	char alive;
	
	//check argument
	if (argsize < 2)
	       cerr << "Wrong sintaxe: please provide an input file." << endl;	
		//throw invalid_argument("Wrong sintaxe!\nUse...");
	
	cout << "oioi" << endl;
	//if it's ok
	ifstream infile;

	infile.open(argsi[1]);	
	
	if (!infile.is_open())
		throw ios_base::failure("Unable to open input file.");

	string line;

	getline(infile, line);

	std::stringstream stm (line);

	stm >> m;
	stm >> n;

	getline(infile, line);
	
	std::stringstream stm2 (line);
	
	stm2 >> alive;

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
	Field life (m, n, aliveCollection);
	
	int generation = 1;
	char userKeep = 'y';

	while (userKeep == 'y' && life.stateField() != Field::STABLE) {

		cout << "Generation " << generation << endl;

		life.print();
		
		cout << "Continue? " << endl;

		cin >> userKeep;
		
		if (userKeep == 'y') {
			life.update();
			++generation;
		}
	}	
		
	if (life.stateField() == Field::STABLE) 
		cout << "The game is stable." << endl;
	else if (life.stateField() == Field::EXTINCT)
		cout << "Life is extinct." << endl;
	else 
		cout << "User ended the game without stability." << endl;

	return 0;
}
