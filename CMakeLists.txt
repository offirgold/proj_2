cmake_minimum_required(VERSION 3.12)
project(proj_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(proj_2 MySerialServer.cpp MySerialServer.h ClientHandler.h Server.h CacheManager.h Solver.h FileCacheManager.h Main.cpp Main.h main.cpp State.h Searcher.h ISearcher.h BestFirstSearch.h ISearchable.h MatrixSearchable.h MatrixSolver.h MyParallelServer.cpp MyParallelServer.h BFS.h MyClientHandler.h DFS.h MyPriorityQueue.h StringableString.cpp StringableString.h Astar.h Experiment.h)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")