#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
//#include "satproblem.h"

class SatParser {
public:
	bool parse(std::string, SatProblem &);

 
};

bool SatParser::parse(std::string file, SatProblem & satproblem ) {
	bool err = false;
	bool headerRead = false;
	std::ifstream probFile(file.c_str());
	std::string line;
  //std::cout<<"error here";
	if (probFile.is_open()) {
		int countCl = 0;
		while (getline(probFile, line))
		{
			//std::cout<<"error here";
			//probFile >> line;
			std::istringstream iss(line);
			std::string token;
			//if (iss) ge;tline(iss, token, ' ');
			if (!(iss >> token)) {break;}
			//std::cout<<"token"<<token<<"/token";
			if (token == std::string(1, 'p')) {
				if (!headerRead && !err) headerRead = true;
				else {
					std::cout<<"error: multiple head lines, check Dimacs format!"<<std::endl;
						err = true;
				}
				//std::cout<<"size "<<clause.size();
				int count = 1;
				while(iss >> token){
					//getline(iss, token, ' ');

					if (count==2) { satproblem.numVar = std::stoi(token);}
					else if (count==3) {satproblem.numClauses = std::stoi(token);}
					else if (count>3 && !err) {std::cout<<"error: unrecognizable items in first line!"<<std::endl;
						err = true;}
					count++;
				}
			}
			else if (!(token ==std::string(1,'c'))){
				try {

					countCl++;

				std::vector<int> clause;
				//std::cout<<std::stoi(token)<<std::endl;
				//std::cout<<"error here";
				clause.push_back(std::stoi(token));
				int count=0;
						while(iss >> token) {
							//getline(iss, token, ' ');

							//std::cout<<std::stoi(token)<<std::endl;

							if (stoi(token)!=0) {
								count++ ;
								if (std::abs(stoi(token))<=satproblem.numVar) {
								clause.push_back(std::stoi(token));}
								else if (!err) {
									std::cout<<"error: more literals than mentioned in header!"<<std::endl;
									err = true;
								}

								//std::cout<<"error here";

								//std::cout<<std::stoi(token)<<' ';
								//for (std::vector<int>::const_iterator i = clause.begin(); i != clause.end(); ++i)
									//std::cout << *i << ' ';
							//std::cout<<std::stoi(token)<<std::endl;
						}
					}
				//if (stoi(token)!=0) then we have a problem here. handle it.
				//clause.resize(count+1);
				//std::cout<<"size "<<clause.size();
						if (clause.size()!=0) {
							//std::cout<<"happy";

							satproblem.clauses.push_back(clause);
							//std::cout<<"size "<<satproblem.clauses.size();
						//std::cout<<"hello";
						}
			}
		catch(...){
			std::cout<<"error: non-numeric strings in clauses!"<<std::endl;
				err = true;
			}

		}

		}
		//std::cout<<countCl<<satproblem.numClauses;
		if (countCl>satproblem.numClauses && !err) {
			std::cout<<"error: more clauses than mentioned in header!"<<std::endl;
			err = true;
		} else if (countCl<satproblem.numClauses && !err) {
			std::cout<<"error: less clauses than mentioned in header!"<<std::endl;
			err = true;
		}
		probFile.close();

	}
	return err;
}
