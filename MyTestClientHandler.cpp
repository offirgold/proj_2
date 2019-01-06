//
// Created by david on 1/3/19.
//

#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include "MyTestClientHandler.h"

// constructor
MyTestClientHandler::MyTestClientHandler(Solver<string, string> *s, CacheManager<string, string> *c) {
    this->solver = s;
    this->cm = c;
}

// function: gets socket and return the message received from socket until end of line
string MyTestClientHandler::readFromSocket(int socket) {
    bool switchFlag = true;
    string problemTemp;
    string problemFinal;
    // read continuously from socket
    while (switchFlag) {
        // first, read all data from socket into buffer
        char[256] buffer;
        int messageLength = recv(socket, buffer, sizeof(buffer), 0);
        // if the message from client is not empty
        if (messageLength > 0) {
            // iterate over the buffer to find end of line
            for (int i = 0; i < messageLength; i++) {
                // as long as it is not end of line -> update the string
                if (buffer[i] != '\n')
                    problemTemp += buffer[i];
                else {
                    // if it is end of line and problem is not empty -> update the final string
                    if (problemTemp.length() > 0) {
                        // copy content from problemTemp to problemFinal
                        for (int j = 0; j < problemTemp.length(); j++)
                            problemFinal[j] = problemTemp[j];
                        problemTemp = "";
                        switchFlag = false;
                    } else {
                        perror("string is invalid\n");
                        return nullptr;
                    }
                }
            }
        } else {
            perror("message from socket is empty\n");
            return nullptr;
        }
    }
    if (!problemFinal.empty())
        return problemFinal;
    else {
        perror("the string 'problem' is empty\n");
        return nullptr;
    }
}

// overridden virtual function
void MyTestClientHandler::handleClient(int socket) {
    bool finish = false;
    string end = "end";
    string fromClient;
    while (!finish) {
        fromClient = readFromSocket(socket);
        if (fromClient == end) {
            finish = true;
        } else {
            if (this->cm->isSaved(fromClient)) {
                // send the solution to client
                const char *fromClientChar = fromClient.c_str(); // convert the string to char *
                send(socket, fromClientChar, strlen(fromClientChar), 0); // write to client
            } else {
                string solution = this->solver->solve(fromClient); // solve the problem
                this->cm->saveSolution(solution); // save the solution
                const char *solutionChar = solution.c_str(); // convert the string to char *
                send(socket, solutionChar, strlen(solutionChar) , 0); // write to client
            }
        }
    }
}