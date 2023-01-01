/**
 * @file Graph.h
 * Funções para ler ficheiros
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_


#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include "Flight.h"
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Graph 
{
  private:
  
  public:
    Graph();
    Graph(int v_);
    void addEdge(Airport src, Airport dest, Airline line); 
    vector<string> BFS(string s, string f);
    unordered_map<string, list<Flight>> nodes;
    // static int hash(string code);
    // static string unhash(int code);
};

#endif