//
// Created by daniella on 1/11/19.
//

#ifndef PROJ_2_MATRIXCLIENTHANDLER_H
#define PROJ_2_MATRIXCLIENTHANDLER_H


#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "MatrixSearchable.h"
#include "MatrixSolver.h"

class MyClientHandler : public ClientHandler {

    Solver<MatrixSearchable, vector<State<Point>*>> *solver;
    CacheManager<MatrixSearchable, vector<State<Point>*>> *cm;
public:
    MyClientHandler(Solver<MatrixSearchable, vector<State<Point>*>> *s,
                        CacheManager<MatrixSearchable, vector<State<Point>*>> *c) {
        solver = s;
        cm = c;
    };

    vector<string> readFromSocket(int socket) {
        bool switchFlag = true;
        string problemTemp;
        vector<string> problemFinal;
        // read continuously from socket
        while (switchFlag) {
            // first, read all data from socket into buffer
            char buffer[256];
            int messageLength = recv(socket, buffer, sizeof(buffer), 0);
            // if the message from client is not empty
            if (messageLength > 0) {
                // iterate over the buffer to find end of line
                for (int i = 0; i < messageLength; i++) {
                    if (problemTemp == "end") {
                        switchFlag = false;
                    }
                    // as long as it is not end of line -> update the string
                    else if (buffer[i] != '\r' && buffer[i + 1] != '\n') {

                        problemTemp += buffer[i];
                        //client finished entering message
                    }  else {
                        // if it is end of line and problem is not empty -> update the final string
                        if (problemTemp.length() > 0) {
                            // copy content from problemTemp to problemFinal
                            problemFinal.push_back(problemTemp);
                            problemTemp = "";
                        } else {
                            perror("string is invalid\n");
                            vector<string> bad;
                            return bad;
                        }
                    }
                }
            } else {
                perror("message from socket is empty\n");
                vector<string> bad;
                return bad;
            }
        }
        if (!problemFinal.empty())
            return problemFinal;
        else {
            perror("the string 'problem' is empty\n");
            vector<string> bad;
            return bad;
        }
    }

    virtual void handleClient(int socket) override {
        bool finish = false;
        string end = "end";
        vector<string> fromClient;
        while (!finish) {
            fromClient = readFromSocket(socket);
            //creating MatrixSearchable from string vector
            MatrixSearchable myMat = MatrixSearchable();
            myMat.convertFromString(fromClient);
            if (this->cm->isSaved(myMat)) {
                vector<State<Point>*> sol = this->cm->getSolution(myMat);
                vector<string> matVecString = myMat.convertToString();
                string vecString = convertVectorToString(matVecString);
                // send the solution to client
                const char *fromClientChar = vecString.c_str(); // convert the string to char *
                send(socket, fromClientChar, strlen(fromClientChar), 0); // write to client
                //still haven't solved this problem
            } else {
                //getting solution
                vector<State<Point>*> solution = this->solver->solve(myMat);
                // save the solution
                this->cm->saveSolution(myMat, solution);
                //converting myMat searchable to vector of strings
                vector<string> matVecString = myMat.convertToString();
                //converting vetcotr of strings to string for writing to client
                string vecString = convertVectorToString(matVecString);
                const char *solutionChar = vecString.c_str(); // convert the string to char *
                send(socket, solutionChar, strlen(solutionChar), 0); // write to client
            }
        } close(socket);
    }

    string convertVectorToString(vector<string> myVec){
        string vecString = {};
        for(int i = 0;i<myVec.size();i++){
           vecString.append(myVec[i]);
        }
        return vecString;
    }
};


#endif //PROJ_2_MATRIXCLIENTHANDLER_H