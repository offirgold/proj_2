//
// Created by david on 1/8/19.
//

#ifndef PROJ_2_SEARCHABLE_H
#define PROJ_2_SEARCHABLE_H

#include <list>
#include "State.h"
#include "ISearchable.h"

template <class T>

class Searchable : public ISearchable {
public:
    virtual State<T> getInitialState() = 0;
    virtual bool isGoalState(State<T> s) = 0;
    virtual list<State<T>> getAllPossibleStates(State<T> s) = 0;
};

#endif //PROJ_2_SEARCHABLE_H
