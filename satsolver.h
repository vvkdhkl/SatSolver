#include<iostream>
#include<algorithm>

//#include<time.h>

//#include "satproblem.h"

bool brutecheck(SatProblem & satproblem, std::vector<int> varVector) {
    //std::cout<<"brutecheck ";
    bool result = true;
    for (unsigned i = 0; i<satproblem.clauses.size(); i++){
      std::vector<int> clause = satproblem.clauses[i];
      bool found = false;
      for (unsigned j = 0; j<clause.size(); j++){
        if (std::find(varVector.begin(), varVector.end(), clause[j]) != varVector.end()) {
          //std::cout<<"found here ";
          found = true;
          break;
        }
      }
      if(!(found)) {result = false; //std::cout<<"not found here ";
      break;}

    }
    return result;
}



std::vector<int> bruterec(SatProblem & satproblem, std::vector<int>  varVector, int d) {
  //std::cout<<"bruterec "<<d<<std::endl;
  if (d==satproblem.numVar) {
    if (brutecheck(satproblem, varVector)) {
  //    std::cout<<"sat: ";
      //for (unsigned i = 0; i<varVector.size(); i++){
      //  std::cout<<varVector[i]<<" ";}
      return varVector;}
    else {std::vector<int> dummy;
      //std::cout<<"unsat! ";
      return dummy;}
  }
  else {
    //d = d-1;
    varVector[d] = -std::abs(varVector[d]);
    std::vector<int> one = bruterec(satproblem, varVector, d+1);
    if (one.size()>0) return one;
    varVector[d] = std::abs(varVector[d]);
    std::vector<int> two = bruterec(satproblem, varVector, d+1);
    //std::cout<<"two size "<<two.size();
    return two;
  }
}

bool reduce(SatProblem & satproblem, int unitClause) {
  //printf("in reduce() %d \n", unitClause);
  bool to_return = true;

  for (unsigned i = 0; i < satproblem.clauses.size(); ) {
    bool delClause = false;
    for (unsigned k = 0; k < satproblem.clauses[i].size(); ) {
      if (unitClause == satproblem.clauses[i][k]) {
        delClause = true;
        satproblem.clauses.erase(satproblem.clauses.begin()+i);
        break;
      }

      else if (-unitClause == satproblem.clauses[i][k]) {

        satproblem.clauses[i].erase(satproblem.clauses[i].begin()+k);
        //to_return = false;
      }
      else {
        ++k;
      }
    }
    if (!delClause) {
      ++i;
    }
  }

  return to_return;
}



bool unitPropagate(SatProblem & satproblem, std::vector<int> & localassign){ //, std::vector<int> assign) {
  bool hasUnitClause = true;
  //std::vector<int> localassign;
  bool to_return = true;
  int unitClause = 0;
  while(hasUnitClause & to_return){
  std::cout<<" inside unitPropagate "<<satproblem.clauses.size()<<std::endl;
  //for (std::vector< std::vector<int> >::const_iterator i = satproblem.clauses.begin(); i != satproblem.clauses.end(); ++i) {
  hasUnitClause = false;


  for (unsigned i = 0; i < satproblem.clauses.size(); ++i){
    std::cout<<"i am here!!"<<std::endl;
     //satproblem.clauses.size()
    std::cout<<"propagating";
    if (satproblem.clauses[i].size()==1) {
      hasUnitClause = true;
      unitClause = satproblem.clauses[i].at(0);
      //assign.push_back(unitClause)
      break;
    }
    else if (satproblem.clauses[i].size()==0) {
      to_return = false;}
    std::cout<<"outside now"<<unitClause;
  }
  if (hasUnitClause) {
    std::cout<<"hasUnitClause"<<unitClause<<std::endl;
    //std::vector<int> solvedAssign;
    to_return = reduce(satproblem, unitClause);
    localassign.push_back(unitClause);
    }
  }
  std::cout<<"unitPropagate size "<<localassign.size()<<std::endl;
  return to_return;
}

int branch(SatProblem satproblem, std::vector<int> & assign){
  //std::cout<<"now branching "<<std::endl;
  if (assign.empty()) {
    assign.push_back(1);
    return 1;
  }
  if (assign[assign.size()-1]==satproblem.numVar){
    std::cout<<"now here"<<std::endl;
    return 0;
  }
  else {
    //std::cout<<*(assign.end())+1<<std::endl;

    int lit = assign[assign.size()-1];
    if (lit<0) {assign.push_back(-lit+1);
      return lit;}
    //printf("%d\n", lit );
    else {
      assign.back() = -lit;
    return (-lit);}


  }

}

bool DPLL_recursive2(SatProblem satproblem, std::vector<int> & assign, std::vector<int> & solvedAssign) {
  int l = 0;
  SatProblem satproblem_c = satproblem;
  bool hasEmptyClause = false;
  std::vector<int> localassign;
  if (assign.size() != 0) {
    l = assign.back();
    reduce(satproblem_c, l);}
  if (!unitPropagate(satproblem_c, localassign)) {printf("unitPropagate says unsat! \n");return false;}
  std::cout<<"size here "<<localassign.size();
  //printf("this point \n");
  //assign.reserve( assign.size() + localassign.size() ); // preallocate memory
  //assign.insert( assign.end(), assign.begin(), assign.end() );
  //assign.insert( assign.end(), localassign.begin(), localassign.end() );
  for (std::vector< std::vector<int> >::const_iterator i = satproblem_c.clauses.begin(); i != satproblem_c.clauses.end(); ++i) {
    if ((*i).size()==0)
      {hasEmptyClause = true;
      break;
    }
  }
  if (hasEmptyClause) return false;
  if (satproblem_c.clauses.size()==0) {
    std::cout<<"size "<<localassign.size();
    solvedAssign.reserve( assign.size() + localassign.size() ); // preallocate memory
    solvedAssign.insert( solvedAssign.end(), assign.begin(), assign.end() );
    solvedAssign.insert( solvedAssign.end(), localassign.begin(), localassign.end() );
   //std::cout<<"size"<<solvedAssign.size();
    //solvedAssign = assign;
    //printf("sat!");
    return true;
  }

  int nextv = 1;
  if (assign.size()!=0)
  {
    while ((std::find(localassign.begin(), localassign.end(), nextv) != localassign.end()) ||(std::find(localassign.begin(), localassign.end(), -nextv) != localassign.end() || (std::find(assign.begin(), assign.end(), nextv) != assign.end()) || (std::find(assign.begin(), assign.end(), nextv) != assign.end()))) {
        nextv++;}
    }
  std::cout<< assign.back() <<satproblem.numVar;
  if (assign.back()<=satproblem.numVar && assign.back()>0){
    assign.push_back(nextv);
    std::cout<<"    assign    !    "<<assign.back();
    //std::cout<<"heyy ! ";
    if (DPLL_recursive2(satproblem_c, assign, solvedAssign)) return true;
    //else {
    assign.back() = -std::abs(assign.back());
    std::cout<<"    assign    !    "<<assign.back();
    if (DPLL_recursive2(satproblem_c, assign, solvedAssign)) return true;
  }
  return false;

}

bool DPLL_recursive(SatProblem satproblem, std::vector<int> assign, std::vector<int> & solvedAssign) {
  int l;
  if (assign.size()==0)  {l=1; assign.push_back(l);}
  else l = assign.back();
  while (l!=0){
      if (l<0) {
              assign[std::abs(l)-1] = -l;
            l = l+1;}
      else {
            assign.back() = l;
          l = l+1;}
      std::cout<<l<<std::endl;
      //assign.push_back(l);
      std::sort(assign.begin(), assign.end(), [](int a, int b) {
            return (std::abs(a) < std::abs(b));
        });

      SatProblem satproblem_c = satproblem;
      reduce(satproblem_c, l);
      //printf(" inside DPLL_recursive \n");
      bool hasEmptyClause = false;
      std::vector<int> localassign;
      if (!unitPropagate(satproblem_c, localassign)) {printf("unitPropagate says unsat! \n");return false;}
      std::cout<<"size here "<<localassign.size();
      //printf("this point \n");
      //assign.reserve( assign.size() + localassign.size() ); // preallocate memory
      //assign.insert( assign.end(), assign.begin(), assign.end() );
      //assign.insert( assign.end(), localassign.begin(), localassign.end() );
      for (std::vector< std::vector<int> >::const_iterator i = satproblem_c.clauses.begin(); i != satproblem_c.clauses.end(); ++i) {
        if ((*i).size()==0)
          {hasEmptyClause = true;
          break;
        }
      }
      //std::cout<<"but this point"<<std::endl;
      if (hasEmptyClause) return false;
      if (satproblem.clauses.size()==0) {
        std::cout<<"size "<<localassign.size();
        solvedAssign.reserve( assign.size() + localassign.size() ); // preallocate memory
        solvedAssign.insert( solvedAssign.end(), assign.begin(), assign.end() );
        solvedAssign.insert( solvedAssign.end(), localassign.begin(), localassign.end() );
       //std::cout<<"size"<<solvedAssign.size();
        //solvedAssign = assign;
        //printf("sat!");
        return true;
      }

      //int l = branch(satproblem, assign);
      //printf("finally this point  \n");
      //if (l==0) return false;

      //std::vector<int> assign_c = assign;

      if (DPLL_recursive(satproblem_c, assign, solvedAssign)) return true;
      //satproblem_c = satproblem;
    }
  //reduce(satproblem_c, -l);
  //if (DPLL_recursive(satproblem_c, assign, solvedAssign)) return true;
  return false;
}

std::vector<int> DPLLsolver(SatProblem satproblem) {
  std::vector<int> assign;
  for (int i=1; i<=satproblem.numVar; i++)
  {
    assign.push_back(-i);
  }
  std::vector<int> solvedAssign;

  //printf("inside dpll \n");
  solvedAssign = bruterec(satproblem, assign, 0);


    return solvedAssign;
}

class SatSolver {
public:
  //SatSolver();
  //~SatSolver();

  bool timer;
  clock_t startTime;
  clock_t endTime;
  std::vector<int> solution;

  struct perfData {
    std::string algorithm;
    int numVar;
    int numClauses;
    float solvedInSeconds;
  } perfData;

  /*void resetTimer();
  void startTimer();
  void endTimer();*/
  void solve(SatProblem satproblem);
  /*void displayLastSoln();
  void lastPerfSummary();*/
};

/*void SatSolver::resetTimer() {
  timer = false;
}

void SatSolver::startTimer() {
  timer = true;
  startTime = clock();
}

void SatSolver::endTimer() {
  timer = false;
  endTime = clock();
}

void lastPerfSummary() {

}*/

void SatSolver::solve(SatProblem satproblem) {
  perfData.algorithm = "DPLL with watchlist";
  perfData.numVar = satproblem.numVar;
  perfData.numClauses = satproblem.numClauses;

  //resetTimer();
  //startTimer();
  //std::cout<<"hello";
  std::vector<int> satisf = DPLLsolver(satproblem);
  if (satisf.size()==0) printf("unsat \n");
  else {
    std::cout<<("sat ");
    //int count = 0;
    for(unsigned count=0; count< satisf.size(); count++) {
      std::cout<<satisf[count]<<' ';
    }
    std::cout<<std::endl;
    //}
          /*while (count<=satproblem.numVar){
      printf("%d ",count);
      count++;
  }*/

    }

  //endTimer();

  //perfData.solvedInSeconds = (endTime - startTime);
}
