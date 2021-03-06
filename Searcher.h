//
// Created by daniella on 1/8/19.
//

#ifndef PROJ_2_SEARCHER_H
#define PROJ_2_SEARCHER_H

#include "ISearcher.h"
#include "State.h"
#include "MyPriorityQueue.h"

template<class S, class T>

class Searcher : public ISearcher<S, T> {

protected:
    MyPriorityQueue<T> *openList;
    int evalNodes;

public:
    Searcher() {
        this->openList = new MyPriorityQueue<T>();
        this->evalNodes = 0;
    };

    virtual S* search(ISearchable<T> *searchable) = 0;

    // set the number of nodes evaluated
    void setEvaluatedNodes(int n) { this->evalNodes = n; }

    // return the number of nodes evaluated
    int getNumOfNodesEval() { return this->evalNodes; }

};


#endif //PROJ_2_SEARCHER_H
