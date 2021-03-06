//
// Created by david on 1/13/19.
//

#ifndef PROJ_2_BFS_H
#define PROJ_2_BFS_H

#include <unordered_set>
#include "Searcher.h"

template<class S, class T>

class BFS : public Searcher <S, T> {
    S* search(ISearchable<T> *searchable) {
        vector<State<T> *> pVec;
        unordered_set<State<T> *> closed;
        State<T> *s = searchable->getInitialState();
        s->setCameFrom(NULL);
        this->openList->push(s);
        searchable->getInitialState()->setVisited(true);
        bool flag = true;

        while (!this->openList->getQueue()->empty() && flag == true) { // while openList is not empty
            State<T> *n = this->openList->popAndGet();
            if (searchable->isGoalState(n)) {
                closed.insert(n);
                pVec = searchable->backTrace(n);
                flag = false;
            }
            if (flag) {
                this->evalNodes++;
                list < State<T> * > successors = searchable->getAllPossibleStates(n); // Create n's successors
                for (typename list<State<T>*>::iterator it = successors.begin(); it != successors.end(); ++it) {
                    State<T> *s = *it;
                    s->setCameFrom(n);
                    this->openList->push(s);
                }
            }
        }
        if (!pVec.empty()) {
            int pathCost;
            for (int i = 0; i < pVec.size(); i++) {
                pathCost += pVec[i]->getCost();
            }
            State<T> *newGoal = searchable->getGoal();
            newGoal->setCostPath(pathCost);
            searchable->setGoal(newGoal);

            return (searchable->getDirections(pVec));
        }
        else throw ("path is empty!\n");
    }
};

#endif //PROJ_2_BFS_H