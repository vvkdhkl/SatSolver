#include<iostream>
#include<vector>
//#include "satsolver.h"

/*
std::vector<int> setup_watchlist(SatProblem* satproblem) {
  std::vector<int> watchlist = new std::vector<int>;
  for (std::vector< std::vector<int> >::const_iterator i = satproblem->clauses.begin(); i != satproblem->clauses.end(); ++i) {
    watchlist.push_back(abs(*((*i).begin())));
  }
  return watchlist;
}

bool update_watchlist(satProblem* satproblem, std::vector<int> watchlist, int F_literal, std::vector<int> assign, bool verbose) {
  std::vector<int>::const_iterator j = watchlist.begin();
  for (std::vector< std::vector<int> >::const_iterator i = clauses.begin(); i != clauses.end(); ++i) {
    if (*j == F_literal) {
      bool assigned = false;
      for (std::vector<int>::const_iterator k = (*i).begin(); k != (*i).end(); ++k) {
        if (assign.at(*k)!=0) {
          *j = *k;
          assigned = true;
          break;
        }
      }
      if (!assigned) {
        if (verbose) {
          dump(watchlist);
          std::cout<<"Clause contradicted! "<<dump(clause);
        }
        return false;
      }

      return true;
    }
    ++j;
  }
}

void solve(SatProblem* satproblem, std::vector<int> watchlist, std::vector<int> assign, int dTrack, bool verbose) {
  std::vector<int> state = new std::vector<int>;

}
*/
bool reduce(SatProblem satproblem, int unitClause) {
  bool to_return = true;

  for (unsigned i = 0; i < satproblem->clauses.size(); ) {
    bool delClause = false;
    for (unsigned k = 0; k < satproblem->clauses[i].size(); ) {
      if (unitClause == satproblem->clauses[i][k]) {
        delClause = true;
        satproblem->clauses.erase(satproblem->clauses.begin()+i);
        break;
      }

      else if (-unitClause == satproblem->clauses[i][k]) {

        satproblem->clauses[i].erase(satproblem->clauses[i].begin()+k);
        to_return = false;
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

bool unitPropagate(SatProblem satproblem, std::vector<int> assign) {
  bool hasUnitClause = false;
  bool to_return = true;
  int unitClause;
  for (std::vector< std::vector<int> >::const_iterator i = satproblem->clauses.begin(); i != satproblem->clauses.end(); ++i) {
    if ((*i).size()==1) {
      hasUnitClause = true;
      unitClause = *((*i).begin());
      break;
    }
  }
  if (hasUnitClause) {
    std::vector<int> solvedAssign;
    to_return = reduce(satproblem, unitClause);
    assign.push_back(unitClause);
  }
  return to_return;
}

int branch(SatProblem satproblem, std::vector<int> assign){
  if (*(assign.end())==satproblem->numVar){
    return 0;
  }
  else {
    return (*(assign.end())+1);
  }

}

bool DPLL_recursive(SatProblem satproblem, std::vector<int> assign, std::vector<int> solvedAssign) {

  bool hasEmptyClause = false;
  if (!unitPropagate(satproblem, assign)) return false;
  for (std::vector< std::vector<int> >::const_iterator i = satproblem->clauses.begin(); i != satproblem->clauses.end(); ++i) {
    if ((*i).size()==0) //{how to show to store const_iterator to vector in arrayhow to store const_iterator to vector in arraytorearraytorearraytore const_iterator to vector in array
      {hasEmptyClause = true;
      break;
    }
  }
  if (hasEmptyClause) return false;
  if (satproblem->clauses.size()==0) {
    solvedAssign = assign;
    return true;
  }

  int l = branch(satproblem, assign);
  if (l==0) return false;
  SatProblem dupliSatProblem = satproblem;
  std::vector<int> dupliAssign;
  dupliAssign = assign;
  reduce(&dupliSatProblem, l);
  if (DPLL_recursive(dupliSatProblem, dupliAssign, solvedAssign)) return true;
  reduce(satproblem, -l);
  return DPLL_recursive(satproblem, assign, solvedAssign);
}

std::vector<int> DPLLsolver(SatProblem satproblem) {
  std::cout<<"running dpll";
  std::vector<int> assign;
  std::vector<int> solvedAssign;

  if (DPLL_recursive(satproblem, assign, solvedAssign))
    return solvedAssign;
  else
    return assign;
}
