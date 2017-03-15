#include<iostream>

#include<string>
//#include "satparser.h"

Class SetParser {
	void parse(file, satproblem) {
		ifstream probFile(file);
		string line;
 
		while (getline(infile, line))
		{
			istringstream iss(line);
			iss.split(' ');
			if (iss[0] == 'p') {
				satproblem.numVar = iss[2];
				satproblem.numClauses = iss[3];
			}
			else if not (iss[0]=='c'){
				index = 0;
				int* clause[(sizeof(iss)/sizeof(*iss))-1];
				while ((iss[index]) & (iss[index]!=0)) {
					clause[index] = iss[index]
					index++;
				}


				satproblem.addClause(clause);
			}

		}

	}
};
