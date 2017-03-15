#include<iostream>
#include<string>
#include<vector>
#include<string>




class SatProblem {
	public:
		int numVar;
		int numClauses;
		std::vector< std::vector<int> > clauses;
		SatProblem() {}
		SatProblem(int numvar, int numclauses);
		//~SatProblem();

		bool addClause(std::vector<int> cl);
		int displayClauses();
};
 
SatProblem::SatProblem(int numvar, int numclauses) {
	numVar = numvar;
	numClauses = numclauses;
}

bool SatProblem::addClause(std::vector<int> cl) {
	std::cout<<cl.size()<<' ';
	clauses.push_back(cl);
	return true;
}


int SatProblem::displayClauses() {
	//std::cout<<"size "<<clauses.size();

	for (unsigned i = 0; i < this->clauses.size(); ++i)
			{
				if (this->clauses[i].size()==0) std::cout<<"clause empty!";
				else {
						for (unsigned j = 0; j < this->clauses[i].size(); j++)
						{
							std::cout << this->clauses[i][j] << ' ';
					   //std::cout<<"hello";
					 }
				 }
			std::cout<<std::endl;}
		  //std::cout<<"hello";}
		return 1;
}
