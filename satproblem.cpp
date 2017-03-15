#include<iostream>

#include<string>
#include "satproblem.h"

using namespace std;

class SatProblem {
	public:
		int numVar;
		int numClauses;
		std::vector<std::string> clauses;

		void SatProblem(int numvar, int numclauses) {
			numVar = numvar;
			numClauses = numclauses;
		}
		//~SatProblem();

 
		bool addClause(cl) {
			clauses.push_back(cl);
		}
};
