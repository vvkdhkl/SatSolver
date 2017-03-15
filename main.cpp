#include<iostream>
#include<string>
#include<stdio.h>
#include "satproblem.h"
#include "satparser.h"
#include "satsolver.h"


int main(int argc, char* argv[]) {

	if (!(argc==2)) {
		std::cout<<argc;
		std::cout<<"Please enter the filename. You passed the wrong arguments.";

	}
	else {
		//std::cout<<"error here";
		SatProblem satProblem;// = new SatProblem();

		SatParser satParser;// = new SatParser();

		bool err = satParser.parse(std::string(argv[1]), satProblem);
		//std::cout<<"error here ";
		//printf("error here \n");

		//std::cout<<satProblem.displayClauses();
    //printf("after displaying \n");
		if (!err){
		SatSolver satSolver;


		satSolver.solve(satProblem);}
		//printf("after solve \n");

		//satSolver.displayLastSoln();
		//satSolver.lastPerfSummary();


	}

	return 0;
}
