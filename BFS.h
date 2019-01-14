//
// Created by david on 1/13/19.
//

#ifndef PROJ_2_BFS_H
#define PROJ_2_BFS_H

#include <unordered_set>
#include "Searcher.h"

template<class P, class S, class T>

class BFS : public Searcher <P, S, T> {
    S search(ISearchable<T> *searchable);
};

#endif //PROJ_2_BFS_H
